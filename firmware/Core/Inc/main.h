/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define BRAKE_LIGHT_Pin GPIO_PIN_13
#define BRAKE_LIGHT_GPIO_Port GPIOC
#define RTDS_Pin GPIO_PIN_14
#define RTDS_GPIO_Port GPIOC
#define ASSI_BUZZER_Pin GPIO_PIN_15
#define ASSI_BUZZER_GPIO_Port GPIOC
#define HSE_IN_Pin GPIO_PIN_0
#define HSE_IN_GPIO_Port GPIOF
#define HSE_OUT_Pin GPIO_PIN_1
#define HSE_OUT_GPIO_Port GPIOF
#define ASSI_LED_R_Pin GPIO_PIN_0
#define ASSI_LED_R_GPIO_Port GPIOC
#define ASSI_LED_G_Pin GPIO_PIN_1
#define ASSI_LED_G_GPIO_Port GPIOC
#define MONO_TEMPERATURE_Pin GPIO_PIN_2
#define MONO_TEMPERATURE_GPIO_Port GPIOC
#define WATER_TEMPERATURE1_Pin GPIO_PIN_3
#define WATER_TEMPERATURE1_GPIO_Port GPIOC
#define WATER_TEMPERATURE2_Pin GPIO_PIN_0
#define WATER_TEMPERATURE2_GPIO_Port GPIOA
#define WATER_PRESSURE1_Pin GPIO_PIN_1
#define WATER_PRESSURE1_GPIO_Port GPIOA
#define WATER_PRESSURE2_Pin GPIO_PIN_2
#define WATER_PRESSURE2_GPIO_Port GPIOA
#define ASSI_LED_B_Pin GPIO_PIN_3
#define ASSI_LED_B_GPIO_Port GPIOA
#define ANALOG_OFFSET1_Pin GPIO_PIN_4
#define ANALOG_OFFSET1_GPIO_Port GPIOA
#define ANALOG_OFFSET2_Pin GPIO_PIN_5
#define ANALOG_OFFSET2_GPIO_Port GPIOA
#define ANALOG_INPUT1_Pin GPIO_PIN_6
#define ANALOG_INPUT1_GPIO_Port GPIOA
#define ANALOG_INPUT2_Pin GPIO_PIN_7
#define ANALOG_INPUT2_GPIO_Port GPIOA
#define POTENTIOMETER_L_Pin GPIO_PIN_4
#define POTENTIOMETER_L_GPIO_Port GPIOC
#define POTENTIOMETER_R_Pin GPIO_PIN_5
#define POTENTIOMETER_R_GPIO_Port GPIOC
#define SENSE_OUT_Pin GPIO_PIN_0
#define SENSE_OUT_GPIO_Port GPIOB
#define SENSE_ADDRESS_IN0_Pin GPIO_PIN_1
#define SENSE_ADDRESS_IN0_GPIO_Port GPIOB
#define SENSE_ADDRESS_IN1_Pin GPIO_PIN_2
#define SENSE_ADDRESS_IN1_GPIO_Port GPIOB
#define PUMP2_Pin GPIO_PIN_10
#define PUMP2_GPIO_Port GPIOB
#define PUMP1_Pin GPIO_PIN_11
#define PUMP1_GPIO_Port GPIOB
#define CAN2_RX_Pin GPIO_PIN_12
#define CAN2_RX_GPIO_Port GPIOB
#define CAN2_TX_Pin GPIO_PIN_13
#define CAN2_TX_GPIO_Port GPIOB
#define FAN_R_Pin GPIO_PIN_14
#define FAN_R_GPIO_Port GPIOB
#define FAN_L_Pin GPIO_PIN_15
#define FAN_L_GPIO_Port GPIOB
#define SAFETY_RESET_Pin GPIO_PIN_6
#define SAFETY_RESET_GPIO_Port GPIOC
#define SAFETY_INT_Pin GPIO_PIN_7
#define SAFETY_INT_GPIO_Port GPIOC
#define SAFETY_SCL_Pin GPIO_PIN_8
#define SAFETY_SCL_GPIO_Port GPIOC
#define SAFETY_SDA_Pin GPIO_PIN_9
#define SAFETY_SDA_GPIO_Port GPIOC
#define LOAD_CELL_SDIO_Pin GPIO_PIN_8
#define LOAD_CELL_SDIO_GPIO_Port GPIOA
#define LOAD_CELL_SCLK_Pin GPIO_PIN_9
#define LOAD_CELL_SCLK_GPIO_Port GPIOA
#define LOAD_CELL_DRDY_Pin GPIO_PIN_10
#define LOAD_CELL_DRDY_GPIO_Port GPIOA
#define CAN_RX_Pin GPIO_PIN_11
#define CAN_RX_GPIO_Port GPIOA
#define CAN_TX_Pin GPIO_PIN_12
#define CAN_TX_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define I2C_SCL_Pin GPIO_PIN_15
#define I2C_SCL_GPIO_Port GPIOA
#define UART_TX_Pin GPIO_PIN_10
#define UART_TX_GPIO_Port GPIOC
#define UART_RX_Pin GPIO_PIN_11
#define UART_RX_GPIO_Port GPIOC
#define SPI_MOSI_Pin GPIO_PIN_12
#define SPI_MOSI_GPIO_Port GPIOC
#define SPI_SCLK_Pin GPIO_PIN_3
#define SPI_SCLK_GPIO_Port GPIOB
#define SPI_MISO_Pin GPIO_PIN_4
#define SPI_MISO_GPIO_Port GPIOB
#define SENSE_ENABLE_PUMPS_Pin GPIO_PIN_5
#define SENSE_ENABLE_PUMPS_GPIO_Port GPIOB
#define SENSE_ENABLE_FANS_Pin GPIO_PIN_6
#define SENSE_ENABLE_FANS_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_7
#define I2C_SDA_GPIO_Port GPIOB
#define BOOT_SELECT_Pin GPIO_PIN_8
#define BOOT_SELECT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
/**
 * @brief Human-friendly aliases
 */

// TIM2
#define htim_pump htim2
#define TIM_CHANNEL_PUMP1 TIM_CHANNEL_4
#define TIM_CHANNEL_PUMP2 TIM_CHANNEL_3

// TIM15
#define htim_fan htim15
#define TIM_CHANNEL_FAN_L TIM_CHANNEL_2
#define TIM_CHANNEL_FAN_R TIM_CHANNEL_1

// ADC1
#define ADC_CHANNEL_MONO_TEMPERATURE 0
#define ADC_CHANNEL_COOLANT_IN_PRESSURE 2
#define ADC_CHANNEL_COOLANT_OUT_PRESSURE 3
#define ADC_CHANNEL_COOLANT_IN_TEMPERATURE 4
#define ADC_CHANNEL_COOLANT_OUT_TEMPERATURE 5

// ADC2
#define ADC_CHANNEL_OIL_L_TEMPERATURE 0
#define ADC_CHANNEL_OIL_R_TEMPERATURE 1
#define ADC_CHANNEL_SUSPENSION_POTENTIOMETER_L 2
#define ADC_CHANNEL_SUSPENSION_POTENTIOMETER_R 3

// GPIO
#define PIN_ERROR_LED 8
#define PIN_SAFETY_LED 9
#define PIN_FUSE_LED 10
#define PIN_RFU2 0
#define PIN_RFU1 1
#define PIN_ASMS 2
#define PIN_FW 3
#define PIN_HV 4
#define PIN_RES 5
#define PIN_HVD 6
#define PIN_INV 7
#define PIN_WHEEL_FL 12
#define PIN_WHEEL_FR 13
#define PIN_WHEEL_RL 14
#define PIN_WHEEL_RR 15
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
