; $Id$
;
; MBSEQ Menu "Step Progression"
;
; ==========================================================================
;
;  Copyright 1998-2006 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

;; --------------------------------------------------------------------------
;;  This is the menu specific GP callback function called by cs_menu_button.inc 
;;  when the GP hook has been installed
;;  Input:
;;     o GP Button number in MIOS_PARAMETER1 (0x00-0x0f)
;;     o Button value MIOS_PARAMETER2:
;;       - 1 if button has been released (=5V)
;;       - 0 if button has been pressed (=0V)
;;  Output:
;;     should return the GP LED values in CS_MENU_GP_OVERLAY_DOUT_SR[01]
;; --------------------------------------------------------------------------
CS_M_UTILS_GP_Callback
	;; all LEDs off when GP button has been depressed
	BRA_IFCLR MIOS_PARAMETER2, 0, ACCESS, CS_M_UTILS_GP_Callback_On
CS_M_UTILS_GP_Callback_Off
	setf	CS_MENU_CURSOR_POS	; (invalidate)
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_On
	;; store button number in cursor pos
	movff	MIOS_PARAMETER1, CS_MENU_CURSOR_POS

	;; branch depending on button number
	movf	MIOS_PARAMETER1, W
	andlw	0x0f
	JUMPTABLE_2BYTES_UNSECURE
	rgoto	CS_M_UTILS_GP_Callback_0
	rgoto	CS_M_UTILS_GP_Callback_1
	rgoto	CS_M_UTILS_GP_Callback_2
	rgoto	CS_M_UTILS_GP_Callback_3
	rgoto	CS_M_UTILS_GP_Callback_4
	rgoto	CS_M_UTILS_GP_Callback_5
	rgoto	CS_M_UTILS_GP_Callback_6
	rgoto	CS_M_UTILS_GP_Callback_7
	rgoto	CS_M_UTILS_GP_Callback_8
	rgoto	CS_M_UTILS_GP_Callback_9
	rgoto	CS_M_UTILS_GP_Callback_A
	rgoto	CS_M_UTILS_GP_Callback_B
	rgoto	CS_M_UTILS_GP_Callback_C
	rgoto	CS_M_UTILS_GP_Callback_D
	rgoto	CS_M_UTILS_GP_Callback_E
	rgoto	CS_M_UTILS_GP_Callback_F

CS_M_UTILS_GP_Callback_0	; Track Copy
	call	CS_M_HLP_GetSelectedTrk
	movff	WREG, SEQ_EVNTT
	rcall	CS_M_UTILS_CopyTrack
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_1	; Track Paste
	call	CS_M_HLP_GetSelectedTrk
	movff	WREG, SEQ_EVNTT
	rcall	CS_M_UTILS_PasteTrack
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_2	; Track Clear
	call	CS_M_HLP_GetSelectedTrk
	movff	WREG, SEQ_EVNTT
	rcall	CS_M_UTILS_ClearTrack
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_3	; reserved
	setf	CS_MENU_CURSOR_POS	; (invalidate)
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_4	; Pattern Copy
	rcall	CS_M_UTILS_CopyPattern
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_5	; Pattern Paste
	rcall	CS_M_UTILS_PastePattern
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_6	; Pattern Clear
	rcall	CS_M_UTILS_ClearPattern
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_7	; reserved
	setf	CS_MENU_CURSOR_POS	; (invalidate)
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_8	; Undo
	rcall	CS_M_UTILS_Undo
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_9	; reserved
	setf	CS_MENU_CURSOR_POS	; (invalidate)
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_A	; reserved
	setf	CS_MENU_CURSOR_POS	; (invalidate)
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_B	; reserved
	setf	CS_MENU_CURSOR_POS	; (invalidate)
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_C	; reserved
	setf	CS_MENU_CURSOR_POS	; (invalidate)
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_D	; reserved
	setf	CS_MENU_CURSOR_POS	; (invalidate)
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_E	; Mute All Tracks
	rcall	CS_M_UTILS_MuteAll
	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_F	; UnMute All Tracks
	rcall	CS_M_UTILS_UnMuteAll
	;; 	rgoto	CS_M_UTILS_GP_Callback_Cont

CS_M_UTILS_GP_Callback_Cont
	;; update LEDs
	rcall	CS_M_UTILS_UpdateGPLEDs

	;; request display update and exit
	bsf	CS_STAT, CS_STAT_DISPLAY_UPDATE_REQ
	return


;; --------------------------------------------------------------------------
CS_M_UTILS_UpdateGPLEDs
	;; clear all LEDs
	clrf	CS_MENU_GP_OVERLAY_DOUT_SR0
	clrf	CS_MENU_GP_OVERLAY_DOUT_SR1

	;; *don't* flash LEDs
	bsf	MB_STAT, MB_STAT_DONT_FLASH_R_GP_DOUT
	bsf	MB_STAT, MB_STAT_DONT_FLASH_L_GP_DOUT

	;; don't lit LED if cursor pos == 0xff (no option triggered)
	incf	CS_MENU_CURSOR_POS, W
	bz	CS_M_UTILS_UpdateGPLEDs_End
	
	;; set LED 1-16 depending on last selected option
	movf	CS_MENU_CURSOR_POS, W
	call	MIOS_HLP_GetBitORMask
	btfss	CS_MENU_CURSOR_POS, 3
	movwf	CS_MENU_GP_OVERLAY_DOUT_SR0
	btfsc	CS_MENU_CURSOR_POS, 3
	movwf	CS_MENU_GP_OVERLAY_DOUT_SR1

CS_M_UTILS_UpdateGPLEDs_End
	return


;; --------------------------------------------------------------------------
;;  Menu Init routine is called when menu page should be initialized
;; --------------------------------------------------------------------------
CS_M_UTILS_Init
	;; install callback function for general purpose buttons, used to select an item here
	TABLE_ADDR CS_M_UTILS_GP_Callback
	call	CS_MENU_SetMenuGPCallbackHook

	;; set cursor pos to invalid value (0xff) -> no LED will lit
	setf	CS_MENU_CURSOR_POS

	;; update LEDs
	rgoto	CS_M_UTILS_UpdateGPLEDs


;; --------------------------------------------------------------------------
;;  Menu Tick routine is called on every refresh cycle
;; --------------------------------------------------------------------------
CS_M_UTILS_Tick
	;; layout:
	;; 00000000001111111111222222222233333333330000000000111111111122222222223333333333
	;; 01234567890123456789012345678901234567890123456789012345678901234567890123456789
	;; <--------------------------------------><-------------------------------------->
	;; BD    UTILS         Track Copied                                                   
	;; 00000001111111111111222222222222222233334444444444555555555566666666667777777777
	;; Cpy/Paste/Clr (Trk) Cpy/Paste/Clr (Ptn) Undo                         Mute UnMute
	;; 88888888889999999999AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDDEEEEEEEEEEFFFFFFFFFF

	;; for 2x16 LCD:
	;; 0000000000111111
	;; 0123456789012345
	;; <-------------->
	;; BD    UTILS     
	;; 0000000111111111
	;; Track copied    
	;; 2222222222333333


	;; print segments 0-15
	BRA_IFSET CS_MENU_REFRESH_ITEM_CTR, 3, ACCESS, CS_M_UTILS_Tick_89ABCDEF

	movf	CS_MENU_REFRESH_ITEM_CTR, W
	andlw	0x07
	JUMPTABLE_2BYTES_UNSECURE
	rgoto	CS_M_UTILS_Tick_0
	rgoto	CS_M_UTILS_Tick_1
	rgoto	CS_M_UTILS_Tick_2
	rgoto	CS_M_UTILS_Tick_3
	rgoto	CS_M_UTILS_Tick_4
	rgoto	CS_M_UTILS_Tick_5
	rgoto	CS_M_UTILS_Tick_6
	rgoto	CS_M_UTILS_Tick_7

CS_M_UTILS_Tick_0
	;; print name of selected track
	movlw	0x00 + 0
	call	MIOS_LCD_CursorSet

	call	CS_M_HLP_GetSelectedTrk
	call	SEQ_TRK_PrnName	; (6 characters)

	rgoto	CS_M_UTILS_Tick_Cont

CS_M_UTILS_Tick_1_STR	STRING 14, 0x00 + 6, "UTILS         "
CS_M_UTILS_Tick_1
	TABLE_ADDR CS_M_UTILS_Tick_1_STR
	call	MIOS_LCD_PrintString
	rgoto	CS_M_UTILS_Tick_Cont

CS_M_UTILS_Tick_2_TABLE
	db	"Track copied    "
	db	"Track pasted    "
	db	"Track cleared   "
	db	"<reserved>      "
	db	"Pattern copied  "
	db	"Pattern pasted  "
	db	"Pattern cleared "
	db	"<reserved>      "
	db	"--> Undo <--    "
	db	"<reserved>      "
	db	"<reserved>      "
	db	"<reserved>      "
	db	"<reserved>      "
	db	"<reserved>      "
	db	"Muted all Tracks"
	db	"Unmuted Tracks  "

CS_M_UTILS_Tick_2
	;; print last command
#if DEFAULT_LCD_WIDTH == 80
	movlw	0x00 + 20
#else
	movlw	0x40 + 0
#endif
	call	MIOS_LCD_CursorSet

	;; print 16 spaces if no command triggered yet
	incf	CS_MENU_CURSOR_POS, W
	bz	CS_M_UTILS_Tick_2_NoCmd
CS_M_UTILS_Tick_2_Cmd
	movf	CS_MENU_CURSOR_POS, W
	TABLE_ADDR_MUL_W CS_M_UTILS_Tick_2_TABLE, 16
	movlw	16
	call	MIOS_LCD_PrintPreconfString
	rgoto	CS_M_UTILS_Tick_Cont

CS_M_UTILS_Tick_2_NoCmd
	movlw	16
	call	SEQ_LCD_PrintSpaces
	rgoto	CS_M_UTILS_Tick_Cont

CS_M_UTILS_Tick_3
	;; print 4 spaces
	movlw	0x00 + 36
	call	MIOS_LCD_CursorSet
	movlw	4
	call	SEQ_LCD_PrintSpaces
	rgoto	CS_M_UTILS_Tick_Cont

CS_M_UTILS_Tick_4
CS_M_UTILS_Tick_5
CS_M_UTILS_Tick_6
CS_M_UTILS_Tick_7
#if DEFAULT_LCD_WIDTH == 80
	;; fill with spaces
	call	CS_M_HLP_Print10Spaces
#endif
	rgoto	CS_M_UTILS_Tick_Cont

CS_M_UTILS_Tick_89ABCDEF_STR
	db	"Cpy/Paste/Clr (Trk) Cpy/Paste/Clr (Ptn) Undo                         Mute UnMute"
CS_M_UTILS_Tick_89ABCDEF
#if DEFAULT_LCD_WIDTH == 80
	;; determine string offset
	movf	CS_MENU_REFRESH_ITEM_CTR, W
	andlw	0x07
	TABLE_ADDR_MUL_W CS_M_UTILS_Tick_89ABCDEF_STR, 10

	;; print 10 characters
	call	CS_M_HLP_Print10Chars
#endif
	;;  	rgoto	CS_M_UTILS_Tick_Cont


CS_M_UTILS_Tick_Cont
	;; Tick function will be called 16 times
	incf	CS_MENU_REFRESH_ITEM_CTR, F
	BRA_IFCLR CS_MENU_REFRESH_ITEM_CTR, 4, ACCESS, CS_M_UTILS_Tick_End
	clrf	CS_MENU_REFRESH_ITEM_CTR
	;; 	rgoto	CS_M_PATTERN_Tick_End

CS_M_UTILS_Tick_End
	return

;; ==========================================================================

;; --------------------------------------------------------------------------
;;  Copy Track
;;  IN: SEQ_EVNTT: track to be copied into buffer
;; --------------------------------------------------------------------------
CS_M_UTILS_CopyTrack
	;; calculate pointer to track configuration
	lfsr	FSR0, SEQ_PATTERN_BUFFER
	SET_BSR	SEQ_BASE
	swapf	SEQ_EVNTT, W, BANKED
	andlw	0xf0
	addwf	FSR0L, F

	;; destination pointer
	lfsr	FSR1, SEQ_COPYPASTE_T_BUFFER

	;; copy track configuration
	clrf	PRODL
CS_M_UTILS_CopyTrackLoop1
	movff	POSTINC0, POSTINC1
	incf	PRODL, F
	BRA_IFCLR PRODL, 4, ACCESS, CS_M_UTILS_CopyTrackLoop1

	;; add offset to triggers
	movlw	0xf0
	addwf	FSR0L, F
	movlw	0x00
	addwfc	FSR0H, F

	;; copy triggers
	clrf	PRODL
CS_M_UTILS_CopyTrackLoop2
	movff	POSTINC0, POSTINC1
	incf	PRODL, F
	BRA_IFCLR PRODL, 4, ACCESS, CS_M_UTILS_CopyTrackLoop2

	;; notify that track copy&paste buffer is filled
	bsf	CS_STAT2, CS_STAT2_COPYPASTE_FILLED_T

	return


;; --------------------------------------------------------------------------
;;  Paste Track
;;  IN: SEQ_EVNTT: track to be copied into buffer
;; --------------------------------------------------------------------------
CS_M_UTILS_PasteTrack
	;; branch to clear function if copy&paste buffer not filled
	BRA_IFCLR CS_STAT2, CS_STAT2_COPYPASTE_FILLED_T, ACCESS, CS_M_UTILS_ClearTrack

	;; update undo buffer before changing data
	rcall	CS_M_UTILS_UndoUpdate

	;; source pointer
	lfsr	FSR0, SEQ_COPYPASTE_T_BUFFER

	;; calculate pointer to track configuration
	lfsr	FSR1, SEQ_PATTERN_BUFFER
	SET_BSR	SEQ_BASE
	swapf	SEQ_EVNTT, W, BANKED
	andlw	0xf0
	addwf	FSR1L, F

	;; copy track configuration
	clrf	PRODL
CS_M_UTILS_PasteTrackLoop1
	movff	POSTINC0, POSTINC1
	incf	PRODL, F
	BRA_IFCLR PRODL, 4, ACCESS, CS_M_UTILS_PasteTrackLoop1

	;; add offset to triggers
	movlw	0xf0
	addwf	FSR1L, F
	movlw	0x00
	addwfc	FSR1H, F

	;; copy triggers
	clrf	PRODL
CS_M_UTILS_PasteTrackLoop2
	movff	POSTINC0, POSTINC1
	incf	PRODL, F
	BRA_IFCLR PRODL, 4, ACCESS, CS_M_UTILS_PasteTrackLoop2

	;; restore MIDI channel/port/note (I find it better, when such settings won't be overwritten)
	rcall	CS_M_UTILS_Hlp_RestoreMIDI

	;; notify that track copy&paste buffer is filled
	bsf	CS_STAT2, CS_STAT2_COPYPASTE_FILLED_T

	return


;; --------------------------------------------------------------------------
;;  Clear Track
;;  IN: SEQ_EVNTT: track to be copied into buffer
;; --------------------------------------------------------------------------
CS_M_UTILS_ClearTrack
	;; update undo buffer before changing data
	rcall	CS_M_UTILS_UndoUpdate

	;; load preset of specific track
	movff	SEQ_EVNTT, WREG
	call	SEQ_BANK_LoadPresetTrk

	;; clear triggers
	lfsr	FSR1, SEQ_TRG0
	movff	SEQ_EVNTT, WREG
	mullw	SEQ_TRGRECORD_LENGTH
	movf	PRODL, W
	addwf	FSR1L, F
	movf	PRODH, W
	addwfc	FSR1H, F

	movlw	SEQ_TRGRECORD_LENGTH
	movwf	PRODL
CS_M_UTILS_ClearTrackLoop
	clrf	POSTINC1
	decfsz	PRODL, F
	rgoto	CS_M_UTILS_ClearTrackLoop
	
	;; restore MIDI channel/port/note (I find it better, when such settings won't be overwritten)
	rcall	CS_M_UTILS_Hlp_RestoreMIDI

	return


;; --------------------------------------------------------------------------
;;  Copy Pattern
;; --------------------------------------------------------------------------
CS_M_UTILS_CopyPattern
	SET_BSR	SEQ_BASE

	;; notify that pattern copy&paste buffer is filled
	bsf	CS_STAT2, CS_STAT2_COPYPASTE_FILLED_P

	;; copy pattern into copypaste buffer
	lfsr	FSR0, SEQ_PATTERN_BUFFER
	lfsr	FSR1, SEQ_COPYPASTE_P_BUFFER
	rcall	CS_M_UTILS_Hlp_Copy512

	return


;; --------------------------------------------------------------------------
;;  Paste Pattern
;; --------------------------------------------------------------------------
CS_M_UTILS_PastePattern
	SET_BSR	SEQ_BASE

	;; branch to clear function if copy&paste buffer not filled
	BRA_IFCLR CS_STAT2, CS_STAT2_COPYPASTE_FILLED_P, ACCESS, CS_M_UTILS_ClearPattern

	;; update undo buffer before changing data
	rcall	CS_M_UTILS_UndoUpdate

	;; copy copypaste buffer into pattern
	lfsr	FSR0, SEQ_COPYPASTE_P_BUFFER
	lfsr	FSR1, SEQ_PATTERN_BUFFER
	rcall	CS_M_UTILS_Hlp_Copy512

	;; restore MIDI channel/port/note (I find it better, when such settings won't be overwritten)
	rcall	CS_M_UTILS_Hlp_RestoreMIDI

	return


;; --------------------------------------------------------------------------
;;  Clear Pattern
;; --------------------------------------------------------------------------
CS_M_UTILS_ClearPattern
	;; update undo buffer before changing data
	rcall	CS_M_UTILS_UndoUpdate

	;; load preset
	call	SEQ_BANK_LoadPreset

	;; clear triggers
	lfsr	FSR1, SEQ_TRG0
CS_M_UTILS_ClearPatternLoop
	clrf	POSTINC1
	movf	FSR1L, W
	bnz	CS_M_UTILS_ClearPatternLoop

	;; restore MIDI channel/port/note (I find it better, when such settings won't be overwritten)
	rcall	CS_M_UTILS_Hlp_RestoreMIDI

	return


;; --------------------------------------------------------------------------
;;  Undo
;; --------------------------------------------------------------------------
CS_M_UTILS_Undo
	SET_BSR	SEQ_BASE

	;; exit if undo buffer not filled
	btfss	CS_STAT2, CS_STAT2_UNDO_FILLED
	return

	;; copy undo buffer into pattern
	lfsr	FSR0, SEQ_UNDO_BUFFER
	lfsr	FSR1, SEQ_PATTERN_BUFFER
	rcall	CS_M_UTILS_Hlp_Copy512

	return


;; --------------------------------------------------------------------------
;;  Update Undo Buffer
;; --------------------------------------------------------------------------
CS_M_UTILS_UndoUpdate
	SET_BSR	SEQ_BASE

	;; copy pattern into undo buffer
	lfsr	FSR0, SEQ_PATTERN_BUFFER
	lfsr	FSR1, SEQ_UNDO_BUFFER
	rcall	CS_M_UTILS_Hlp_Copy512

	;; notify that undo buffer is filled
	bsf	CS_STAT2, CS_STAT2_UNDO_FILLED

	return

;; --------------------------------------------------------------------------
;;  Help Function which copies 512 bytes
;;  IN: Source Pointer in FSR0, Destination Pointer in FSR1
;; --------------------------------------------------------------------------
CS_M_UTILS_Hlp_Copy512
	clrf	PRODL
	clrf	PRODH
CS_M_UTILS_Hlp_Copy512Loop
	movff	POSTINC0, POSTINC1
	incf	PRODL, F
	skpnz
	incf	PRODH, F
	BRA_IFCLR PRODH, 1, ACCESS, CS_M_UTILS_Hlp_Copy512Loop
	return


;; --------------------------------------------------------------------------
;;  Help Function to restore MIDI settings from UNDO buffer
;; --------------------------------------------------------------------------
CS_M_UTILS_Hlp_RestoreMIDI
	lfsr	FSR0, SEQ_UNDO_BUFFER
	lfsr	FSR1, SEQ_PATTERN_BUFFER

	;; for all 16 tracks
	clrf	PRODL
CS_M_UTILS_Hlp_RestoreMIDILoop
	movlw	SEQ_TRKCHNx	; MIDI channel and port
	movff	PLUSW0, TABLAT
	movff	TABLAT, PLUSW1

	movlw	SEQ_TRKNOTEx	; MIDI Note
	movff	PLUSW0, TABLAT
	movff	TABLAT, PLUSW1

	;; TRKVELx and TRKVELAx could be restored as well

	;; switch to next track
	movlw	SEQ_TRKRECORD_LENGTH
	addwf	FSR0L, F
	addwf	FSR1L, F

	;; loop over all 16 tracks
	incf	PRODL, F
	BRA_IFCLR PRODL, 4, ACCESS, CS_M_UTILS_Hlp_RestoreMIDILoop

	return


;; --------------------------------------------------------------------------
;;  Mute All Tracks
;; --------------------------------------------------------------------------
CS_M_UTILS_MuteAll
	;; mute all tracks
	SET_BSR	SEQ_BASE
	setf	SEQ_TRKS_MUTED0, BANKED
	setf	SEQ_TRKS_MUTED1, BANKED
	return


;; --------------------------------------------------------------------------
;;  UnMute All Tracks
;; --------------------------------------------------------------------------
CS_M_UTILS_UnMuteAll
	;; unmute all tracks
	SET_BSR	SEQ_BASE
	clrf	SEQ_TRKS_MUTED0, BANKED
	clrf	SEQ_TRKS_MUTED1, BANKED
	return
