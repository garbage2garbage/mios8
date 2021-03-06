; $Id$
;
; MBSEQ Menu "Track Direction"
;
; ==========================================================================
;
;  Copyright 1998-2006 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

;; --------------------------------------------------------------------------
;;  This table contains the edit values
;; --------------------------------------------------------------------------
CS_M_TRKDIR_PARAMETERS
 ;;			 CC/value				max	cursor/len	MenuParameterHook
 CS_MENU_PARAMETER_ENTRY SEQ_CC_OFFSET_DIRECTION,		0x03,	0x40, 10,	CS_M_TRKDIR_ValueChanged
 CS_MENU_PARAMETER_ENTRY -1,					0x03,   0x0f, 1,	CS_M_HLP_TrkChanged

;; --------------------------------------------------------------------------
;;  Menu Init routine is called when menu page should be initialized
;; --------------------------------------------------------------------------
CS_M_TRKDIR_Init
	;; install parameter table
	TABLE_ADDR CS_M_TRKDIR_PARAMETERS	; pointer to table
	movlw	2				; number of parameters
	call	CS_MENU_SetMenuParameterTable

	;; print static chars
	TABLE_ADDR CS_M_TRKDIR_STR
	goto	MIOS_LCD_PrintString

CS_M_TRKDIR_STR  STRING 14, 0x00, "Dir. of Track:"

;; --------------------------------------------------------------------------
;;  Menu Tick routine is called on every refresh cycle
;; --------------------------------------------------------------------------
CS_M_TRKDIR_Tick
	;; print track number
	call	CS_M_HLP_PrnTrkAt0F

	;; print trkdir name depending on selected track and direction at second line
	movlw	SEQ_CC_OFFSET_DIRECTION
	call	CS_M_HLP_TrkCC_Get
	movwf	TMP1

	movlw	0x40
	call	MIOS_LCD_CursorSet
	TABLE_ADDR CS_M_TRKDIR_NAME_TABLE	; initial pointer to table
	movf	TMP1, W
	mullw	CS_M_TRKDIR_NAME_LEN		; multiply with string len
	movf	PRODL, W			; add result to table pointer
	addwf	TBLPTRL, F
	movf	PRODH, W
	addwfc	TBLPTRH, F
	movlw	CS_M_TRKDIR_NAME_LEN		; finally print table entry
	call	MIOS_LCD_PrintPreconfString

	;; branch to the cursor handler
	goto	CS_MENU_CursorHandler

;; ==========================================================================

;; --------------------------------------------------------------------------
;;  This hook is called when the menu parameter value has been changed
;; --------------------------------------------------------------------------
CS_M_TRKDIR_ValueChanged
	movlw	SEQ_CC_OFFSET_DIRECTION
	goto	CS_M_HLP_TrkCC_Set

;; ==========================================================================

CS_M_TRKDIR_NAME_LEN		EQU	10	; 14 characters per entry
CS_M_TRKDIR_NAME_ENTRIES	EQU	4	; 4 entries
CS_M_TRKDIR_NAME_TABLE				; all entries are listed here
	de	"Forward   "
	de	"Backward  "
	de	"Ping Pong "
	de	"Random    "
