
#ifndef _HW_FLAGS_H
#define _HW_FLAGS_H

#ifdef __18F452
#define PIC_DERIVATIVE_CODE_SIZE	0x08000
#define PIC_DERIVATIVE_RAM_SIZE		0x600
#define PIC_DERIVATIVE_EEPROM_SIZE	0x100
#define PIC_DERIVATIVE_IRQ_WORKAROUND	0
#define PIC_DERIVATIVE_NEW_ADC		0
#define PIC_DERIVATIVE_CMCON_INIT	0
#define PIC_DERIVATIVE_T08BIT_INVERTED	0
#define PIC_DERIVATIVE_SET_LCD_4BIT	0
#endif

#ifdef __18F4620
#define PIC_DERIVATIVE_CODE_SIZE	0x10000
#define PIC_DERIVATIVE_RAM_SIZE		0xf80
#define PIC_DERIVATIVE_EEPROM_SIZE	0x400
#define PIC_DERIVATIVE_IRQ_WORKAROUND	1
#define PIC_DERIVATIVE_NEW_ADC		1
#define PIC_DERIVATIVE_CMCON_INIT	1
#define PIC_DERIVATIVE_T08BIT_INVERTED	1
#define PIC_DERIVATIVE_SET_LCD_4BIT	0
#endif
	
#ifdef __18F4520
#define PIC_DERIVATIVE_CODE_SIZE	0x08000
#define PIC_DERIVATIVE_RAM_SIZE		0x600
#define PIC_DERIVATIVE_EEPROM_SIZE	0x100
#define PIC_DERIVATIVE_IRQ_WORKAROUND	1
#define PIC_DERIVATIVE_NEW_ADC		1
#define PIC_DERIVATIVE_CMCON_INIT	1
#define PIC_DERIVATIVE_T08BIT_INVERTED	0
#define PIC_DERIVATIVE_SET_LCD_4BIT	0
#endif

#ifdef __18F4682
#define PIC_DERIVATIVE_CODE_SIZE	0x14000
#define PIC_DERIVATIVE_RAM_SIZE		0xd00
#define PIC_DERIVATIVE_EEPROM_SIZE	0x400
#define PIC_DERIVATIVE_IRQ_WORKAROUND	0
#define PIC_DERIVATIVE_NEW_ADC		1
#define PIC_DERIVATIVE_CMCON_INIT	1
#define PIC_DERIVATIVE_T08BIT_INVERTED	0
#define PIC_DERIVATIVE_SET_LCD_4BIT	1
#endif

#ifdef __18F4685
#define PIC_DERIVATIVE_CODE_SIZE	0x18000
#define PIC_DERIVATIVE_RAM_SIZE		0xd00
#define PIC_DERIVATIVE_EEPROM_SIZE	0x400
#define PIC_DERIVATIVE_IRQ_WORKAROUND	0
#define PIC_DERIVATIVE_NEW_ADC		1
#define PIC_DERIVATIVE_CMCON_INIT	1
#define PIC_DERIVATIVE_T08BIT_INVERTED	0
#define PIC_DERIVATIVE_SET_LCD_4BIT	1
#endif

#endif
