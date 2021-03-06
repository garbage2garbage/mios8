;; sub_menu_key_minus_menu_4.inc

;; --------[MINUS @ MAIN MENU4]------------------
;; JUMPED IN HERE FROM sub_menu_key_minus.inc
MINUS_KEY_SUBROUTINE_AT_MAIN_MENU4
	
	;; MAIN MENU4 = AMPLITUDE/VOLUME MENU
	;; MINUS HAD BEEN PRESSED
	;;
	;; 1) CHECK WHICH ITEM (AY REG) IS 
	;; IN EDITING MODE "*"
	;; VIA AY_LCD_COURSER_POS_MAIN_MENU_ABC_TUNE
	;;
	;; 2) DEC ITEM 

;; --[ 1) CHECK ITEM]-------

	;; CHECK LOCATION VIA EDITING MODE "*"
	;; COPY THE VALUE OF EDITING MODE TO  MIOS_PARAMETER1
	movff 	AY_LCD_COURSER_POS_MAIN_MENU_AMPLITUDE, MIOS_PARAMETER1

LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_CHK_ITEM1	
	movlw 	MENU_ITEM_POS1
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 1?

		;; NO
		rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_CHK_ITEM2

		;; YES
		rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM1
	

LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_CHK_ITEM2

	movlw 	MENU_ITEM_POS2
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 2?

		;; NO
		rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_CHK_ITEM3

		;; YES
		rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM2	


LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_CHK_ITEM3
	
	movlw 	MENU_ITEM_POS3
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 3?

		;; NO? - No Item Left Over - So Quit Here
		goto LABEL_MAIN_MENUE_SWITCH

		;; YES
		rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM3	




;;---[ 2) DEC ITEM [MAIN MENU4 - [1-3]]]--------

;;---[ 2) DEC ITEM1 [MAIN MENU4]--------
LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM1
	;; INC ITEM1
	;; ITEM1 => AY REG 8 = Volume CH. A 4BIT - LOW NIBBLE (!)
	;; => RANGE 0-15 DEC.
	;; => RANGE 0x00-0x0F  HEX

		;; CHEK ITEM VALUE 
		;; ITEM1 = 4BIT = 0x0F = 15 DEC
		;; compare f with WREG, skip if f = 0
		;; JUST TAKE A THE LO NIBBLE !
		movlw	NIBBLE_B00001111
		andwf	AY_R8_CH_A_AMPLITUDE,W
		movwf	MIOS_PARAMETER1 ;; LOW NIBBLE OF AY_R8_CH_A_AMPLITUDE (0x00 - 0x0F)
		
		clrw	
		cpfseq 	MIOS_PARAMETER1 ;; IS LOW NIBBLE OF AY_R8_CH_A_AMPLITUDE
					;; = 1 ? 
		
			;; NO
			rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM1_OK

			;; YES - LOW NIBBLE OF AY_R8_CH_A_AMPLITUDE = 0 DEC.
			;; QUIT HERE
			goto LABEL_MAIN_MENUE_SWITCH



LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM1_OK
	;; ITEM = ITEM -1
	decf AY_R8_CH_A_AMPLITUDE, F
	
	;; PREPARE ITEM DATA FOR TRANSFERE TO AY CHIP VIA ay_sr.inc
	;; --------------------------------------------------------
	;; WRITE AY REG *ADRESS* TO AY_REG_ADDRESS FOR => AY_SR_Write
	movlw AY_CHIP_ADR_08_TONE_A_VOLUME_ENV_MODE_ON_OFF 
	movwf AY_REG_ADDRESS 		; ADDRESS FOR => AY_SR_Write
	;; WRITE AY REG *DATA* TO AY_REG_DATA FOR => AY_SR_Write
	movff AY_R8_CH_A_AMPLITUDE, AY_REG_DATA 
	
	;; WRITING 8BIT DATA (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE
	call LABEL_AY_SR_Write
		
		;; SWITCH MAIN MENU TO: MAIN MENU 4
		goto LABEL_MAIN_MENUE_SWITCH


;;---[ 2) INC ITEM2 [MAIN MENU4]--------
LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM2

	;; INC ITEM2
	;; ITEM2 => AY REG 9 = Volume CH. B 4BIT - LOW NIBBLE (!)
	;; => RANGE 0-15 DEC.
	;; => RANGE 0-F  HEX

		;; CHEK ITEM VALUE 
		;; ITEM2 = LOW NIBBLE (4BIT)
		;; 0x00 - 0x0F HEX = 0 - 15 DEC
		;; compare f with WREG, skip if f = 0
		;; JUST TAKE A THE LO NIBBLE
		movlw	NIBBLE_B00001111
		andwf	AY_R9_CH_B_AMPLITUDE,W
		movwf	MIOS_PARAMETER1 ;; LOW NIBBLE OF AY_R9_CH_B_AMPLITUDE (0x00 - 0x0F)
		
		clrw	
		cpfseq 	MIOS_PARAMETER1 ;; IS LOW NIBBLE OF AY_R9_CH_B_AMPLITUDE
					;; = 0 ? 
		
			;; NO
			rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM2_OK

			;; YES - LOW NIBBLE OF AY_R9_CH_B_AMPLITUDE = 0 DEC.
			;; SO QUIT HERE
			goto LABEL_MAIN_MENUE_SWITCH



LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM2_OK
	;; ITEM = ITEM -1
	decf AY_R9_CH_B_AMPLITUDE, F
	
	;; PREPARE ITEM DATA FOR TRANSFERE TO AY CHIP VIA ay_sr.inc
	;; --------------------------------------------------------
	;; WRITE AY REG *ADRESS* TO AY_REG_ADDRESS FOR => AY_SR_Write
	movlw AY_CHIP_ADR_09_TONE_B_VOLUME_ENV_MODE_ON_OFF
	movwf AY_REG_ADDRESS 		; ADDRESS FOR => AY_SR_Write
	;; WRITE AY REG *DATA* TO AY_REG_DATA FOR => AY_SR_Write
	movff AY_R9_CH_B_AMPLITUDE, AY_REG_DATA 
	
	;; WRITING 8BIT DATA (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE
	call LABEL_AY_SR_Write
		
		;; SWITCH MAIN MENU TO: MAIN MENU 4
		goto LABEL_MAIN_MENUE_SWITCH





;;---[ 2) INC ITEM3 [@MAIN MENU4]--------

LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM3
		
	;; INC ITEM3
	;; ITEM3 => AY REG 10 = Volume CH. C 4BIT - LOW NIBBLE (!)
	;; => RANGE 0-15 DEC.
	;; => RANGE 0-F  HEX

		;; CHEK ITEM VALUE 
		;; ITEM1 = 4BIT LOW NIBBLE => 0x00 - 0x0F = 0 - 15 DEC
		;; compare f with WREG, skip if f = 0
		;; JUST TAKE A THE LO NIBBLE
		movlw	NIBBLE_B00001111 ;; AND W WITH 00001111b
		andwf	AY_R10_CH_C_AMPLITUDE,W
		movwf	MIOS_PARAMETER1 ;; LOW NIBBLE OF AY_R8_CH_A_AMPLITUDE (0x00 - 0x0F)
		
		clrw	
		cpfseq 	MIOS_PARAMETER1 ;; IS LOW NIBBLE 
					;; = 0 ? 
		
			;; NO
			rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM3_OK

			;; YES - LOW NIBBLE = 0 
			;; QUIT HERE
			goto LABEL_MAIN_MENUE_SWITCH



LABEL_AY_SUB_MENU_MINUS_MAIN_MENU4_DEC_ITEM3_OK
	;; ITEM = ITEM -1
	decf AY_R10_CH_C_AMPLITUDE, F
	
	;; PREPARE ITEM DATA FOR TRANSFERE TO AY CHIP VIA ay_sr.inc
	;; --------------------------------------------------------
	;; WRITE AY REG *ADRESS* TO AY_REG_ADDRESS FOR => AY_SR_Write
	movlw AY_CHIP_ADR_10_TONE_C_VOLUME_ENV_MODE_ON_OFF
	movwf AY_REG_ADDRESS 		; ADDRESS FOR => AY_SR_Write
	;; WRITE AY REG *DATA* TO AY_REG_DATA FOR => AY_SR_Write
	movff AY_R10_CH_C_AMPLITUDE, AY_REG_DATA 
	
	;; WRITING 8BIT DATA (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE
	call LABEL_AY_SR_Write
	;; ---------------------------------------------------------
		

		;; SWITCH MAIN MENU TO: MAIN MENU 4
		goto LABEL_MAIN_MENUE_SWITCH



;; ------[END MINUS @ MAIN MENU4]
