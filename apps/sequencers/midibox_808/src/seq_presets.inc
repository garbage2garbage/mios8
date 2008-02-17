; $Id$
;
; MIDIboxSEQ
; Presets (EEPROM content)
;
; Note: this file doesn't contain the predefined presets which can be 
; fetched from the track event configuration menu - they are located
; in seq_pinit.inc
;
; ==========================================================================
;
;  Copyright 1998-2006 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

        ERRORLEVEL      -220    ; suppress "Address exceeds maximum range for this processor."
	;; this is (unfortunately) required for gpasm


	org	0xf00000	; eeprom base address

SEQ_PRESET_PATTERN
#include "seq_preset_pattern.inc"

	org	0xf00200	; eeprom base address
SEQ_PRESETS_GLOBALS_Offset
SEQ_PRESETS_CFG0_AND_BPM		de	0x08, 120	; SEQ_CFG0 and BPM
SEQ_PRESETS_INT_EXT_DIVIDER		de	0x00, 0x01	; (Internal: 1:1, 1:4)
SEQ_PRESETS_SEQ_CHN_AND_SPLIT		de	1, 0x3c		; sequencer channel (0 to disable) and split note (C-3)
SEQ_PRESETS_MORPH_CHN_CC		de	1, 0x01		; morph channel (0 to disable) and assigned CC
SEQ_PRESETS_METRO_CHN			de	10, 0		; metronome channel (0 to disable)
SEQ_PRESETS_METRO_NOTES			de	0x25, 0x25	; C#1/C#1 (0 to disable)
SEQ_PRESETS_GLOBAL_SCALE		de	0x00, 0x00	; global scale, scale control mode (global/group1-4) and root note

SEQ_PRESETS_MCLK_ENABLED		de	0x00, 0		; router settings: MIDI clock enabled (second byte is dummy)

SEQ_PRESETS_ROUTER_IN0_PORT0		de	0x00, 0x00	; source/destination of port 0
SEQ_PRESETS_ROUTER_IN0_PORT1		de	0x00, 0x00	; source/destination of port 1
SEQ_PRESETS_ROUTER_IN0_PORT2		de	0x00, 0x00	; source/destination of port 2
SEQ_PRESETS_ROUTER_IN0_PORT3		de	0x00, 0x00	; source/destination of port 3
SEQ_PRESETS_ROUTER_IN0_PORT4		de	0x00, 0x00	; source/destination of port 4
SEQ_PRESETS_ROUTER_IN0_PORT5		de	0x00, 0x00	; source/destination of port 5
SEQ_PRESETS_ROUTER_IN0_PORT6		de	0x00, 0x00	; source/destination of port 6
SEQ_PRESETS_ROUTER_IN0_PORT7		de	0x00, 0x00	; source/destination of port 7

SEQ_PRESETS_ROUTER_IN1_PORT0		de	0x00, 0x00	; source/destination of port 0
SEQ_PRESETS_ROUTER_IN1_PORT1		de	0x00, 0x00	; source/destination of port 1
SEQ_PRESETS_ROUTER_IN1_PORT2		de	0x00, 0x00	; source/destination of port 2
SEQ_PRESETS_ROUTER_IN1_PORT3		de	0x00, 0x00	; source/destination of port 3
SEQ_PRESETS_ROUTER_IN1_PORT4		de	0x00, 0x00	; source/destination of port 4
SEQ_PRESETS_ROUTER_IN1_PORT5		de	0x00, 0x00	; source/destination of port 5
SEQ_PRESETS_ROUTER_IN1_PORT6		de	0x00, 0x00	; source/destination of port 6
SEQ_PRESETS_ROUTER_IN1_PORT7		de	0x00, 0x00	; source/destination of port 7


	;; fill unused EEPROM area
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00


	;; this 256 byte block is unusued yet
	org	0xf00300

	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	de	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00