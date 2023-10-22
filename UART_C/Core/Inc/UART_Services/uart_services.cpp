/*
 * uart_services.c
 *
 *  Created on: Oct 13, 2023
 *      Author: hoang
 */

#include "uart_services.h"

class UART_MSG{
	uint8_t header[10];
	uint8_t data[20];
	uint8_t footer[10];
public:
	UART_MSG(uint8_t* header, uint8_t* data, uint8_t* footer){
		this->header = header;
		this->data = data;
		this->footer = end;
	}
	uint8_t* get_header(){
		return header;
	}
	uint8_t* get_data(){
		return data;
	}
	uint8_t* get_footer(){
		return footer;
	}

};

uint8_t buffer_chan1_index = RESET_VALUE;
uint8_t buffer_chan2_index = RESET_VALUE;

uint8_t data_chan1_received_flag = RESET_VALUE;
uint8_t data_chan2_received_flag = RESET_VALUE;

uint8_t chan1_received_data;
uint8_t chan2_received_data;


uint8_t uart_chan1_buffer[BUFFER_CHAN1_LENGTH] = {RESET_VALUE};
uint8_t uart_chan2_buffer[BUFFER_CHAN1_LENGTH] = {RESET_VALUE};

#define UART_RECEIVED_DATA(chan,received_data) 	HAL_UART_Receive_IT(chan,received_data,1)
#define UART_TRANSMIT_DATA(chan,data,size) 	HAL_UART_Transmit_IT(chan,data,size)

#define UART_Rx_CALLBACK(chan)   	HAL_UART_RxCpltCallback(chan)
#define UART_Tx_CALLBACK(chan)		HAL_UART_TxCpltCallback(chan)

UART_HandleTypeDef* uart_obj[NUMBER_CHANNEL];

void uart_init(uint8_t uart_channel){
	switch(uart_channel){
		case CHANNEL_1:
			uart_obj[uart_channel-1] = &huart4;
			break;
		case CHANNEL_2:
			uart_obj[uart_channel-1] = &huart5;
			break;
	}
}

uint8_t uart_send(uint8_t uart_channel ,uint8_t* data, uint8_t data_length){
	switch(uart_channel){
		case CHANNEL_1:
			return UART_TRANSMIT_DATA(uart_obj[uart_channel-1],data,data_length);
			break;
		case CHANNEL_2:
			return UART_TRANSMIT_DATA(uart_obj[uart_channel-1],data,data_length);
			break;

	}
	return CHANNEL_NOT_FOUND;
}
uint8_t uart_receive(uint8_t uart_channel){
	if (data_chan1_received_flag == 1){
		data_chan1_received_flag = 0;
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		switch(uart_channel){
			case CHANNEL_1:
				application_uart(uart_channel);
				break;
			case CHANNEL_2:
				application_uart(uart_channel);
				break;
		}

	}
	return TRANSMIT_SUCCESS;
}
void uart_callback(uint8_t uart_channel){
	switch(uart_channel){
		case CHANNEL_1:
		{
			UART_Rx_CALLBACK(uart_obj[uart_channel-1]);
			UART_Tx_CALLBACK(uart_obj[uart_channel-1]);
			break;
		}
		case CHANNEL_2:
		{
			UART_Rx_CALLBACK(uart_obj[uart_channel-1]);
			UART_Tx_CALLBACK(uart_obj[uart_channel-1]);
			break;
		}
	}
}

void application_uart(uint8_t uart_channel){
	switch(uart_channel){
		case CHANNEL_1:
		{
			uint8_t buffer[30] = "Ok\n";
			uint8_t input_length = (uint8_t)strlen((char*)&uart_chan1_buffer);
			//if (uart_chan1_buffer[0] == 'H')
			if (strcmp((char *)&uart_chan1_buffer,"Hi") == 0)
				uart_send(CHANNEL_1,buffer,2);
			for(int i = 0; i < input_length;i++){
				uart_chan1_buffer[i] = RESET_VALUE;
			}
			UART_RECEIVED_DATA(uart_obj[uart_channel-1],&chan1_received_data);
			break;
		}
		case CHANNEL_2:
			break;
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == UART4){
		if(BUFFER_CHAN1_LENGTH == buffer_chan1_index)
		{
			buffer_chan1_index = RESET_VALUE;
		}
		switch(chan1_received_data){
			case CARRIAGE_ASCII:
			{
				buffer_chan1_index = RESET_VALUE;
				data_chan1_received_flag = 1;
				break;
			}

			default:{
				uart_chan1_buffer[buffer_chan1_index++] = (uint8_t)chan1_received_data;
			    break;
			}
		}
		UART_RECEIVED_DATA(huart,&chan1_received_data);
	}
	else if (huart->Instance == UART5){
		if(BUFFER_CHAN2_LENGTH == buffer_chan2_index)
		{
			buffer_chan2_index = RESET_VALUE;
		}
		switch(chan2_received_data){
			case CARRIAGE_ASCII:
			{
				buffer_chan2_index = RESET_VALUE;
				data_chan2_received_flag = 1;
				break;
			}
			default:
				uart_chan2_buffer[buffer_chan2_index++] = (uint8_t)chan2_received_data;
				break;
		}
		UART_RECEIVED_DATA(huart,&chan2_received_data);
	}
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == UART4){

	}
	if (huart->Instance == UART5){

	}

}

