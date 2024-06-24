/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "communication_task.h"
#include "interface_task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for communicationTask */
osThreadId_t communicationTaskHandle;
const osThreadAttr_t communicationTask_attributes = {.name = "communicationTask", .priority = (osPriority_t)osPriorityNormal, .stack_size = 256 * 4};
/* Definitions for interfaceTask */
osThreadId_t interfaceTaskHandle;
const osThreadAttr_t interfaceTask_attributes = {.name = "interfaceTask", .priority = (osPriority_t)osPriorityLow, .stack_size = 128 * 4};
/* Definitions for dataMutex */
osMutexId_t dataMutexHandle;
const osMutexAttr_t dataMutex_attributes = {.name = "dataMutex"};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Communication_Task(void* argument);
void Interface_Task(void* argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */
    /* Create the mutex(es) */
    /* creation of dataMutex */
    dataMutexHandle = osMutexNew(&dataMutex_attributes);

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of communicationTask */
    communicationTaskHandle = osThreadNew(Communication_Task, NULL, &communicationTask_attributes);

    /* creation of interfaceTask */
    interfaceTaskHandle = osThreadNew(Interface_Task, NULL, &interfaceTask_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_Communication_Task */
/**
 * @brief  Function implementing the communicationTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_Communication_Task */
__weak void Communication_Task(void* argument) {
    /* USER CODE BEGIN Communication_Task */
    /* Infinite loop */
    for(;;) {
        osDelay(1);
    }
    /* USER CODE END Communication_Task */
}

/* USER CODE BEGIN Header_Interface_Task */
/**
 * @brief Function implementing the interfaceTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Interface_Task */
__weak void Interface_Task(void* argument) {
    /* USER CODE BEGIN Interface_Task */
    /* Infinite loop */
    for(;;) {
        osDelay(1);
    }
    /* USER CODE END Interface_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
