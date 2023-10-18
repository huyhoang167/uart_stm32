/*
 * uart_services.c
 *
 *  Created on: Oct 13, 2023
 *      Author: hoang
 */

#include "uart_services.h"

uint8_t buffer_chan1_index = RESET_VALUE;
uint8_t buffer_chan2_index = RESET_VALUE;

uint8_t data_chan1_received_flag = false;
uint8_t data_chan2_received_flag = false;

uint8_t chan1_received_data;
uint8_t chan2_received_data;

uint8_t chan1_comletely_send_data_flag;
uint8_t chan2_comletely_send_data_flag;


uint8_t uart_chan1_buffer[BUFFER_CHAN1_LENGTH] = {RESET_VALUE};
uint8_t uart_chan2_buffer[BUFFER_CHAN1_LENGTH] = {RESET_VALUE};
/*
void uart_init(uint8_t uart_channel){
	switch(uart_channel){
		case 1:
			UART_CHAN1_INIT();
			break;
		case 2:
			UART_CHAN2_INIT();
			break;
		default:
			break;
	}
}*/

uint8_t uart_send(UART_HandleTypeDef *huart,uint8_t* data){
	HAL_StatusTypeDef transmit_status = HAL_OK;
	uint8_t data_length = RESET_VALUE;
	char *temp_data = (char *)data;

	/* Calculate length of message received */
	data_length = ((uint8_t)(strlen(temp_data)));

	chan1_comletely_send_data_flag = 0;

	transmit_status = UART_TRANSMIT_DATA(huart,data,data_length);
	if (transmit_status != HAL_OK){
		return TRANSMIT_ERROR;
	}
	return TRANSMIT_SUCCESS;
}

uint8_t uart_receive(uint8_t uart_channel, uint8_t* buffer);
void 	uart_callback_function(UART_HandleTypeDef *huart){
	UART_Rx_CALLBACK(huart);
	UART_Tx_CALLBACK(huart);
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
				buffer_chan1_index = RESET_VALUE;
				data_chan1_received_flag = 1;
				break;
			default:
				uart_chan1_buffer[buffer_chan1_index++] = (uint8_t)chan2_received_data;
				break;
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
				buffer_chan2_index = RESET_VALUE;
				data_chan2_received_flag = 1;
				break;
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
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}

}

