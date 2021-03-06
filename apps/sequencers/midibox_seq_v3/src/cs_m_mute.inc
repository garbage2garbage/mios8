; $Id$
;
; MBSEQ Menu "Mute Tracks"
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
;;     should return the GP LED values in
;;     CS_MENU_GP_OVERLAY_DOUT_SR[01]
;; --------------------------------------------------------------------------
CS_M_MUTE_GP_Callback
	;; do nothing if button has been depressed
	btfsc	MIOS_PARAMETER2, 0
	return

	;; branch depending on Mute Button status
	SET_BSR	SEQ_BASE
	BRA_IFSET SEQ_MODE1, SEQ_MODE1_MUTE_HOLD, BANKED, CS_M_MUTE_GP_Callback_Sel

CS_M_MUTE_GP_Callback_Mute
	;; toggle mute flag
	lfsr	FSR1, SEQ_TRKS_MUTED0
	btfsc	CS_STAT3, CS_STAT3_SELECT_PRESSED
	lfsr	FSR1, SEQ_TRKS_MUTED0_REQ

	btfsc	MIOS_PARAMETER1, 3
	movf	POSTINC1, W	; increment pointer if track > 8
	
	movf	MIOS_PARAMETER1, W
	call	MIOS_HLP_GetBitORMask
	xorwf	INDF1, F

	rgoto	CS_M_MUTE_GP_Callback_End

CS_M_MUTE_GP_Callback_Sel
	;; if multi selection not set (will be set after the first selection), clear all track selections
	BRA_IFSET SEQ_MODE1, SEQ_MODE1_MUTE_HOLD_MULTISEL, BANKED, CS_M_MUTE_GP_Callback_SelNot1st
CS_M_MUTE_GP_Callback_Sel1st
	bsf	SEQ_MODE1, SEQ_MODE1_MUTE_HOLD_MULTISEL, BANKED	; arm multiselection flag
	movlw	0xf0
	movwf	SEQ_SELECTED_TRKS_G0, BANKED
	movwf	SEQ_SELECTED_TRKS_G1, BANKED
	movwf	SEQ_SELECTED_TRKS_G2, BANKED
	movwf	SEQ_SELECTED_TRKS_G3, BANKED
CS_M_MUTE_GP_Callback_SelNot1st

	;; toggle track selection depending on button number
	rrf	MIOS_PARAMETER1, W
	rrf	WREG, W
	andlw	0x03
	movwf	SEQ_SELECTED_GROUP, BANKED

	lfsr	FSR1, SEQ_SELECTED_TRKS_G0
	movf	SEQ_SELECTED_GROUP, W, BANKED
	addwf	FSR1L, F

	movf	MIOS_PARAMETER1, W
	andlw	0x03
	call	MIOS_HLP_GetBitORMask
	xorwf	INDF1, F
	movlw	0xf0		; (for correct function of the track buttons - no multi selections!)
	iorwf	INDF1, F

	;; request display re-initisation to update the marker
	bsf	CS_STAT, CS_STAT_DISPLAY_INIT_REQ
	

	;; 	rgoto	CS_M_MUTE_GP_Callback_End
	
CS_M_MUTE_GP_Callback_End
	;; 	rgoto	CS_M_MUTE_UpdateGPLEDs

;; --------------------------------------------------------------------------
CS_M_MUTE_UpdateGPLEDs
	;; branch depending on Mute Button status
	SET_BSR	SEQ_BASE
	BRA_IFSET SEQ_MODE1, SEQ_MODE1_MUTE_HOLD, BANKED, CS_M_MUTE_UpdateGPLEDs_Sel
CS_M_MUTE_UpdateGPLEDs_Mute
	;; don't flash LEDs
	bsf	MB_STAT, MB_STAT_DONT_FLASH_R_GP_DOUT
	bsf	MB_STAT, MB_STAT_DONT_FLASH_L_GP_DOUT

	BRA_IFSET CS_STAT3, CS_STAT3_SELECT_PRESSED, ACCESS, CS_M_MUTE_UpdateGPLEDs_MuteSyn
	movff	SEQ_TRKS_MUTED0, CS_MENU_GP_OVERLAY_DOUT_SR0
	movff	SEQ_TRKS_MUTED1, CS_MENU_GP_OVERLAY_DOUT_SR1
	return

CS_M_MUTE_UpdateGPLEDs_MuteSyn
	movff	SEQ_TRKS_MUTED0_REQ, CS_MENU_GP_OVERLAY_DOUT_SR0
	movff	SEQ_TRKS_MUTED1_REQ, CS_MENU_GP_OVERLAY_DOUT_SR1
	return

CS_M_MUTE_UpdateGPLEDs_Sel
	;; flash LEDs
	bcf	MB_STAT, MB_STAT_DONT_FLASH_R_GP_DOUT
	bcf	MB_STAT, MB_STAT_DONT_FLASH_L_GP_DOUT

	;; light up selected tracks
	movf	SEQ_SELECTED_TRKS_G0, W, BANKED
	andlw	0x0f
	movwf	CS_MENU_GP_OVERLAY_DOUT_SR0

	swapf	SEQ_SELECTED_TRKS_G1, W, BANKED
	andlw	0xf0
	iorwf	CS_MENU_GP_OVERLAY_DOUT_SR0, F

	movf	SEQ_SELECTED_TRKS_G2, W, BANKED
	andlw	0x0f
	movwf	CS_MENU_GP_OVERLAY_DOUT_SR1

	swapf	SEQ_SELECTED_TRKS_G3, W, BANKED
	andlw	0xf0
	iorwf	CS_MENU_GP_OVERLAY_DOUT_SR1, F

	return


;; --------------------------------------------------------------------------
;;  Select routine is called when the select button has been pressed
;; --------------------------------------------------------------------------
CS_M_MUTE_Select
	;; enter simultaneous selection mode if select button pressed
	;; change mutes simultaneously if select button released
	
	;; select/deselect CS_MIXER_PAGE[7] (utility page) depending on button
	btfsc	MIOS_PARAMETER2, 0
	bcf	CS_STAT3, CS_STAT3_SELECT_PRESSED
	btfss	MIOS_PARAMETER2, 0
	bsf	CS_STAT3, CS_STAT3_SELECT_PRESSED

	;; branch depending on state
	BRA_IFCLR CS_STAT3, CS_STAT3_SELECT_PRESSED, ACCESS, CS_M_MUTE_Select_0
CS_M_MUTE_Select_1
	;; transfer current mute state into _REQ variables
	movff	SEQ_TRKS_MUTED0, SEQ_TRKS_MUTED0_REQ
	movff	SEQ_TRKS_MUTED1, SEQ_TRKS_MUTED1_REQ
	return

CS_M_MUTE_Select_0
	;; transfer requested mute state into MUTED variables
	movff	SEQ_TRKS_MUTED0_REQ, SEQ_TRKS_MUTED0
	movff	SEQ_TRKS_MUTED1_REQ, SEQ_TRKS_MUTED1
	return


;; --------------------------------------------------------------------------
;;  Menu Init routine is called when menu page should be initialized
;; --------------------------------------------------------------------------
CS_M_MUTE_Init
	;; no parameter table!

	;; allow fast display update
	bsf	CS_STAT2, CS_STAT2_ALLOW_FAST_DISP_UPDATE

	;; clear state of select button
	bcf	CS_STAT3, CS_STAT3_SELECT_PRESSED

	;; install callback function for general purpose buttons, used to mute/unmute the tracks here
	TABLE_ADDR CS_M_MUTE_GP_Callback
	call	CS_MENU_SetMenuGPCallbackHook
	rgoto	CS_M_MUTE_UpdateGPLEDs


;; --------------------------------------------------------------------------
;;  Menu Tick routine is called on every refresh cycle
;; --------------------------------------------------------------------------
CS_M_MUTE_Tick
	;; fast refresh requested? Only used for meters
	BRA_IFSET CS_STAT2, CS_STAT2_FAST_DISPLAY_UPDATE, ACCESS, CS_M_MUTE_Tick_Fast

CS_M_MUTE_Tick_Slow
	;; init horizontal bars (if required - function breaks if charset already uploaded)
	movlw	CS_MENU_CHARSET_HBARS
	call	CS_SPECIAL_CHARS_Init

	;; print track numbers in first line
	clrf	TMP1		; set TMP1.0 if track selected
	SET_BSR	SEQ_BASE
	lfsr	FSR1, SEQ_SELECTED_TRKS_G0
	rrf	CS_MENU_REFRESH_ITEM_CTR, W
	rrf	WREG, W
	andlw	0x03
	addwf	FSR1L, F

	movf	CS_MENU_REFRESH_ITEM_CTR, W
	andlw	0x03
	call	MIOS_HLP_GetBitORMask
	andwf	INDF1, W
	bz	CS_M_MUTE_Tick_NotSelected
	bsf	TMP1, 0
CS_M_MUTE_Tick_NotSelected
	
	movf	CS_MENU_REFRESH_ITEM_CTR, W	; set cursor position
	andlw	0x07
	mullw	5
	movf	PRODL, W
	addlw	0x00 + 1
	btfsc	CS_MENU_REFRESH_ITEM_CTR, 3
	addlw	0x80
	call	MIOS_LCD_CursorSet

	;; if SELECT button pressed: flash potential mute change
	BRA_IFCLR CS_STAT3, CS_STAT3_SELECT_PRESSED, ACCESS, CS_M_MUTE_Tick_NoFlash
	BRA_IFSET CS_STAT, CS_STAT_CURSOR_FLASH, ACCESS, CS_M_MUTE_Tick_NoFlash
CS_M_MUTE_Tick_Flash
	movlw	5
	call	SEQ_LCD_PrintSpaces
	rgoto	CS_M_MUTE_Tick_Slow_End

CS_M_MUTE_Tick_NoFlash
	movlw	'>'		; mark track if selected
	btfss	TMP1, 0
	movlw	' '
	call	MIOS_LCD_PrintChar

	incf	CS_MENU_REFRESH_ITEM_CTR, W	; print track number
	call	MIOS_LCD_PrintBCD2

	movlw	'<'		; mark track if selected
	btfss	TMP1, 0
	movlw	' '
	call	MIOS_LCD_PrintChar

CS_M_MUTE_Tick_Slow_End

CS_M_MUTE_Tick_Fast
	;; print muted tracks at second line
	movf	CS_MENU_REFRESH_ITEM_CTR, W	; set cursor position
	andlw	0x07
	mullw	5
	movf	PRODL, W
	addlw	0x40 + 0
	btfsc	CS_MENU_REFRESH_ITEM_CTR, 3
	addlw	0x80
	call	MIOS_LCD_CursorSet

	;; print "Mute" if muted, else print a nice horizontal meter for track status
	SET_BSR	SEQ_BASE
	movf	SEQ_TRKS_MUTED0, W, BANKED
	btfsc	CS_MENU_REFRESH_ITEM_CTR, 3
	movf	SEQ_TRKS_MUTED1, W, BANKED
	movwf	TMP1

	BRA_IFCLR CS_STAT3, CS_STAT3_SELECT_PRESSED, ACCESS, CS_M_MUTE_Tick_NoSynReq
CS_M_MUTE_Tick_SynReq
	movff	TMP1, PRODL
	movf	SEQ_TRKS_MUTED0_REQ, W, BANKED
	btfsc	CS_MENU_REFRESH_ITEM_CTR, 3
	movf	SEQ_TRKS_MUTED1_REQ, W, BANKED
	movwf	TMP1

	;; flash if mute state different (has changed while select button pressed)
	xorwf	PRODL, W
	movwf	PRODH
	movf	CS_MENU_REFRESH_ITEM_CTR, W
	call	MIOS_HLP_GetBitORMask
	andwf	PRODH, W
	bz	CS_M_MUTE_Tick_SynReq_Cont


	;; mute state different -> flash it
	BRA_IFSET CS_STAT, CS_STAT_CURSOR_FLASH, ACCESS, CS_M_MUTE_Tick_SynReq_Cont
	movlw	5
	call	SEQ_LCD_PrintSpaces
	rgoto	CS_M_MUTE_Tick_Cont

CS_M_MUTE_Tick_NoSynReq
CS_M_MUTE_Tick_SynReq_Cont
	movf	CS_MENU_REFRESH_ITEM_CTR, W
	call	MIOS_HLP_GetBitORMask
	andwf	TMP1, W
	bz	CS_M_MUTE_Tick_NotMuted
CS_M_MUTE_Tick_Muted
	movlw	'M'
	call	MIOS_LCD_PrintChar
	movlw	'u'
	call	MIOS_LCD_PrintChar
	movlw	't'
	call	MIOS_LCD_PrintChar
	movlw	'e'
	call	MIOS_LCD_PrintChar
	movlw	' '
	call	MIOS_LCD_PrintChar
	rgoto	CS_M_MUTE_Tick_Cont

CS_M_MUTE_Tick_NotMuted
	;; print meter (counter is decremented by cs_menu_timer.inc, and set within seq_core.inc)
	lfsr	FSR1, CS_MENU_METER_CTR_BEGIN
	movf	CS_MENU_REFRESH_ITEM_CTR, W
	movf	PLUSW1, W
	call	SEQ_LCD_PrnHBar

CS_M_MUTE_Tick_Cont
	;; Tick function will be called 16 times
	incf	CS_MENU_REFRESH_ITEM_CTR, F
	BRA_IFCLR CS_MENU_REFRESH_ITEM_CTR, 4, ACCESS, CS_M_MUTE_Tick_End
	clrf	CS_MENU_REFRESH_ITEM_CTR
	;; 	rgoto	CS_M_MUTE_Tick_End

CS_M_MUTE_Tick_End
	return

;; ==========================================================================

