/*
 * fsm.h
 *
 *  Created on: Nov 18, 2023
 *      Author: ASUS
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "SoftwareTimer.h"

#define MAX_BUFFER_SIZE 30
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

void command_parser_fsm();
void uart_communiation_fsm();
#endif /* INC_FSM_H_ */
