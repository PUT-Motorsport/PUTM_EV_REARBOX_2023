/**
 ******************************************************************************
 * @file           : led_test_task.cpp
 * @brief          : LED test task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "led_test_task.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "data.h"
//We need this to use LOG levels, if this proves messy switch to numerical
#include "logging_task.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern osMutexId_t dataMutexHandle;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void Led_Test_Task(void* argument) {
	//Log_Send(LOG_INFO, "LED Test task started");

    for(;;) {
        osDelay(pdMS_TO_TICKS(3000));

        if(osMutexAcquire(dataMutexHandle, osWaitForever) == osOK) {
            data.led_test = false;
            osMutexRelease(dataMutexHandle);
            osThreadTerminate(osThreadGetId());
        }
    }
}
