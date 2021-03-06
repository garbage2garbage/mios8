// $Id$
/*
 * MIDI program module definitions
 *
 * ==========================================================================
 *
 *  Copyright (C) 2005  Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _MIDI_H
#define _MIDI_H

/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Global Types
/////////////////////////////////////////////////////////////////////////////

// status of analog toolbox application
typedef union {
  struct {
    unsigned ALL:8;
  };
  struct {
    unsigned NOTE:7;
    unsigned GATE:1;
  };
} midi_note_t;



/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

void MIDI_Init(void);
void MIDI_Evnt(unsigned char evnt0, unsigned char evnt1, unsigned char evnt2);

/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////

extern midi_note_t midi_note[16];

extern unsigned char midi_cc_chn0[128];

extern unsigned int midi_pitch_bender[16];

#endif /* _MIDI_H */
