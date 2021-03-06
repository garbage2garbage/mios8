; $Id$
;
; MIDIbox64E
; Presets (EEPROM/Flash Content)
;
; ==========================================================================
;
;  Copyright 1998-2003 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

        ERRORLEVEL      -220    ; suppress "Address exceeds maximum range for this processor."
	;; this is (unfortunately) required for gpasm


; ==========================================================================
;  Data structure:
;                      BankStick Addr.   Internal Addr.   
;   +---------------+  0xfff             not implemented
;   | Enc Strings   |  
;   +---------------+  0x800             not implemented
;   | Reserved      |  
;   +---------------+  0x700             -
;   | Configuration |
;   +---------------+  0x690             0x50 (EEPROM)
;   | Button Values |
;   +---------------+  0x680             0x40 (EEPROM)
;   | Enc Values    |
;   +---------------+  0x600             0x00 (EEPROM)
;   | LED Patterns  |
;   +---------------+  0x400             0x7a00 (FLASH)
;   | Enc Modes     |
;   +---------------+  0x300             0x7900 (FLASH)
;   | Button Events |
;   +---------------+  0x200             0x7800 (FLASH)
;   | Enc Events    |
;   +---------------+  0x000             0x7600 (FLASH)
;
;
; ==========================================================================

	org	0x07600		; enc/button events stored at the end of internal flash
	
;; This macro generates an ENC entry
;; Parameters: event_0, event_1, min_value, max_value
;; normaly we need 8 bits for every event byte, but since we are only able to 
;; embedd 7-bit events within a SysEx stream, the MSB is masked out. 
;; However, the MSB (bit 8) is 1 for every MIDI event (0x80-0xff), therefore 
;; this doesn't hurt. Simmlar approach for event_1: the MSB is 0 for every MIDI 
;; event (0x00-0x7f), so we can get rid of it.
ENCODER_ENTRY MACRO event_0, event_1, min, max
	db	event_0, event_1, min, max
	ENDM

;; This macro generates a BUTTON entry
;; Parameters: event_0, event_1, event_2, mode
BUTTON_ENTRY MACRO event_0, event_1, event_2, mode
	db	event_0, event_1, event_2, mode
	ENDM

;; This macro generates an encoder mode entry
;; Parameters: mode, speed, led pattern
ENCODER_MODE_ENTRY MACRO mode, speed, led_pattern
	db	(mode) | (speed), led_pattern
	ENDM

;; This macro generates a led pattern entry
;; Parameters: pattern
LED_ENTRY MACRO pattern
	db	((pattern)>>8)&0x7f, ((pattern)>>15)&1, (pattern)&0x7f, ((pattern)>>7)&1
	ENDM

;; This macro generates a enc label entry
;; Parameters: mode, str
ENC_LABEL_ENTRY MACRO mode, str
	db	str, mode
	ENDM

;; ---[ Controller Enc Bank ]------------------------------------------------
MB64E_Presets
MB64E_Presets_FLASH_Lower
MB64E_Presets_OffsetEncs
MB64E_Presets_OffsetEncsRge0		; preset: volume (Bn 07)
	ENCODER_ENTRY 0xb0, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xb1, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xb2, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xb3, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xb4, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xb5, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xb6, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xb7, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xb8, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xb9, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xba, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xbb, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xbc, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xbd, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xbe, 0x07, 0x00, 0x7f
	ENCODER_ENTRY 0xbf, 0x07, 0x00, 0x7f

MB64E_Presets_OffsetEncsRge1		; preset: panorama (Bn 0A)
	ENCODER_ENTRY 0xb0, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xb1, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xb2, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xb3, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xb4, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xb5, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xb6, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xb7, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xb8, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xb9, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xba, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xbb, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xbc, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xbd, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xbe, 0x0a, 0x00, 0x7f
	ENCODER_ENTRY 0xbf, 0x0a, 0x00, 0x7f

MB64E_Presets_OffsetEncsPge2		; preset: reverb (Bn 5B)
	ENCODER_ENTRY 0xb0, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xb1, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xb2, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xb3, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xb4, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xb5, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xb6, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xb7, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xb8, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xb9, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xba, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xbb, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xbc, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xbd, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xbe, 0x5b, 0x00, 0x7f
	ENCODER_ENTRY 0xbf, 0x5b, 0x00, 0x7f

MB64E_Presets_OffsetEncsRge3		; preset: chorus (Bn 5D)
	ENCODER_ENTRY 0xb0, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xb1, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xb2, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xb3, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xb4, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xb5, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xb6, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xb7, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xb8, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xb9, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xba, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xbb, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xbc, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xbd, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xbe, 0x5d, 0x00, 0x7f
	ENCODER_ENTRY 0xbf, 0x5d, 0x00, 0x7f

MB64E_Presets_OffsetEncsRge4		; preset: Variation (Bn 5E)
	ENCODER_ENTRY 0xb0, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xb1, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xb2, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xb3, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xb4, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xb5, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xb6, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xb7, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xb8, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xb9, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xba, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xbb, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xbc, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xbd, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xbe, 0x5e, 0x00, 0x7f
	ENCODER_ENTRY 0xbf, 0x5e, 0x00, 0x7f

MB64E_Presets_OffsetEncsRge5		; preset: CutOff (Bn 4A)
	ENCODER_ENTRY 0xb0, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xb1, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xb2, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xb3, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xb4, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xb5, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xb6, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xb7, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xb8, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xb9, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xba, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xbb, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xbc, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xbd, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xbe, 0x4a, 0x00, 0x7f
	ENCODER_ENTRY 0xbf, 0x4a, 0x00, 0x7f

MB64E_Presets_OffsetEncsRge6		; preset: Resonance (Bn 47)
	ENCODER_ENTRY 0xb0, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xb1, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xb2, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xb3, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xb4, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xb5, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xb6, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xb7, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xb8, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xb9, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xba, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xbb, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xbc, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xbd, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xbe, 0x47, 0x00, 0x7f
	ENCODER_ENTRY 0xbf, 0x47, 0x00, 0x7f

MB64E_Presets_OffsetEncsRge7		; preset: Modulation (Bn 01)
	ENCODER_ENTRY 0xb0, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xb1, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xb2, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xb3, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xb4, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xb5, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xb6, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xb7, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xb8, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xb9, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xba, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xbb, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xbc, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xbd, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xbe, 0x01, 0x00, 0x7f
	ENCODER_ENTRY 0xbf, 0x01, 0x00, 0x7f


MB64E_Presets_OffsetButtons
	;; DIN/DOUT group 0
	BUTTON_ENTRY 0x90, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x91, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x92, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x93, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x94, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x95, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x96, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x97, 0x30, 0x7f, 0x00

	;; DIN/DOUT group 1
	BUTTON_ENTRY 0x98, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x99, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x9a, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x9b, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x9c, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x9d, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x9e, 0x30, 0x7f, 0x00
	BUTTON_ENTRY 0x9f, 0x30, 0x7f, 0x00

	;; DIN/DOUT group 2
	BUTTON_ENTRY 0xff, 0x08, 0x41, 0x00	; SFB: select bank/group
	BUTTON_ENTRY 0xff, 0x08, 0x40, 0x00	; SFB: Select Parameter with encoder when hold
	BUTTON_ENTRY 0xff, 0x08, 0x11, 0x00	; SFB: Encoder in fast mode when hold
	BUTTON_ENTRY 0xff, 0x08, 0x21, 0x00	; SFB: Encoder in slow mode when hold
	BUTTON_ENTRY 0x94, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x95, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x96, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x97, 0x54, 0x7f, 0x00

	;; DIN/DOUT group 3
	BUTTON_ENTRY 0x98, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x99, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x9a, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x9b, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x9c, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x9d, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x9e, 0x54, 0x7f, 0x00
	BUTTON_ENTRY 0x9f, 0x54, 0x7f, 0x00

	;; DIN/DOUT group 4
	BUTTON_ENTRY 0x90, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x91, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x92, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x93, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x94, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x95, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x96, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x97, 0x3c, 0x7f, 0x00

	;; DIN/DOUT group 5
	BUTTON_ENTRY 0x98, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x99, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x9a, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x9b, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x9c, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x9d, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x9e, 0x3c, 0x7f, 0x00
	BUTTON_ENTRY 0x9f, 0x3c, 0x7f, 0x00

	;; DIN/DOUT group 6
	BUTTON_ENTRY 0x90, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x91, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x92, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x93, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x94, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x95, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x96, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x97, 0x48, 0x7f, 0x00

	;; DIN/DOUT group 7
	BUTTON_ENTRY 0x98, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x99, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x9a, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x9b, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x9c, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x9d, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x9e, 0x48, 0x7f, 0x00
	BUTTON_ENTRY 0x9f, 0x48, 0x7f, 0x00


MB64E_Presets_OffsetEncMode
	;; Encoder Page 0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0

	;; Encoder Page 1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_1

	;; Encoder Page 2
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0

	;; Encoder Page 3
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0

	;; Encoder Page 4
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0

	;; Encoder Page 5
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0

	;; Encoder Page 6
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0

	;; Encoder Page 7
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0
	ENCODER_MODE_ENTRY ENC_MODE_ABSOLUTE, ENC_MODE_SPEED_NORMAL, LEDRING_PATTERN_0

MB64E_Presets_OffsetLEDPatterns
	;; LED Pattern #1
	LED_ENTRY b'0000000000000001'
	LED_ENTRY b'0000000000000001'
	LED_ENTRY b'0000000000000011'
	LED_ENTRY b'0000000000000011'
	LED_ENTRY b'0000000000000011'
	LED_ENTRY b'0000000000000111'
	LED_ENTRY b'0000000000000111'
	LED_ENTRY b'0000000000000111'
	LED_ENTRY b'0000000000001111'
	LED_ENTRY b'0000000000001111'
	LED_ENTRY b'0000000000001111'
	LED_ENTRY b'0000000000011111'
	LED_ENTRY b'0000000000011111'
	LED_ENTRY b'0000000000011111'
	LED_ENTRY b'0000000000111111'
	LED_ENTRY b'0000000000111111'
	LED_ENTRY b'0000000000111111'
	LED_ENTRY b'0000000000111111'
	LED_ENTRY b'0000000001111111'
	LED_ENTRY b'0000000001111111'
	LED_ENTRY b'0000000001111111'
	LED_ENTRY b'0000000011111111'
	LED_ENTRY b'0000000011111111'
	LED_ENTRY b'0000000011111111'
	LED_ENTRY b'0000000111111111'
	LED_ENTRY b'0000000111111111'
	LED_ENTRY b'0000000111111111'
	LED_ENTRY b'0000001111111111'
	LED_ENTRY b'0000001111111111'
	LED_ENTRY b'0000001111111111'
	LED_ENTRY b'0000011111111111'
	LED_ENTRY b'0000011111111111'

	;; LED Pattern #2
	LED_ENTRY b'0000000000111111'
	LED_ENTRY b'0000000000111111'
	LED_ENTRY b'0000000000111110'
	LED_ENTRY b'0000000000111110'
	LED_ENTRY b'0000000000111110'
	LED_ENTRY b'0000000000111100'
	LED_ENTRY b'0000000000111100'
	LED_ENTRY b'0000000000111100'
	LED_ENTRY b'0000000000111000'
	LED_ENTRY b'0000000000111000'
	LED_ENTRY b'0000000000111000'
	LED_ENTRY b'0000000000110000'
	LED_ENTRY b'0000000000110000'
	LED_ENTRY b'0000000000110000'
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000001100000'
	LED_ENTRY b'0000000001100000'
	LED_ENTRY b'0000000001100000'
	LED_ENTRY b'0000000011100000'
	LED_ENTRY b'0000000011100000'
	LED_ENTRY b'0000000011100000'
	LED_ENTRY b'0000000111100000'
	LED_ENTRY b'0000000111100000'
	LED_ENTRY b'0000000111100000'
	LED_ENTRY b'0000001111100000'
	LED_ENTRY b'0000001111100000'
	LED_ENTRY b'0000001111100000'
	LED_ENTRY b'0000011111100000'
	LED_ENTRY b'0000011111100000'

	;; LED Pattern #3
	LED_ENTRY b'0000000000000001'
	LED_ENTRY b'0000000000000001'
	LED_ENTRY b'0000000000000001'
	LED_ENTRY b'0000000000000010'
	LED_ENTRY b'0000000000000010'
	LED_ENTRY b'0000000000000010'
	LED_ENTRY b'0000000000000100'
	LED_ENTRY b'0000000000000100'
	LED_ENTRY b'0000000000000100'
	LED_ENTRY b'0000000000001000'
	LED_ENTRY b'0000000000001000'
	LED_ENTRY b'0000000000001000'
	LED_ENTRY b'0000000000010000'
	LED_ENTRY b'0000000000010000'
	LED_ENTRY b'0000000000010000'
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000001000000'
	LED_ENTRY b'0000000001000000'
	LED_ENTRY b'0000000001000000'
	LED_ENTRY b'0000000010000000'
	LED_ENTRY b'0000000010000000'
	LED_ENTRY b'0000000010000000'
	LED_ENTRY b'0000000100000000'
	LED_ENTRY b'0000000100000000'
	LED_ENTRY b'0000000100000000'
	LED_ENTRY b'0000001000000000'
	LED_ENTRY b'0000001000000000'
	LED_ENTRY b'0000001000000000'
	LED_ENTRY b'0000010000000000'
	LED_ENTRY b'0000010000000000'
	LED_ENTRY b'0000010000000000'

	;; LED Pattern #4
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000000100000'
	LED_ENTRY b'0000000001110000'
	LED_ENTRY b'0000000001110000'
	LED_ENTRY b'0000000001110000'
	LED_ENTRY b'0000000001110000'
	LED_ENTRY b'0000000001110000'
	LED_ENTRY b'0000000001110000'
	LED_ENTRY b'0000000011111000'
	LED_ENTRY b'0000000011111000'
	LED_ENTRY b'0000000011111000'
	LED_ENTRY b'0000000011111000'
	LED_ENTRY b'0000000011111000'
	LED_ENTRY b'0000000011111000'
	LED_ENTRY b'0000000111111100'
	LED_ENTRY b'0000000111111100'
	LED_ENTRY b'0000000111111100'
	LED_ENTRY b'0000000111111100'
	LED_ENTRY b'0000000111111100'
	LED_ENTRY b'0000000111111100'
	LED_ENTRY b'0000001111111110'
	LED_ENTRY b'0000001111111110'
	LED_ENTRY b'0000001111111110'
	LED_ENTRY b'0000001111111110'
	LED_ENTRY b'0000001111111110'
	LED_ENTRY b'0000001111111110'	
	LED_ENTRY b'0000011111111111'
	LED_ENTRY b'0000011111111111'
	LED_ENTRY b'0000011111111111'
	LED_ENTRY b'0000011111111111'


	;; NOTE: in internal bank, all reads and writes from offset 0x600
	;; with be forwarded to the EEPROM address 0xf00000!
	;; by MB64E_BANK_Write, MB64E_BANK_Read

	org	0xf00000	; eeprom base address

MB64E_Presets_OffsetEncValues
	;; page 0
	db	0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f
	;; page 1
	db	0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40
	;; page 2
	db	0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40
	;; page 3
	db	0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40
	;; page 4
	db	0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40
	;; page 5
	db	0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40
	;; page 6
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	;; page 7
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

MB64E_Presets_OffsetButtonValues
	;; button:
	;;            6543         3210
	db	b'00001111', b'00001111' ; 1st SR
	db	b'00001111', b'00001111' ; 2nd SR
	db	b'00001111', b'00001111' ; 3rd SR
	db	b'00001111', b'00001111' ; 4th SR
	db	b'00001111', b'00001111' ; 5th SR
	db	b'00001111', b'00001111' ; 6th SR
	db	b'00001111', b'00001111' ; 7th SR
	db	b'00001111', b'00001111' ; 8th SR


;; ---[ Misc Configuration ]-------------------------------------------------
MB64E_Presets_OffsetGlobal
MB64E_Presets_OffsetMagicNumbers
	db	BANKSTICK_MAGIC0, BANKSTICK_MAGIC1	; don't change these values, required to identify bankstick format
MB64E_Presets_OffsetCFG
	;; note: since SysEx doesn't allow to transfer 8-bit values, they
	;; are splitted here: first byte is the low-nibble, second byte the high-nibble
MB64E_Presets_CFG0
	db	((DEFAULT_TOUCH_SENSOR_MODE&1) << MB64E_CFG0_TSMODE0) | (((DEFAULT_TOUCH_SENSOR_MODE>>1)&1) << MB64E_CFG0_TSMODE1) | (1 << MB64E_CFG0_MERGEROFF), 0x00
MB64E_Presets_CFG1
	db	0x00, 0x00
MB64E_Presets_BANKNAME
	db	'I','n','t','e','r','n','a','l',' ','B','a','n','k',' ',' ',' '
MB64E_Presets_RESERVED1
	db	0x00, 0x00
MB64E_Presets_RESERVED2
	db	0x00, 0x00
MB64E_Presets_RESERVED3
	db	0x00, 0x00
MB64E_Presets_RESERVED4
	db	0x00, 0x00
MB64E_Presets_RESERVED5
	db	0x00, 0x00
MB64E_Presets_RESERVED6
	db	0x00, 0x00
MB64E_Presets_RESERVED7
	db	0x00, 0x00
MB64E_Presets_RESERVED8
	db	0x00, 0x00
MB64E_Presets_TS_SENSITIVITY
	db	DEFAULT_TOUCH_SENSOR_SENSITIVITY, 0x00
MB64E_Presets_RESERVED9
	db	0x00, 0x00
MB64E_Presets_LED_MAP
	db	0x00, 0x00
	db	0x00, 0x00
	db	0x00, 0x00
	db	0x00, 0x00
	db	0x00, 0x00
	db	0x00, 0x00
	db	0x00, 0x00
	db	0x00, 0x00
MB64E_Presets_DISPLAY_PAGE
	db	0x00, 0x00
MB64E_Presets_MORPH_BANK
	db	0x00, 0x00
MB64E_Presets_GLOBAL_CHANNEL
	db	0x00, 0x00

	;; fill unused area
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

	;; these two entries cannot be overwritten via SysEx.
	;; it contains the device ID and the to-COM option
EEPROM_READONLY
	db	0x00, DEFAULT_DEVICE_ID
