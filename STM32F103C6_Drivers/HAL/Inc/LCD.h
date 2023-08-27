/*
 * LCD.h
 *
 * Created: 15/07/2023 08:39:32 م
 *  Author: Amir
 */ 

#ifndef LCD_H_
#define LCD_H_

#include "stdlib.h"
#include <STM32F103x6_GPIO.h>


#define LCD_CRTL GPIOA
#define RS_SWITCH 		GPIO_PIN_8
#define RW_SWITCH 		GPIO_PIN_9
#define ENABLE_SWITCH 	GPIO_PIN_10

#define DATA_SHIFT 4

#define	EIGHT_BIT_MODE
//#define FOUR_BIT_MODE



#define LCD_REGISTER_SELECT_PIN						(0)
#define LCD_READ_WRITE_PIN							(1)
#define LCD_ENABLE_PIN								(2)
#define LCD_REGISTER_SELECT_ENABLE					(1)
#define LCD_REGISTER_SELECT_DISABLE					(0)
#define READ_FROM_LCD								(1)
#define WRITE_TO_LCD								(0)
#define LCD_ENABLE									(1)
#define LCD_DISABLE									(0)
#define LCD_FIRST_LINE								(0)
#define LCD_SECOND_LINE								(1)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_RAW						(0x80)
#define LCD_BEGIN_AT_SECOND_RAW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)

void LCD_init(void);
void LCD_GPIO_Init(void);
void LCD_Write_Command(unsigned char command);
void LCD_Write_Char(char Char);
void LCD_Write_String(char * String);
void LCD_Clear_Screen(void);
void LCD_GOTO_XY(unsigned char line , unsigned char position);
void LCD_Write_Integer(unsigned char num);
void LCD_Write_Real_Number(double num);
void delay_ms(unsigned int x);

#endif /* LCD_H_ */
