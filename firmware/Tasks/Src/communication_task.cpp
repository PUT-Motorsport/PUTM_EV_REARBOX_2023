/**
 ******************************************************************************
 * @file           : communication_task.cpp
 * @brief          : CAN communication task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "communication_task.h"
#include "can_interface.hpp"
#include "cmsis_os2.h"
#include "data.h"
#include "fdcan.h"
#include "iwdg.h"

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
void Communication_Task(void* argument) {
    for(;;) {
        // Send
        PUTM_CAN::RearboxSafety rearbox_safety = {
            .safety_rfu1 = safety.rfu1,
            .safety_rfu2 = safety.rfu2,
            .safety_asms = safety.asms,
            .safety_fw = safety.fw,
            .safety_hv = safety.hv,
            .safety_res = safety.res,
            .safety_hvd = safety.hvd,
            .safety_inv = safety.inv,
            .safety_wheel_fl = safety.wheel_fl,
            .safety_wheel_fr = safety.wheel_fr,
            .safety_wheel_rl = safety.wheel_rl,
            .safety_wheel_rr = safety.wheel_rr,
        };
        auto safety_message = PUTM_CAN::Can_tx_message<PUTM_CAN::RearboxSafety>(rearbox_safety, PUTM_CAN::can_tx_header_REARBOX_SAFETY);
        safety_message.send(hfdcan1);

        PUTM_CAN::RearboxTemperature rearbox_temperature = {
            .mono_temperature = temperature.mono,
            .coolant_temperature_in = temperature.coolant_in,
            .coolant_temperature_out = temperature.coolant_out,
            .oil_temperature_l = temperature.oil_l,
            .oil_temperature_r = temperature.oil_r,
        };
        auto temperature_message = PUTM_CAN::Can_tx_message<PUTM_CAN::RearboxTemperature>(rearbox_temperature, PUTM_CAN::can_tx_header_REARBOX_TEMPERATURE);
        temperature_message.send(hfdcan1);

        PUTM_CAN::RearboxMiscellaneous rearbox_miscellaneous = {
            .coolant_pressure_in = data.coolant_pressure_in,
            .coolant_pressure_out = data.coolant_pressure_out,
            .suspension_l = data.suspension_l,
            .suspension_r = data.suspension_r,
        };
        auto miscellaneous_message =
            PUTM_CAN::Can_tx_message<PUTM_CAN::RearboxMiscellaneous>(rearbox_miscellaneous, PUTM_CAN::can_tx_header_REARBOX_MISCELLANEOUS);
        miscellaneous_message.send(hfdcan1);

        // Receive
        if(PUTM_CAN::can.get_pc_new_data()) {
            auto pc_data = PUTM_CAN::can.get_pc_main_data();
            if(osMutexAcquire(dataMutexHandle, osWaitForever) == osOK) {
                data.rtd = pc_data.rtd;
                osMutexRelease(dataMutexHandle);
            }
        }

        if(PUTM_CAN::can.get_front_data_main_new_data()) {
            auto front_data = PUTM_CAN::can.get_front_data_main_data();
            if(osMutexAcquire(dataMutexHandle, osWaitForever) == osOK) {
                if(front_data.is_braking) {
                    data.brake_light = true;
                } else {
                    data.brake_light = false;
                }

                osMutexRelease(dataMutexHandle);
            }
        }

        // Reset watchdog
        HAL_IWDG_Refresh(&hiwdg);

        osDelay(100);
    }
}
