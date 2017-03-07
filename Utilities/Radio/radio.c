/*
 * radio.c
 *
 *  Created on: Mar 7, 2017
 *      Author: lesanua
 */

#include "radio.h"

void radio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2	| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_1);

	TIM2->PSC = (168 / 2) - 1;

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x3;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x3;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x3;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x3;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	/* TIM enable counter */
	TIM_Cmd(TIM2, ENABLE);

	/* Enable the CC2 Interrupt Request */
	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);
}
