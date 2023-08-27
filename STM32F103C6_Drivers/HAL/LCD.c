/*
 * LCD.c
 *
 * Created: 15/07/2023 08:38:34 م
 *  Author: Amir
 */ 
#include "LCD.h"
#include "stdlib.h"
#include "stdio.h"
void delay_ms(unsigned int x)
{
	unsigned int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<255;j++);
}
void LCD_KICK()
{
	MCAL_GPIO_WritePin(LCD_CRTL, ENABLE_SWITCH, GPIO_PIN_SET);
	//	LCD_CRTL &=  ~(1<<ENABLE_SWITCH); // Make PIN(E) disabled To ensure that doesn't exist any command is executing while checking LCD BUSY
	delay_ms(50);
	//	LCD_CRTL |=  (1<<ENABLE_SWITCH); // Return PIN(E) enabled [ To execute any command I want after then)
	MCAL_GPIO_WritePin(LCD_CRTL, ENABLE_SWITCH, GPIO_PIN_RESET);
}
void LCD_GOTO_XY(unsigned char line , unsigned char position)
{
	if((position >= 0) && (position < 16))
	{
		if(line == 1)
		{
			LCD_Write_Command(LCD_BEGIN_AT_FIRST_RAW + position);
		}
		else if(line == 2)
		{
			LCD_Write_Command(LCD_BEGIN_AT_SECOND_RAW + position);
		}	
	}
}
void LCD_Clear_Screen(void)
{
	LCD_Write_Command(LCD_CLEAR_SCREEN);
}
void LCD_isbusy()
{
#ifdef	EIGHT_BIT_MODE
	//	DataDir_LCD_PORT = 0x00; //  make PORTA(D0--->D7) work as Input
	// SET PORTA PINS (0 ---> 7) AS INPUT
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_0, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_1, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_2, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_3, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_4, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_5, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_6, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_7, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
#endif

#ifdef	FOUR_BIT_MODE
	//	DataDir_LCD_PORT &= ~(0xFF << DATA_SHIFT); //  Mask (D4-->D7) for PORTA  to work as Input
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_4, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_5, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_6, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_7, GPIO_MODE_Input_FLO, GPIO_MAX_Speed_10M);
#endif
	//	LCD_CRTL |=  RW_SWITCH; //read mode
	MCAL_GPIO_WritePin(LCD_CRTL, RW_SWITCH, GPIO_PIN_SET);
	//	LCD_CRTL &=  ~(RS_SWITCH); //read mode
	MCAL_GPIO_WritePin(LCD_CRTL, RS_SWITCH, GPIO_PIN_RESET);
	LCD_KICK(); // D7 ifBusy --> OFF  , Else --> ON 
//	DataDir_LCD_PORT = 0xFF; //  return PORTA work as Output
//	LCD_CRTL &=  ~(1<<RW_SWITCH);
	MCAL_GPIO_WritePin(LCD_CRTL, RW_SWITCH, GPIO_PIN_RESET);
}
void LCD_GPIO_Init(void)
{
	//	DataDir_LCD_CTRL |= (1<<RW_SWITCH | 1<<RS_SWITCH | 1<<ENABLE_SWITCH);//make (E,RS,RW) OUTPUT PINS
	//SET PIN Control AS OUTPUT
	MCAL_GPIO_SET_Pin(LCD_CRTL, RW_SWITCH, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, RS_SWITCH, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, ENABLE_SWITCH, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);

	//============================
	// SET THE NEXT 8 PINS AS OUTPUT
	//	DataDir_LCD_PORT = 0xFF; //  return PORTA (pin 0 ---> 7) work as Output
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_0, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_1, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_2, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_3, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_4, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_5, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_6, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(LCD_CRTL, GPIO_PIN_7, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	//	LCD_CRTL &= ~(1<<RW_SWITCH | 1<<RS_SWITCH | 1<<ENABLE_SWITCH);//make control pins off to do (reset/set) according the command we want to do after then
	MCAL_GPIO_WritePin(LCD_CRTL, RW_SWITCH	  , GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CRTL, RS_SWITCH	  , GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CRTL, ENABLE_SWITCH, GPIO_PIN_RESET);
}
void LCD_init(void)
{
	delay_ms(20);
//	LCD_isbusy();
	LCD_GPIO_Init();
	//DataDir_LCD_PORT = 0xFF; //  return PORTA work as Output
	delay_ms(15);

	LCD_Clear_Screen();	
#ifdef	EIGHT_BIT_MODE
	LCD_Write_Command(LCD_FUNCTION_8BIT_2LINES);
#endif

#ifdef	FOUR_BIT_MODE
	LCD_Write_Command(0x02);
	LCD_Write_Command(LCD_FUNCTION_4BIT_2LINES);
#endif

	LCD_Write_Command(LCD_ENTRY_MODE);
	LCD_Write_Command(LCD_BEGIN_AT_FIRST_RAW);
	LCD_Write_Command(LCD_DISP_ON_CURSOR_BLINK);
}
void LCD_Write_Command(unsigned char command)
{
//	LCD_isbusy();
#ifdef	EIGHT_BIT_MODE
//	LCD_CRTL = command;
	MCAL_GPIO_WritePort(LCD_CRTL, command);
//	LCD_CRTL &= ~(1<<RW_SWITCH | 1<<RS_SWITCH); // Write Command Mode
	MCAL_GPIO_WritePin(LCD_CRTL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CRTL, RS_SWITCH, GPIO_PIN_RESET);
	delay_ms(1);
	LCD_KICK();
#endif
#ifdef	FOUR_BIT_MODE
	// Send Most Significant 4 Bits in the data
	MCAL_GPIO_WritePort(LCD_CRTL, (LCD_PORT & 0x0F) | (command & 0xF0));
//	LCD_PORT = ((LCD_PORT & 0x0F) | (command & 0xF0));
	LCD_CRTL &= ~(1<<RW_SWITCH | 1<<RS_SWITCH); // Write Command Mode
	delay_ms(1);
	LCD_KICK();
	// Send Least Significant 4 Bits in the data
	MCAL_GPIO_WritePort(LCD_CRTL, (LCD_PORT & 0x0F) | (command << 4));
//	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	LCD_CRTL &= ~(1<<RW_SWITCH | 1<<RS_SWITCH); // Write Command Mode
	delay_ms(1);
	LCD_KICK();

#endif
}
void LCD_Write_Char(char Char)
{
//	LCD_isbusy();
#ifdef	EIGHT_BIT_MODE
//	MCAL_GPIO_WritePin(LCD_CRTL, RS_SWITCH, GPIO_PIN_SET);
//	LCD_CRTL |= (1<<RS_SWITCH);
//	LCD_PORT = Char;
	MCAL_GPIO_WritePort(LCD_CRTL, Char);
	// Write data Mode
	MCAL_GPIO_WritePin(LCD_CRTL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CRTL, RS_SWITCH, GPIO_PIN_SET);
//	LCD_CRTL &= ~(1<<RW_SWITCH);
//	LCD_CRTL |= (1<<RS_SWITCH);
	delay_ms(1);
	LCD_KICK();
#endif
#ifdef	FOUR_BIT_MODE
	// Send Most Significant 4 Bits in the data
	MCAL_GPIO_WritePort(LCD_CRTL, (LCD_PORT & 0x0F) | (Char & 0xF0));
//	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	// Write data Mode
	MCAL_GPIO_WritePin(LCD_CRTL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CRTL, RS_SWITCH, GPIO_PIN_SET);
//	LCD_CRTL &= ~(1<<RW_SWITCH);
//	LCD_CRTL |= (1<<RS_SWITCH);
	delay_ms(1);
	LCD_KICK();
	// Send Least Significant 4 Bits in the data
	MCAL_GPIO_WritePort(LCD_CRTL, (LCD_PORT & 0x0F) | (Char << 4));
//	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	// Write data Mode
	MCAL_GPIO_WritePin(LCD_CRTL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CRTL, RS_SWITCH, GPIO_PIN_SET);
//	LCD_CRTL &= ~(1<<RW_SWITCH);
//	LCD_CRTL |= (1<<RS_SWITCH);
	delay_ms(1);
	LCD_KICK();

#endif
}
void LCD_Write_String(char *String)
{
	unsigned char counter = 0;
	while(*String > 0 )
	{
		LCD_Write_Char(*String++);
		counter++;
		if(counter == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if(counter == 32)
		{
			LCD_Write_Command(LCD_CLEAR_SCREEN);
			LCD_GOTO_XY(1,0);
			counter = 0;
		}
	}
}
void LCD_Write_Integer(unsigned char num)
{
	char *str = 0;
	// convert integer to string
	itoa(num,str,10);
	// Display the string
	LCD_Write_String(str);
}
void LCD_Write_Real_Number(double Real_Num) // 653.0332
{
	char str[16];

	char * Numsign = (Real_Num < 0) ? "-" : "";
	int IntNum1 = Real_Num ; // cast the integer Part of the number (653)
	float Float_Part = Real_Num - IntNum1;// cast the Float Part of the number (0.0332) 
	int IntNum2 = Float_Part * 10000 ; // turn into integer

	sprintf(str,"%s%d.%04d",Numsign,IntNum1,IntNum2);

	LCD_Write_String(str); // Send string 
}
