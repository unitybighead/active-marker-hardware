/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MODE_Pin GPIO_PIN_1
#define MODE_GPIO_Port GPIOA
#define COLOR_Pin GPIO_PIN_2
#define COLOR_GPIO_Port GPIOA
#define COLOR_EXTI_IRQn EXTI2_TSC_IRQn
#define USER_VR_Pin GPIO_PIN_3
#define USER_VR_GPIO_Port GPIOA
#define USER_BTN1_Pin GPIO_PIN_4
#define USER_BTN1_GPIO_Port GPIOA
#define USER_BTN1_EXTI_IRQn EXTI4_IRQn
#define USER_BTN2_Pin GPIO_PIN_6
#define USER_BTN2_GPIO_Port GPIOA
#define USER_BTN2_EXTI_IRQn EXTI9_5_IRQn
#define USER_LED_Pin GPIO_PIN_1
#define USER_LED_GPIO_Port GPIOB
#define ID4_Pin GPIO_PIN_15
#define ID4_GPIO_Port GPIOA
#define ID1_Pin GPIO_PIN_3
#define ID1_GPIO_Port GPIOB
#define ID1_EXTI_IRQn EXTI3_IRQn
#define ID8_Pin GPIO_PIN_4
#define ID8_GPIO_Port GPIOB
#define ID2_Pin GPIO_PIN_5
#define ID2_GPIO_Port GPIOB
#define ID2_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
