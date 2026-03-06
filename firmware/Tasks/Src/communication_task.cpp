#include "communication_task.h"
#include "can_driver.hpp" 
#include "PUTM_CAN_M.h"
#include "cmsis_os2.h"
#include "data.h"
#include "fdcan.h"
#include "iwdg.h"

extern osMutexId_t dataMutexHandle;

putm_ev_can::CanDriver can_m; 

void Communication_Task(void* argument) {
    
    can_m.Init(&hfdcan1);

    data.rtd_2 = -1;
    data.rtd_2_prev = -1;
    data.rtd_edge = 0;

    can_m.RegisterCallback<PUTM_CAN_M_front_data_t>(
        PUTM_CAN_M_FRONT_DATA_FRAME_ID, 
        [](const PUTM_CAN_M_front_data_t& front_data) {
           // HAL_IWDG_Refresh(&hiwdg); // Refresh na odebranie ramki
            if (osMutexAcquire(dataMutexHandle, 0) == osOK) {
                data.brake_light = front_data.is_braking;
                osMutexRelease(dataMutexHandle);
            }
        }
    );

    can_m.RegisterCallback<PUTM_CAN_M_pc_main_data_t>(
        PUTM_CAN_M_PC_MAIN_DATA_FRAME_ID, 
        [](const PUTM_CAN_M_pc_main_data_t& pc_data) {
            if (osMutexAcquire(dataMutexHandle, 0) == osOK) {
                data.rtd = pc_data.rtd;
                data.rtd_2_prev = data.rtd_2;
                data.rtd_2 = data.rtd;

                // Edge detection
                if (data.rtd_2_prev == 0 && data.rtd_2 == 1) {
                    data.rtd_edge = 1;
                } else if (data.rtd_2_prev == 0 && data.rtd_2 == 0) {
                    data.rtd_edge = 0;
                }
                
                osMutexRelease(dataMutexHandle);
            }
        }
    );

    for(;;) {

        PUTM_CAN_M_rearbox_safety_t safety_msg = {
            .safety_tsmp = (uint8_t)safety.TSMP,
            .safety_rfu = 0, 
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
        can_m.Send(PUTM_CAN_M_REARBOX_SAFETY_FRAME_ID, safety_msg);


        PUTM_CAN_M_rearbox_temperature_t temp_msg = {
            .mono_temperature = (uint8_t)temperature.mono,
            .coolant_temperature_in = (uint8_t)temperature.coolant_in,
            .coolant_temperature_out = (uint8_t)temperature.coolant_out,
            .oil_temperature_l = (uint8_t)temperature.oil_l,
            .oil_temperature_r = (uint8_t)temperature.oil_r
        };
        can_m.Send(PUTM_CAN_M_REARBOX_TEMPERATURE_FRAME_ID, temp_msg);


        PUTM_CAN_M_rearbox_miscellaneous_t misc_msg = {
            .coolant_pressure_in = (uint8_t)data.coolant_pressure_in,
            .coolant_pressure_out = (uint8_t)data.coolant_pressure_out,
            .suspension_l = (uint16_t)data.suspension_l,
            .suspension_r = (uint16_t)data.suspension_r
        };
        can_m.Send(PUTM_CAN_M_REARBOX_MISCELLANEOUS_FRAME_ID, misc_msg);

        osDelay(100);
    }
}