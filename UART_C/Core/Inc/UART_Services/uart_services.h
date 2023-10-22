/*
 * uart_services.h
 *
 *  Created on: Oct 13, 2023
 *      Author: hoang
 */

#ifndef INC_UART_SERVICES_UART_SERVICES_H_
#define INC_UART_SERVICES_UART_SERVICES_H_

#include "stdint.h"
#include "main.h"
#include "string.h"

extern uint8_t chan1_received_data;
extern uint8_t chan2_received_data;

#define NUMBER_CHANNEL 	2

#define CHANNEL_1   1
#define	CHANNEL_2   2

#define BUFFER_CHAN1_LENGTH 10
#define BUFFER_CHAN2_LENGTH 10


#define CHANNEL_NOT_FOUND	3


#define RESET_VALUE         0
#define CARRIAGE_ASCII      13

extern uint8_t buffer_chan1_index;
extern uint8_t buffer_chan2_index;

extern uint8_t data_chan1_received_flag;
extern uint8_t data_chan2_received_flag;

extern uint8_t uart_chan1_buffer[BUFFER_CHAN1_LENGTH];
extern uint8_t uart_chan2_buffer[BUFFER_CHAN1_LENGTH];

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;

extern UART_HandleTypeDef* uart_obj[NUMBER_CHANNEL];



void uart_init(uint8_t uart_channel);
uint8_t uart_send(uint8_t uart_channel ,uint8_t* data, uint8_t data_length);
void uart_callback(uint8_t uart_channel);
uint8_t uart_receive(uint8_t uart_channel);
void application_uart(uint8_t uart_channel);

#endif /* INC_UART_SERVICES_UART_SERVICES_H_ */
