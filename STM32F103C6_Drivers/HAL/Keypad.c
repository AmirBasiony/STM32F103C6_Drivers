/*
 * Keypad.c
 *
 * Created: 15/07/2023 10:59:15 م
 *  Author: Amir
 */

#include "Keypad.h"
#include "stdint.h"

uint16_t KEYPAD_R[] ={R0,R1,R2,R3};
uint16_t KEYPAD_C[] ={C0,C1,C2,C3};

void KEYPAD_Init()
{
	//	DataDir_KEYPAD_PORT &= ~((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3)); // Input Pins
	//	DataDir_KEYPAD_PORT |= ((1<<C0)| (1<<C1) | (1<<C2) | (1<<C3));// Output Pins
	// SET (R0 ,R1 ,R2 ,R3) AS OUTPUT
	MCAL_GPIO_SET_Pin(KEYPAD_PORT, R0, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(KEYPAD_PORT, R1, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(KEYPAD_PORT, R2, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(KEYPAD_PORT, R3, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	// SET (C0 ,C1 ,C2 ,C3) AS OUTPUT
	MCAL_GPIO_SET_Pin(KEYPAD_PORT, C0, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(KEYPAD_PORT, C1, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(KEYPAD_PORT, C2, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);
	MCAL_GPIO_SET_Pin(KEYPAD_PORT, C3, GPIO_MODE_Output_PP, GPIO_MAX_Speed_10M);

	//	KEYPAD_PORT = 0xFF;
	// SET PINs (R0 ,R1 ,R2 ,R3 ,C0 ,C1 ,C2 ,C3)
	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);
}

char KEYPAD_Get_Char()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		//		KEYPAD_PORT |= ((1<<KEYPAD_C[0])| (1<<KEYPAD_C[1]) | (1<<KEYPAD_C[2]) | (1<<KEYPAD_C[3]));
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[0], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[1], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[2], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[3], GPIO_PIN_SET);
		//		KEYPAD_PORT &= ~(1<<KEYPAD_C[i]);
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[i], GPIO_PIN_RESET);
		for(j=0;j<4;j++)
		{
			if((MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R[j])) == 0) // check if key is pressed
			{
				while((MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R[j])) == 0)
					;  // For Single Press

				switch(i) // for columns
				{
				//column 0
				case 0 :
					if(j == 0) return '7'; // for row 0 , column 0
					else if(j == 1) return '4'; // for row 1 , column 0
					else if(j == 2) return '1'; // for row 2 , column 0
					else if(j == 3) return '!'; // for row 3 , column 0
					break;
					//column 1
				case 1 :
					if(j == 0) return '8'; // for row 0 , column 1
					else if(j == 1) return '5'; // for row 1 , column 1
					else if(j == 2) return '2'; // for row 2 , column 1
					else if(j == 3) return '0'; // for row 3 , column 1
					break;
					//column 2
				case 2 :
					if(j == 0) return '9'; // for row 0 , column 2
					else if(j == 1) return '6'; // for row 1 , column 2
					else if(j == 2) return '3'; // for row 2 , column 2
					else if(j == 3) return '='; // for row 3 , column 2
					break;
					//column 3
				case 3 :
					if(j == 0) return '/'; // for row 0 , column 3
					else if(j == 1) return '*'; // for row 1 , column 3
					else if(j == 2) return '-'; // for row 2 , column 3
					else if(j == 3) return '+'; // for row 3 , column 3
					break;
				}
			}
		}
	}
	return 'N'; // No Key is Pressed
}
