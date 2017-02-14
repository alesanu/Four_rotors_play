/**
  ******************************************************************************
  * @file    WWDG_Example/main.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    20-September-2012
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


/* Includes */
#include "stm32f30x.h"

#include "stdio.h"

#include "Delay.h"
#include "IMU.h"
#include "BMP085.h"
#include "ESC.h"
#include "PID.h"
#include "IO_Devices.h"

#include "Serial.h"
#include "IO_Devices.h"
#include "nRF24.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
void GPIO_Configuration(void);
void NVIC_Configuration(void);


void GetSensors(void);
void PrintSensors(void);


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
