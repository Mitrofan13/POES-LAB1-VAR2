/*
 * exti_func.c
 *
 *  Created on: Oct 8, 2022
 *      Author: shoko
 */


#include "main.h"
extern uint8_t flag;
extern uint8_t btn_cur ;
extern uint8_t btn_prev ;
extern uint8_t count;

extern TIM_HandleTypeDef htim1;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim->Instance == TIM1)
	{
		HAL_TIM_Base_Stop_IT(&htim1); // останавливаем таймер
		__HAL_GPIO_EXTI_CLEAR_IT(BUTTON_EXTI_Pin);  // очищаем бит EXTI_PR (бит прерывания)
		NVIC_ClearPendingIRQ(EXTI15_10_IRQn); // очищаем бит NVIC_ICPRx (бит очереди)
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);   // включаем внешнее прерывание
		btn_cur = HAL_GPIO_ReadPin(BUTTON_EXTI_GPIO_Port, BUTTON_EXTI_Pin);
		if((btn_prev == 0) && (btn_cur != 0))
		{
			count++;
			if(count == 4)
			{
				count = 0;
			}
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == BUTTON_EXTI_Pin)
	{
		HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // сразу же отключаем прерывания на этом пине
		// либо выполняем какое-то действие прямо тут, либо поднимаем флажок
		HAL_TIM_Base_Start_IT(&htim1); // запускаем таймер
	}
}
