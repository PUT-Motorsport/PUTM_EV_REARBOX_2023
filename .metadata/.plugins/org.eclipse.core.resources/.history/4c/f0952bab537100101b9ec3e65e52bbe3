/**
 ******************************************************************************
 * @file           : safety_task.cpp
 * @brief          : Safety senses readout task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "safety_task.h"
#include "cmsis_os2.h"
#include "data.h"
#include "main.h"
#include "tca6416a.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern osMutexId_t safetyMutexHandle;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void Safety_Task(void* argument) {
    for(;;) {
        if(osMutexAcquire(safetyMutexHandle, osWaitForever) == osOK) {
            safety.rfu1 = TCA6416A_ReadPin(&htca, PIN_RFU1);
            safety.rfu2 = TCA6416A_ReadPin(&htca, PIN_RFU2);
            safety.asms = TCA6416A_ReadPin(&htca, PIN_ASMS);
            safety.fw = TCA6416A_ReadPin(&htca, PIN_FW);
            safety.hv = TCA6416A_ReadPin(&htca, PIN_HV);
            safety.res = TCA6416A_ReadPin(&htca, PIN_RES);
            safety.hvd = TCA6416A_ReadPin(&htca, PIN_HVD);
            safety.inv = TCA6416A_ReadPin(&htca, PIN_INV);
            safety.wheel_fl = TCA6416A_ReadPin(&htca, PIN_WHEEL_FL);
            safety.wheel_fr = TCA6416A_ReadPin(&htca, PIN_WHEEL_FR);
            safety.wheel_rl = TCA6416A_ReadPin(&htca, PIN_WHEEL_RL);
            safety.wheel_rr = TCA6416A_ReadPin(&htca, PIN_WHEEL_RR);

            safety.tripped = safety.rfu1 || safety.rfu2 || safety.asms || safety.fw || safety.hv || safety.res || safety.hvd || safety.inv || safety.wheel_fl ||
                             safety.wheel_fr || safety.wheel_rl || safety.wheel_rr;

            osMutexRelease(safetyMutexHandle);
        }

        osDelay(100);
    }
}
