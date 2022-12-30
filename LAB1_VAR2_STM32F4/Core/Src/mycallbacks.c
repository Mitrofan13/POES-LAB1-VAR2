/*
 * mycallbacks.c
 *
 *  Created on: 13 ����� 2017 �.
 *      Author: Maxim
 */

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "myTypes.h"
#include "Ptimer.h"

extern globalFlags_t gflag;

inline void HAL_SYSTICK_Callback(void)
{
  PTimer();
}

inline void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
 /* Prevent unused argument(s) compilation warning */
 UNUSED(GPIO_Pin);
 /* Set button pressed flag and disable EXTI0 IRQ */
 gflag.button_action = 1;
}
