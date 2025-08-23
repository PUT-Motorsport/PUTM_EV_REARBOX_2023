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
            safety.sus_rl = TCA6416A_ReadPin(&htca, PIN_RFU1);//sdc__sus_rl
            safety.sus_rr= TCA6416A_ReadPin(&htca, PIN_RFU2);//sdc_sus_rr
            safety.TSMP = TCA6416A_ReadPin(&htca, PIN_ASMS);//TSMP
            safety.motor_front = TCA6416A_ReadPin(&htca, PIN_FW);//motor front
            safety.hv = TCA6416A_ReadPin(&htca, PIN_HV);//TSAC
            safety.inv_hv = TCA6416A_ReadPin(&htca, PIN_RES);//inv hv sense
            safety.hvd = TCA6416A_ReadPin(&htca, PIN_HVD);
            safety.inv = TCA6416A_ReadPin(&htca, PIN_INV);
            safety.wheel_fl = TCA6416A_ReadPin(&htca, PIN_WHEEL_FL);
            safety.wheel_fr = TCA6416A_ReadPin(&htca, PIN_WHEEL_FR);
            safety.wheel_rl = TCA6416A_ReadPin(&htca, PIN_WHEEL_RL);
            safety.wheel_rr = TCA6416A_ReadPin(&htca, PIN_WHEEL_RR);

            safety.tripped = safety.sus_rl || safety.sus_rr || safety.TSMP || safety.motor_front || safety.hv || safety.inv_hv || safety.hvd || safety.inv || safety.wheel_fl ||
                             safety.wheel_fr || safety.wheel_rl || safety.wheel_rr;

            osMutexRelease(safetyMutexHandle);
        }

        osDelay(100);
    }
}
