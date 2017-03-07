/**
 * stm32f30x_it.c: Manage interrupt handlers
 */

#include "stm32f30x_it.h"
#include "controls.h"
#include <string.h>
#include <stdlib.h>
#include "radio.h"

int i;
extern uint8_t enabled;
static __IO uint32_t TimingDelay;
// uint16_t capture = 0;

uint8_t pid_run_flag = 0;
uint16_t radio_in[NUM_CHANNELS];
uint8_t radio_data[NUM_CHANNELS];

////////////////////////////////////////////////////////////////////////////////
//    Error Handlers
////////////////////////////////////////////////////////////////////////////////

void ErrorLoop(Led_TypeDef led) {
  int i = 0;
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(led);

  while (1) {
    for(i = 0; i < 0x7FFFF; i++);
    STM_EVAL_LEDToggle(LED3);
    STM_EVAL_LEDToggle(led);
  }
}

/**
 * Set LED3 and LED10 on Hard Fault
 */
void HardFault_Handler(void) {
  /* Go to infinite loop when Hard Fault exception occurs */
  ErrorLoop(LED10);
}

/**
 * Set LED3 and LED9
 */
void UsageFault_Handler(void) {
  ErrorLoop(LED9);
}

/**
 * Set LED3 and LED8
 */
void BusFault_Handler(void) {
  ErrorLoop(LED8);
}

/**
 * Set LED3 and LED7
 */
void MemMang_Hander(void) {
  ErrorLoop(LED7);
}

////////////////////////////////////////////////////////////////////////////////
//    User Handlers
////////////////////////////////////////////////////////////////////////////////

/**
 * User Button
 */
void EXTI0_IRQHandler(void) {
  if ((EXTI_GetITStatus(USER_BUTTON_EXTI_LINE) == SET) && (STM_EVAL_PBGetState(BUTTON_USER) != RESET)) {
    /* Delay */
    for (i = 0; i < 0x7FFFF; i++);

    while (STM_EVAL_PBGetState(BUTTON_USER) != RESET);

    for (i = 0; i < 0x7FFFF; i++);

#ifndef DEBUG
    if (enabled)
      enabled = 0;
    else
      enabled = 1;
#endif

    EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);

  }
}

/**
 * Wait for amount of milliseconds
 * nTime - time to wait in milliseconds
 */
void Delay(__IO uint32_t nTime) {
  TimingDelay = nTime;
  while (TimingDelay != 0);
}

/**
 * Delay Decrementer
 */
void TimingDelay_Decrement(void) {
  if (TimingDelay != 0x00) {
    TimingDelay--;
  }
}

/**
 * SysTick Handler
 */
void SysTick_Handler(void) {
  TimingDelay_Decrement();
}

/**
 * USART3 Interrupt handler
 *//*
void USART3_IRQHandler(void) {
  if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
    static uint8_t cnt = 255;
    static uint8_t size = 0;
    static command_list_t* new_command;
    char byte = USART_ReceiveData(USART3);
    if (cnt == 255) {
      size = byte - 2;
      new_command = (command_list_t*)malloc(sizeof(command_list_t));
      new_command->raw = (uint8_t*)malloc((size + 1) * sizeof(uint8_t));
      new_command->next = 0;
      new_command->timestamp = 0;
      cnt = 0;
    } else {
      if (cnt < size) {
        new_command->raw[cnt] = byte;
        cnt++;
      } else {
        if (command_list_start == 0) {
          command_list_start = new_command;
        } else {
          command_list_end->next = new_command;
        }
        command_list_end = new_command;
        cnt = 255;
        STM_EVAL_LEDToggle(LED9);
      }
    }
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
  }
}
*/
void TIM3_IRQHandler(void) {
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
    if (pid_run_flag)
      STM_EVAL_LEDOn(LED10);
    pid_run_flag = 1;
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  }
}

void TIM2_IRQHandler(void)
{
	static float capture_1,capture_1_2,capture_2,capture_2_2,capture_3,capture_3_2,capture_4,capture_4_2;
    static radio_command_list_t* new_command;
    new_command = (radio_command_list_t*)malloc(sizeof(radio_command_list_t));
    new_command->radio = (float*)malloc(NUM_CHANNELS * sizeof(float));
    new_command->next = 0;
	if(TIM2->SR & TIM_IT_CC1)
	{
		TIM2->SR = ~TIM_IT_CC1;//TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
		TIM2->SR = ~TIM_FLAG_CC1OF;
		if(GPIOB->IDR & GPIO_Pin_0)
		{
			capture_1 = TIM_GetCapture1(TIM2);
			radio_data[RADIO_THROTTLE] = 0;
		}
		else
		{
			capture_1_2 = TIM_GetCapture1(TIM2);
			if(capture_1_2>=capture_1)
			{
				radio_in[RADIO_THROTTLE] = THROTTLE_MIN + (((capture_1_2 - capture_1) - RADIO_THROTTLE_MIN) / RADIO_THROTTLE_RANGE) * THROTTLE_RANGE;
				radio_data[RADIO_THROTTLE] = 1;
			}
			else
			{
				radio_in[RADIO_THROTTLE] = THROTTLE_MIN + (((0xffff-capture_1+capture_1_2) - RADIO_THROTTLE_MIN) / RADIO_THROTTLE_RANGE) * THROTTLE_RANGE;
				radio_data[RADIO_THROTTLE] = 1;
			}
		}
	}
	if(TIM2->SR & TIM_IT_CC2)
	{
		TIM2->SR = ~TIM_IT_CC2;
		TIM2->SR = ~TIM_FLAG_CC2OF;
		if(GPIOB->IDR & GPIO_Pin_1)
		{
			capture_2 = TIM_GetCapture2(TIM2);
			radio_data[RADIO_ROLL] = 0;
		}
		else
		{
			capture_2_2 = TIM_GetCapture2(TIM2);
			if(capture_2_2>=capture_2)
			{
				radio_in[RADIO_ROLL] = ROLL_MIN + (((capture_2_2-capture_2) - RADIO_ROLL_MIN) / RADIO_ROLL_RANGE) * ROLL_RANGE;
				radio_data[RADIO_ROLL] = 1;
			}
			else
			{
				radio_in[RADIO_ROLL] = ROLL_MIN + (((0xffff-capture_2+capture_2_2) - RADIO_ROLL_MIN) / RADIO_ROLL_RANGE) * ROLL_RANGE;
				radio_data[RADIO_ROLL] = 1;
			}
		}
	}
	if(TIM2->SR & TIM_IT_CC3)
	{
		TIM2->SR = ~TIM_IT_CC3;
		TIM2->SR = ~TIM_FLAG_CC3OF;
		if(GPIOB->IDR & GPIO_Pin_2)
		{
			capture_3 = TIM_GetCapture3(TIM2);
			radio_data[RADIO_YAW] = 0;
		}
		else
		{
			capture_3_2 = TIM_GetCapture3(TIM2);
			if(capture_3_2>=capture_3)
			{
				radio_in[RADIO_YAW] = YAW_MIN + (((capture_3_2-capture_3) - RADIO_YAW_MIN) / RADIO_YAW_RANGE) * YAW_RANGE;
				radio_data[RADIO_YAW] = 1;
			}
			else
			{
				radio_in[RADIO_YAW] = YAW_MIN + (((0xffff-capture_3+capture_3_2) - RADIO_YAW_MIN) / RADIO_YAW_RANGE) * YAW_RANGE;
				radio_data[RADIO_YAW] = 1;
			}
		}
	}
	if(TIM2->SR & TIM_IT_CC4)
	{
		TIM2->SR = ~TIM_IT_CC4;
		TIM2->SR = ~TIM_FLAG_CC4OF;
		if(GPIOB->IDR & GPIO_Pin_3)
		{
			capture_4 = TIM_GetCapture4(TIM2);
			radio_data[RADIO_PITCH] = 0;
		}
		else
		{
			capture_4_2 = TIM_GetCapture4(TIM2);
			if(capture_4_2>=capture_4)
			{
				radio_in[RADIO_PITCH] = PITCH_MIN + (((capture_4_2-capture_4) - RADIO_PITCH_MIN) / RADIO_PITCH_RANGE) * PITCH_RANGE;
				radio_data[RADIO_PITCH] = 1;
			}
			else
			{
				radio_in[RADIO_PITCH] = PITCH_MIN + (((0xffff-capture_4+capture_4_2) - RADIO_PITCH_MIN) / RADIO_PITCH_RANGE) * PITCH_RANGE;
				radio_data[RADIO_PITCH] = 1;
			}
		}
	}
	if(radio_data[RADIO_THROTTLE] && radio_data[RADIO_ROLL] && radio_data[RADIO_YAW] && radio_data[RADIO_PITCH])
	{
	    new_command->radio[RADIO_THROTTLE] = radio_in[RADIO_THROTTLE];
	    new_command->radio[RADIO_ROLL] = radio_in[RADIO_ROLL];
	    new_command->radio[RADIO_PITCH] = radio_in[RADIO_PITCH];
	    new_command->radio[RADIO_YAW] = radio_in[RADIO_YAW];
        if (radio_command_list_start == 0) {
        	radio_command_list_start = new_command;
        } else {
        	radio_command_list_start->next = new_command; // initial was radio_command_list_end
        }
       // radio_command_list_end = new_command;

	}
}
