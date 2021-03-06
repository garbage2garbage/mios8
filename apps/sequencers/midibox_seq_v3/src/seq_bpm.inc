; $Id$
;
; MIDIboxSEQ
; BPM Timer function
;
; Some notes to the way how MIDIboxSEQ generates the internal 96ppqn clock
;
; MASTER MODE
; ~~~~~~~~~~~
;
; The period of USER_Timer will be configured based on bpm_table.inc which
; is a generated file (utils\gen_bpm_table.pl). The values are calculated 
; based on the formula: delay = (60 / (bpm * 24)) / prescaler_delay
; 
; For a common MIDI clock (24ppqn), 8 should be used as prescaler delay to 
; realize BPM rates from 48 to 255
; But MBSEQ works with 4 times resolution (96ppqn), therefore a prescaler
; delay of 2 is used here
;
; The USER_Timer hook increments the SEQ_CLK_REQ_CTR with every invokation
; which triggers the SEQ_CORE_Clk function. Using a counter instead of a
; request flag ensures that a clock event never get lost, even though the
; sequencer handler won't be called for a certain time - e.g. during a
; EEPROM write transfer
;
;
; SLAVE MODE
; ~~~~~~~~~~
;
; Could be realized by incrementing the SEQ_CLK_REQ_CTR by 4 with every
; received MIDI clock. But for the current implementation I spent some
; effort to realize 3 interpolated clock events between the received
; MIDI clocks in order to increase the resolution.
;
; This mechanism works that way: USER_Timer is used as reference
; counter which will be invoked every 500 uS. It measures the delay
; between two F8 events by incrementing a counter SEQ_INCOMING_CLK_CTR
; which will be registered in SEQ_INCOMING_CLK_DELAY on the next F8
; event.
;
; The delay value will be divided by 4, this is the preload value of
; SEQ_SENT_CLK_DELAY which defines the delay between interpolated clock
; events. The SEQ_SENT_CLK_DELAY will be decremented by USER_Timer
; every 500 uS. Once it reaches zero, a clock event will be triggered,
; and SEQ_SENT_CLK_DELAY will be reloaded by SEQ_INCOMING_CLK_DELAY / 4
;
; The SEQ_SENT_CLK_CTR ensures that never more than 3 internal clock
; events will be triggered by USER_Timer. This is to avoid timing 
; failures on BPM sweeps or jittering MIDI interfaces.
;
; And now the trick for stable timings: SEQ_MIDI_NotifyRx_Clk 
; (which receives the F8 events) increments SEQ_SENT_CLK_CTR by
; 4 - SEQ_SENT_CLK_CTR. 
;
; This ensures that the sequencer will always run in sync with
; the external MIDI clock, and that a 96ppqn clock event never
; get lost, regardless of jitter or BPM sweeps
;
; Copyright (C) 22th January 2004 by Thorsten Klose
;
; ==========================================================================
;
;  Copyright 1998-2006 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

;; --------------------------------------------------------------------------
;;  This function returns the BPM setting
;; --------------------------------------------------------------------------
SEQ_BPM_Get
	SET_BSR	SEQ_BPM
	movf	SEQ_BPM, W, BANKED
	return
	

;; --------------------------------------------------------------------------
;;  This function sets the clock mode to master (WREG==0) or slave (WREG==1) or auto (WREG==2)
;; --------------------------------------------------------------------------
SEQ_BPM_ModeSet
	IRQ_DISABLE
	SET_BSR	SEQ_BASE
	bcf	SEQ_CFG0, SEQ_CFG0_BPM_CLK_SLAVE, BANKED
	btfsc	WREG, 0
	bsf	SEQ_CFG0, SEQ_CFG0_BPM_CLK_SLAVE, BANKED

	bcf	SEQ_CFG0, SEQ_CFG0_BPM_CLK_AUTO, BANKED
	btfsc	WREG, 1
	bsf	SEQ_CFG0, SEQ_CFG0_BPM_CLK_AUTO, BANKED

	;; re-init BPM timer
	movf	SEQ_BPM, W, BANKED
	rgoto	SEQ_BPM_Set

;; --------------------------------------------------------------------------
;;  This function sets the timer to a given BPM period length
;;  Expecting: BPM in WREG, clock mode in SEQ_CFG0,SEQ_CFG0_BPM_CLK_SLAVE
;; --------------------------------------------------------------------------
SEQ_BPM_Set
	;; disable all IRQs
	IRQ_DISABLE

	;; set BPM rate
	SET_BSR	SEQ_BPM
	movwf	SEQ_BPM, BANKED

	;; branch depending on master/slave mode
	BRA_IFCLR SEQ_CFG0, SEQ_CFG0_BPM_CLK_SLAVE, BANKED, SEQ_BPM_Master
SEQ_BPM_Slave
	;; in slave mode, the timer will be used to measure the delay between
	;; one clock, in order to produce 4 internal clocks on every F8 event
	;; using 500 uS as reference
	movlw	5000 & 0xff
	movwf	MIOS_PARAMETER1
	movlw	5000 >> 8
	movwf	MIOS_PARAMETER2
	movlw	0x00
	call	MIOS_TIMER_Init

	;; update LED digits
	rcall	SEQ_BPM_DigitUpdate_Slave

	rgoto	SEQ_BPM_End

	
SEQ_BPM_Master
	;; reset NOECHO flag
	bcf	SEQ_REQ, SEQ_REQ_NOECHO, BANKED

	;; calc address to timer value:
	movlw	(3125000 >> 16) & 0xff
	movwf	MATH_AARGB0
	movlw	(3125000 >> 8) & 0xff
	movwf	MATH_AARGB1
	movlw	(3125000) & 0xff
	movwf	MATH_AARGB2

	clrf	MATH_BARGB0
	movf	SEQ_BPM, W, BANKED
	movwf	MATH_BARGB1

	call	MATH_DIV24_16

	;; result in MATH_AARGB1:MATH_AARGB2
	;; copy to MIOS_PARAMETER[12]
	movff	MATH_AARGB2, MIOS_PARAMETER1
	movff	MATH_AARGB1, MIOS_PARAMETER2

	;; init timer; prescaler 1:2
	movlw	0x01
	call	MIOS_TIMER_ReInit

	;; update LED digits
	rcall	SEQ_BPM_DigitUpdate_Master

SEQ_BPM_End
	;; enable IRQs again and exit
	IRQ_ENABLE
	return


SEQ_BPM_Stop
	goto	MIOS_TIMER_Stop


;; --------------------------------------------------------------------------
;;  This function is called by mb_timer.inc to generate a MIDI clock event
;;  Note that this is an interrupt service routine! Use FSR2 instead of FSR0
;;  and IRQ_TMPx instead of TMPx -- and make the routine as fast as possible!
;; --------------------------------------------------------------------------
SEQ_BPM_Tick
	SET_BSR	SEQ_BASE
	BRA_IFCLR SEQ_CFG0, SEQ_CFG0_BPM_CLK_SLAVE, BANKED, SEQ_BPM_Tick_Master
SEQ_BPM_Tick_Slave
	;; increment the clock counter, used to measure the delay between two F8 events
	;; see also SEQ_MIDI_NotifyRx
	incf	SEQ_INCOMING_CLK_CTR, F, BANKED

	;; decrement sent clock delay, send interpolated clock events 3 times
	;; (more infos: see header of seq_bpm.inc)
	decf	SEQ_SENT_CLK_DELAY, F, BANKED
	bnz	SEQ_BPM_Tick_Slave_NoTrigger
SEQ_BPM_Tick_Slave_Trigger
	movf	SEQ_SENT_CLK_CTR, W, BANKED
	xorlw	0x03
	bz	SEQ_BPM_Tick_Slave_NoTrigger
	incf	SEQ_SENT_CLK_CTR, F, BANKED
	incf	SEQ_CLK_REQ_CTR, F, BANKED
	rrf	SEQ_INCOMING_CLK_DELAY, W, BANKED
	rrf	WREG, W
	andlw	0x3f
	movwf	SEQ_SENT_CLK_DELAY, BANKED
SEQ_BPM_Tick_Slave_NoTrigger
	return


SEQ_BPM_Tick_Master
	;; increment clock request counter which is used by SEQ_CORE
	incf	SEQ_CLK_REQ_CTR, F, BANKED

	return


;; --------------------------------------------------------------------------
;;  this function updates the LED digits for slave mode (display SLA)
;; --------------------------------------------------------------------------
SEQ_BPM_DigitUpdate_Slave
	lfsr	FSR1, BPM_DIGIT_2
	;; coding: see SEQ_BPM_Digit_TABLE

                ; habcdefg
	movlw	b'01011011' ; S
	movwf	POSTDEC1
	movlw	b'00001110' ; L
	movwf	POSTDEC1
	movlw	b'01110111' ; A
	movwf	POSTDEC1

	return

;; --------------------------------------------------------------------------
;;  this function updates the LED digits for master mode (display BPM value)
;; --------------------------------------------------------------------------
SEQ_BPM_DigitUpdate_Master
	;; convert BPM value to BCD
	SET_BSR	SEQ_BPM
	movf	SEQ_BPM, W, BANKED	; low byte in WREG
	clrf	MIOS_PARAMETER1		; high byte in MIOS_PARAMETER1 (here: always 0)
	call	MIOS_HLP_Dec2BCD	; now: digits in MIOS_PARAMETER[12]

	lfsr	FSR1, BPM_DIGIT_0

	movf	MIOS_PARAMETER1, W
	andlw	0x0f
	rcall	SEQ_BPM_DigitUpdate_Hlp
	movwf	POSTINC1

	swapf	MIOS_PARAMETER1, W
	andlw	0x0f
	rcall	SEQ_BPM_DigitUpdate_Hlp
	movwf	POSTINC1

	movf	MIOS_PARAMETER2, W
	andlw	0x0f
	rcall	SEQ_BPM_DigitUpdate_Hlp
	movwf	POSTINC1

	return


	;; help function which returns the segment code depending on WREG (0-15)
SEQ_BPM_DigitUpdate_Hlp
	TABLE_ADDR_MUL_W SEQ_BPM_Digit_TABLE, 1
	tblrd*+
	movf	TABLAT, W
	return

SEQ_BPM_Digit_TABLE
;    a
;   ---
;  !   !
; f! g !b
;   ---
;  !   !
; e!   !c
;   ---
;    d   h
; 1 = on, 0 = off
; NOTE: the dod (h) will be set automatically by the driver above when bit 7 is set
                ; habcdefg
	db	b'01111110', b'00110000' ; 0, 1
	db	b'01101101', b'01111001' ; 2, 3
	db	b'00110011', b'01011011' ; 4, 5
	db	b'01011111', b'01110000' ; 6, 7
	db	b'01111111', b'01111011' ; 8, 9
	db	b'01110111', b'00011111' ; A, B
	db	b'01001110', b'00111101' ; C, D
	db	b'01001111', b'01000111' ; E, F


;; --------------------------------------------------------------------------
;;  This function is called when a tempo is "tapped" with a button
;; --------------------------------------------------------------------------
SEQ_BPM_TapTempo
	SET_BSR	SEQ_BASE

	;; determine new tempo if timer hasn't been enabled yet, or on overrun
	BRA_IFCLR T0CON, TMR0ON, ACCESS, SEQ_BPM_TapTempo_New
	BRA_IFSET INTCON, TMR0IF, ACCESS, SEQ_BPM_TapTempo_New

SEQ_BPM_TapTempo_Beat
	;; stop timer
	bcf	T0CON, TMR0ON

	;; transfer new timer value to PROD[LH]
	;; (required, as TMR0H latch cannot be used as calculation target - it's indirectly updated on access to TMR0L)
	movff	TMR0L, PRODL
	movff	TMR0H, PRODH

	;; if measured delay is < 0x2000: BPM > 256 (ca. 286) --- cannot be processed anyhow
	;; such taps will be ignored, because it can be assumed that they happened because
	;; of a bouncing button
	movf	PRODH, W
	andlw	0xe0
	bz	SEQ_BPM_TapTempo_Beat_Ignore

SEQ_BPM_TapTempo_Beat_GoodOne
	;; increment beat counter
	incf	SEQ_TAPTEMPO_BEAT_CTR, F, BANKED

	;; ensure that beat counter won't overrun to zero (so that average calculation restarts)
	;; however, in reality the user would never tap more than 256 times without a break ;)
	movlw	0x83
	btfsc	SEQ_TAPTEMPO_BEAT_CTR, 7, BANKED
	andwf	SEQ_TAPTEMPO_BEAT_CTR, F, BANKED

	
	;; add measured time to average array
	lfsr	FSR1, SEQ_TAPTEMPO_AVERAGE0_L
	rlf	SEQ_TAPTEMPO_BEAT_CTR, W, BANKED
	andlw	0x06
	addwf	FSR1L, F

	;; add new timer value (divided by 4) to array
	clrc
	rrf	PRODH, F
	rrf	PRODL, F
	clrc
	rrf	PRODH, F
	rrf	PRODL, F

	movff	PRODL, POSTINC1
	movff	PRODH, POSTDEC1

	;; calculate new mean value
	clrf	SEQ_TAPTEMPO_MEAN_L, BANKED
	clrf	SEQ_TAPTEMPO_MEAN_H, BANKED
	clrf	PRODL
	lfsr	FSR1, SEQ_TAPTEMPO_AVERAGE0_L
SEQ_BPM_TapTempo_Beat_AvgLoop
	movf	POSTINC1, W
	addwf	SEQ_TAPTEMPO_MEAN_L, F, BANKED
	movf	POSTINC1, W
	addwfc	SEQ_TAPTEMPO_MEAN_H, F, BANKED
	incf	PRODL, F
	BRA_IFCLR PRODL, 2, ACCESS, SEQ_BPM_TapTempo_Beat_AvgLoop

	;; once counter reached value >= 4, calculate BPM
	movf	SEQ_TAPTEMPO_BEAT_CTR, W, BANKED
	andlw	0xfc
	bz	SEQ_BPM_TapTempo_Beat_NoBPM
SEQ_BPM_TapTempo_Beat_BPM
	;; timer is clocked each 25.600 uS
	;; accordingly the BPM is: 60 / (SEQ_TAPTEMPO_MEAN * 25.600 uS)
	;;                     or: (60/25.6 uS) / SEQ_TAPTEMPO_MEAN
	;;         -> fixed point: 2343750 / SEQ_TAPTEMPO_MEAN
	;; we can use the already included MATH_DIV24_16 routine to calculate this! :-)

	movlw	(2343750 >> 16) & 0xff
	movwf	MATH_AARGB0
	movlw	(2343750 >> 8) & 0xff
	movwf	MATH_AARGB1
	movlw	(2343750) & 0xff
	movwf	MATH_AARGB2

	movff	SEQ_TAPTEMPO_MEAN_L, MATH_BARGB1
	movff	SEQ_TAPTEMPO_MEAN_H, MATH_BARGB0

	call	MATH_DIV24_16

	;; result in MATH_AARGB1:MATH_AARGB2
	;; saturate if high byte != 0
	movf	MATH_AARGB1, W
	skpz
	setf	MATH_AARGB2

	;; if BPM value < 48, force it to 48 (requirement of SEQ_BPM_Set routine)
	movlw	48
	cpfsgt	MATH_AARGB2
	movwf	MATH_AARGB2

	;; before setting BPM: ensure that sequencer not running in slave mode
	SET_BSR	SEQ_BASE
	bcf	SEQ_CFG0, SEQ_CFG0_BPM_CLK_SLAVE, BANKED

	;; MATH_AARGB2 contains the BPM
	movf	MATH_AARGB2, W
	rcall	SEQ_BPM_Set
	
SEQ_BPM_TapTempo_Beat_NoBPM

SEQ_BPM_TapTempo_Beat_Ignore
	;; clear 16bit timer register
	clrf	TMR0H
	clrf	TMR0L

	;; ensure that TMR0IF is cleared
	bcf	INTCON, TMR0IF

	;; start timer: clocked by internal source, 16bit, prescaler 1:2
	movlw	(1 << TMR0ON) | (7 << 0)
	movwf	T0CON	

	return


SEQ_BPM_TapTempo_New
	;; clear beat counter
	clrf	SEQ_TAPTEMPO_BEAT_CTR, BANKED

	;; stop timer
	bcf	T0CON, TMR0ON

	;; ensure that timer0 interrupt not enabled (-> normaly used by MIOS_AIN driver)
	bcf	INTCON, T0IE

	;; clear 16bit timer register
	clrf	TMR0H
	clrf	TMR0L

	;; clear TMR0IF (overrun flag)
	bcf	INTCON, TMR0IF

	;; start timer: clocked by internal source, 16bit, prescaler 1:2
	movlw	(1 << TMR0ON) | (7 << 0)
	movwf	T0CON	
	
	return
	
