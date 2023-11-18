/*
 * fsm.c
 *
 *  Created on: Nov 18, 2023
 *      Author: ASUS
 */
#include "fsm.h"
int status_command = INIT_command, status_uart = INIT_uart;
uint8_t temp = 0;
uint8_t cmd[50];
uint32_t ADC_value = 0;
uint8_t index_buffer = 0;
uint8_t buffer[MAX_BUFFER_SIZE] = {0};
uint8_t buffer_flag = 0;

void command_parser_fsm(){
	switch(status_command){
	case INIT_command:
		if (temp == '!'){
			status_command = READ_command;
		}
		break;

	case READ_command:
		if (temp != '#') cmd[index_buffer++] = temp;
		else { // == '#'
			index_buffer = 0;
			temp = 0;
			status_command = STOP_command;
		}
		break;

	case STOP_command:
		if (cmd[0] == 'R' && cmd[1] == 'S' && cmd[2] == 'T'){
			status_uart = RST;
		}
		else if (cmd[0] == 'O' && cmd[1] == 'K'){
			status_uart = OK;
		}

		status_command = INIT_command;
		break;

	default:
		break;
	}
}
void uart_communication_fsm(){
	switch(status_uart){
	case INIT_uart:
		break;

	case RST:
		ADC_value = HAL_ADC_GetValue (&hadc1);
		HAL_UART_Transmit (&huart2, (void *) str, sprintf (str, "%d\n", ADC_value), 50);
		status_uart = WAIT;
		setTimer2(300);
		break;

	case WAIT:
		break;

	case OK:
		timer2_flag = 0;
		timer2_counter=0;
		status_uart = INIT_uart;
		break;

	default:
		break;
	}
}
