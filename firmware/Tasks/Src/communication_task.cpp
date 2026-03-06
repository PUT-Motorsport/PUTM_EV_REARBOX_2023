#include "communication_task.h"
#include "can_driver.hpp" 
#include "PUTM_CAN_M.h"
#include "cmsis_os2.h"
#include "data.h"
#include "fdcan.h"
#include "iwdg.h"

extern osMutexId_t dataMutexHandle;
putm_ev_can::CanDriver can_driver; 

void Communication_Task(void* argument) {

    can_driver.RegisterCallback<PUTM_CAN_M_front_data_t>(
        PUTM_CAN_M_FRONT_DATA_FRAME_ID, 
        [](const PUTM_CAN_M_front_data_t& front_data) {
            HAL_IWDG_Refresh(&hiwdg); // Refresh na odebranie ramki
            if (osMutexAcquire(dataMutexHandle, 0) == osOK) {
                data.brake_light = front_data.is_braking;
                osMutexRelease(dataMutexHandle);
            }
        }
    );

    for(;;) {


        PUTM_CAN_M_rearbox_safety_t safety_msg = {
            .safety_tsmp = (uint8_t)safety.TSMP,
            .safety_hv_battery = (uint8_t)safety.hv,
            .safety_inv_hv = (uint8_t)safety.inv_hv,
            .safety_hvd = (uint8_t)safety.hvd,
            .safety_inv = (uint8_t)safety.inv,
            .safety_wheel_fl = (uint8_t)safety.wheel_fl,
            .safety_wheel_fr = (uint8_t)safety.wheel_fr,
            .safety_wheel_rl = (uint8_t)safety.wheel_rl,
            .safety_wheel_rr = (uint8_t)safety.wheel_rr,
            .safety_suspension_rl = (uint8_t)safety.sus_rl,
            .safety_suspension_rr = (uint8_t)safety.sus_rr,
            .safety_motor_front = (uint8_t)safety.motor_front
        };
        can_driver.Send(PUTM_CAN_M_REARBOX_SAFETY_FRAME_ID, safety_msg);


        PUTM_CAN_M_rearbox_temperature_t temp_msg = {
            .mono_temperature = (uint8_t)temperature.mono,
            .coolant_temperature_in = (uint8_t)temperature.coolant_in,
            .coolant_temperature_out = (uint8_t)temperature.coolant_out,
            .oil_temperature_l = (uint8_t)temperature.oil_l,
            .oil_temperature_r = (uint8_t)temperature.oil_r
        };
        can_driver.Send(PUTM_CAN_M_REARBOX_TEMPERATURE_FRAME_ID, temp_msg);

        osDelay(100);
    }
}