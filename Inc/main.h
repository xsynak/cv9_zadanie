/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_pwr.h"
#include "stm32f3xx_ll_dma.h"
#include "stm32f3xx_ll_tim.h"
#include "stm32f3xx_ll_i2c.h"
#include "stm32f3xx.h"
#include "stm32f3xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define		GPIO_PORT_BUTTON				GPIOB
#define		GPIO_PIN_BUTTON					3

// defines for "checkButtonState"
#define		TRIGGER_RISE					0
#define		TRIGGER_FALL					1

#define		BUTTON_EXTI_TRIGGER				TRIGGER_FALL
#define		BUTTON_EXTI_SAMPLES_WINDOW		30
#define		BUTTON_EXTI_SAMPLES_REQUIRED	20
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
int state,dot_pos;
int setState(int new_state);
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define DISP_B_Pin LL_GPIO_PIN_0
#define DISP_B_GPIO_Port GPIOA
#define DISP_A_Pin LL_GPIO_PIN_1
#define DISP_A_GPIO_Port GPIOA
#define DISP_3_Pin LL_GPIO_PIN_2
#define DISP_3_GPIO_Port GPIOA
#define DISP_F_Pin LL_GPIO_PIN_3
#define DISP_F_GPIO_Port GPIOA
#define DISP_1_Pin LL_GPIO_PIN_4
#define DISP_1_GPIO_Port GPIOA
#define DISP_TIME_Pin LL_GPIO_PIN_7
#define DISP_TIME_GPIO_Port GPIOA
#define DISP_0_Pin LL_GPIO_PIN_0
#define DISP_0_GPIO_Port GPIOB
#define DISP_DP_Pin LL_GPIO_PIN_1
#define DISP_DP_GPIO_Port GPIOB
#define DISP_C_Pin LL_GPIO_PIN_8
#define DISP_C_GPIO_Port GPIOA
#define DISP_E_Pin LL_GPIO_PIN_11
#define DISP_E_GPIO_Port GPIOA
#define DISP_2_Pin LL_GPIO_PIN_12
#define DISP_2_GPIO_Port GPIOA
#define BUTTON_Pin LL_GPIO_PIN_3
#define BUTTON_GPIO_Port GPIOB
#define BUTTON_EXTI_IRQn EXTI3_IRQn
#define DISP_G_Pin LL_GPIO_PIN_4
#define DISP_G_GPIO_Port GPIOB
#define DISP_D_Pin LL_GPIO_PIN_5
#define DISP_D_GPIO_Port GPIOB
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
