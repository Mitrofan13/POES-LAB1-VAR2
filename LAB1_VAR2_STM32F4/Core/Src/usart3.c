/*
 * usart3.c
 *
 *  Created on: 9 окт. 2022 г.
 *      Author: shoko
 */

#include "main.h"
#include "stdio.h"
#include "myTypes.h"
#define R_BUFF_LEN 32

//extern uint8_t tipe_str;
//extern uint8_t buff[R_BUFF_LEN];
//extern uart_ring_buff_t uart_ring;
//
//extern uint8_t tstring[255];
//extern uint8_t rstring[R_BUFF_LEN + 1];
//extern char string[8];


extern volatile uint8_t counter;
extern volatile uint8_t buff[16];
extern volatile uint8_t value;
extern volatile uint8_t flag;

extern int str[255];

extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart3, (uint8_t*) &ch, 1, HAL_MAX_DELAY);
	return 0;
}
//Receive one char in blocking mode
int __io_getchar(void)
{
	uint8_t result;
	__HAL_UART_CLEAR_OREFLAG(&huart3);
	HAL_UART_Receive(&huart3, &result, 1, HAL_MAX_DELAY);
	if (result == '\r')
		result = '\n'; // Dirty hack. Replace "return" character with "new line" character
	return (int) result;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart3)
	{
		HAL_UART_Receive_IT(&huart3, &value, 1);
		//	sscanf(value,"%d",&buff[counter]);
		buff[counter] = value;

		if (value == '\r')
		{
			counter = 0;
			flag = 1;
		}
		else
			counter++;
	}
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	// Check that interrupt caused by UART1
//	if (huart == &huart3)
//		{
//			// Put new character from the UART receiver data register (RDR) to the ring buffer
//			ring_putchar(&uart_ring,huart->Instance->DR);                                             //питання RDR чи DR?
//			// Set the overrun flag if the message is longer than ring buffer can hold
//			if (uart_ring.end == uart_ring.start) uart_ring.flag.BufferOverrun = 1;
//			// Set the message ready flag if the end of line character has been received
//			if ((uart_ring.buffer[uart_ring.end -1] == '\r') ||
//					(uart_ring.buffer[uart_ring.end -1] == '\n'))
//				uart_ring.flag.MessageReady = 1;
//			// Receive the next character from UART in non blocking mode
//			HAL_UART_Receive_IT(&huart3,&uart_ring.buffer[uart_ring.end],1);
//		}
//}
//// Initializes the ring buffer
//void ring_init(uart_ring_buff_t * uart_ring, uint8_t * buff, uint16_t buff_size)
//{
//	uart_ring->buffer = buff;
//	uart_ring->size = buff_size;
//	ring_clear(uart_ring);
//}
//// Clears the ring buffer
//void ring_clear(uart_ring_buff_t * uart_ring)
//{
//	uart_ring->start = 0;
//	uart_ring->end = 0;
//	uart_ring->flag.BufferOverrun = 0;
//	uart_ring->flag.MessageReady = 0;
//}
//// Puts a new character to the ring buffer
//void ring_putchar(uart_ring_buff_t * uart_ring, uint8_t ch)
//{
//	uart_ring->buffer[uart_ring->end++] = ch;
//	if (uart_ring->end >= uart_ring->size) uart_ring->end = 0;
//}
//// Gets one character from the ring buffer
//uint8_t ring_getchar(uart_ring_buff_t * uart_ring)
//{
//	uint8_t ch = uart_ring->buffer[uart_ring->start++];
//	if (uart_ring->start >= uart_ring->size) uart_ring->start = 0;
//	return ch;
//}
//// Reads full message from the ring buffer and clears appropriate flags
//uint8_t ring_get_message(uart_ring_buff_t * uart_ring, uint8_t * string)
//{
//	uint16_t char_count = 0;
//	// Check if the message has been received
//	if (uart_ring->flag.MessageReady)
//		{
//			if (uart_ring->flag.BufferOverrun)
//				{
//					uart_ring->start = uart_ring->end;
//					uart_ring->flag.BufferOverrun = 0;
//				}
//			while ((uart_ring->buffer[uart_ring->start] != '\r') &&
//						 (uart_ring->buffer[uart_ring->start] != '\n') &&
//						 (uart_ring->size != char_count - 1))
//				{
//					*string =  ring_getchar(uart_ring);
//					string++;
//					char_count++;
//				}
//			*string =  ring_getchar(uart_ring);
//			string++;
//			char_count++;
//			*string = '\0';
//			uart_ring->flag.MessageReady = 0;
//		}
//	return char_count;
//}
