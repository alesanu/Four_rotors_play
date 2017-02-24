/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "radio.h"


void radio_init(void)
{
	  // Select TIM1 on pins PB11, PB12, PB13 and PB14
		TIM_ICInitTypeDef  TIM_ICInitStructure;

	  /* TIM1 Configuration */
	  radio_TIM_config();

	  	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
	    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	    TIM_ICInitStructure.TIM_ICFilter = 0x0;

	    TIM_PWMIConfig(TIM1, &TIM_ICInitStructure);

	    /* Select the TIM2 Input Trigger: TI2FP2 */
	    TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);

	    /* Select the slave Mode: Reset Mode */
	    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
	    TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);

	    /* TIM enable counter */
	    TIM_Cmd(TIM2, ENABLE);

	    /* Enable the CCx Interrupt Request */
	     TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
	     TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
	     TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
	     TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);
}

/**
  * @brief  Configure the TIM1 Pins.
  * @param  None
  * @retval None
  */
void radio_TIM_config(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;

	  /* TIM1 clock enable */
	   RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	    /* GPIOB clock enable */
	    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	  /* TIM2 chennel2 configuration : PB11, PB12, PB13 and PB14 */
	  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);

	  /* Connect TIM pin to AF1 */
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_2);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_2);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_2);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_2);

	  /* Enable the TIM1 global Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

}

