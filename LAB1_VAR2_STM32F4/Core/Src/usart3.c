/*
 * usart3.c
 *
 *  Created on: 9 окт. 2022 г.
 *      Author: shoko
 */

#include "main.h"
#include "stdio.h"

volatile uint8_t counter = 0;		//рахівник на колбеці У�?РТ
volatile uint8_t buff[16] = { 0, };   //буфер дл�? збереженн�? введеної інформації value
volatile uint8_t value = 0;	//змінна в котру запи�?ують байт інформаціїї з терміналу
volatile uint8_t flag = 0; //флаг дл від�?лідковуванн�? введенн�? команд в термінал

int str[255] = { 0, };					//ма�?ив де зберігають�?�? введені дані з ьерміналу

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
