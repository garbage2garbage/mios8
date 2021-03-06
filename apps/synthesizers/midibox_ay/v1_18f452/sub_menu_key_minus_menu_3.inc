;; sub_menu_key_minus_menu_3.inc


;; --------[MINUS @ MAIN MENU3]------------------
;; JUMPED IN HERE FROM sub_menu_key_minus.inc

MINUS_KEY_SUBROUTINE_AT_MAIN_MENU3
	;; MAIN MENU3 = MIXER MENU
	;; MIX CH ABC + ADD NOISE TO CH ABC
	;; MINUS HAD BEEN PRESSED

	;; 1) CHECK WHICH ITEM (AY REG) IS 
	;; IN EDITING MODE "*"
	;; VIA AY_LCD_COURSER_POS_MAIN_MENU_ABC_NOISE
	;;
	;; 2) DEC ITEM 



;; --[ 1) CHECK ITEM]-------

	;; CHECK LOCATION VIA EDITING MODE "*"
	;; COPY THE VALUE OF EDITING MODE TO MIOS_PARAMETER1
	movff 	AY_LCD_COURSER_POS_MAIN_MENU_ABC_NOISE, MIOS_PARAMETER1

LABEL_AY_SUB_MENU_MINUS_MAIN_MENU3_CHK_ITEM4	
	;; ITEM4 = NOISE PERIOD IS THE ONLY POS. WHRER MINUS
	;; IS NEEDED FOR DEC THE NOISE PERIOD, SO CHECK
	;; IF THE EDITING MODE POS "*" = 4
	movlw 	MENU_ITEM_POS4
	cpfseq 	MIOS_PARAMETER1 ;; EDITING MODE ITEM  = 4?

		;; NO, SO QUIT
		goto LABEL_MAIN_MENUE_SWITCH

		;; YES
		rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU3_DEC_ITEM4	

;;---[ 2) INC ITEM [MAIN MENU3 - ITEM4 [NOISE PERIOD]]]--------
LABEL_AY_SUB_MENU_MINUS_MAIN_MENU3_DEC_ITEM4
	
	;; DEC ITEM4
	;; ITEM4 => AY REG 6 = RANGE BIT0-4 (!)
	;; => RANGE 0-31 DEC.
	;; => RANGE 0-1F  HEX.
	;;
	;; Note: 0 on LCD = 31 @ AY CHIP REG =  Lowest Noise PERIOD frequency
	;; 	31 on LCD =  0 @ AY CHIP REG =  Highest Noise PERIOD frequency
	
		;; CHEK ITEM VALUE 
		;; ITEM4 = HAS 5BIT = 0x1F = 31 DEC
		;; compare f with WREG, skip IF >
		;; AY REG > 0x1E? (dec. 31)
		movlw 	0x1E
		cpfsgt 	AY_R6_NOISE_PERIOD
		
			;; NO - OK GO ON
			rgoto LABEL_AY_SUB_MENU_MINUS_MAIN_MENU3_DEC_ITEM4_OK

			;; YES - SO QUIT HERE
			goto LABEL_MAIN_MENUE_SWITCH
		
		
LABEL_AY_SUB_MENU_MINUS_MAIN_MENU3_DEC_ITEM4_OK

	;; DONT BE CONFUSED:
	;; DEC = FOR LCD!
	;; INC = FOR AY_R6_NOISE_PERIOD => AY REG.
	;; ITEM = ITEM +1
	incf AY_R6_NOISE_PERIOD, F
	
	;; PREPARE ITEM DATA FOR TRANSFERE TO AY CHIP VIA ay_sr.inc
	;; --------------------------------------------------------
	;; WRITE AY REG *ADRESS* TO AY_REG_ADDRESS FOR => AY_SR_Write
	movlw AY_CHIP_ADR_06_NOISE_PERIOD ; ADRESS => AY REGISTER
	movwf AY_REG_ADDRESS 		  ; ADDRESS FOR => AY_SR_Write
	;; WRITE AY REG *DATA* TO AY_REG_DATA FOR => AY_SR_Write
	movff AY_R6_NOISE_PERIOD, AY_REG_DATA 
	
	;; WRITING 8BIT DATA (AY_REG_ADDRESS, AY_REG_DATA)TO AY REG(X) ROUTINE
	;; @ay_sr.inc
	call LABEL_AY_SR_Write
	

		;; SWITCH MAIN MENU TO: MAIN MENU 3
		goto LABEL_MAIN_MENUE_SWITCH

