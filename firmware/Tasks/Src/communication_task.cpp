/**
 ******************************************************************************
 * @file           : communication_task.cpp
 * @brief          : CAN communication task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "communication_task.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "data.h"
#include "fdcan.h"
#include "PUTM_CAN_M.h"
#include "can_driver.hpp"

/* Typedefs ------------------------------------------------------------------*/
enum class CanRxMsgType : uint8_t { PC_MAIN_DATA, FRONT_DATA };

struct CanRxMsg {
    CanRxMsgType type;
    union {
        PUTM_CAN_M_pc_main_data_t pc_main;
        PUTM_CAN_M_front_data_t   front;
    };
};

/* Defines -------------------------------------------------------------------*/
#define CAN_RX_QUEUE_LEN 16

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static QueueHandle_t can_rx_queue;

/* Public variables ----------------------------------------------------------*/
extern osMutexId_t dataMutexHandle;

/* Private function prototypes -----------------------------------------------*/
static void process_rx_queue(void);

/* Public functions ----------------------------------------------------------*/

static void process_rx_queue(void)
{
    CanRxMsg msg;
    while (xQueueReceive(can_rx_queue, &msg, 0) == pdTRUE)
    {
        if (osMutexAcquire(dataMutexHandle, osWaitForever) != osOK) continue;

        switch (msg.type)
        {
        case CanRxMsgType::PC_MAIN_DATA:
            data.rtd        = msg.pc_main.rtd;
            data.rtd_2_prev = data.rtd_2;
            data.rtd_2      = data.rtd;
            if (data.rtd_2_prev == 0 && data.rtd_2 == 1) data.rtd_edge = 1;
            if (data.rtd_2_prev == 0 && data.rtd_2 == 0) data.rtd_edge = 0;
            break;

        case CanRxMsgType::FRONT_DATA:
            data.brake_light = msg.front.is_braking;
            break;
        }

        osMutexRelease(dataMutexHandle);
    }
}

void Communication_Task(void* argument)
{
    data.rtd_2      = -1;
    data.rtd_2_prev = -1;
    data.rtd_edge   =  0;

    can_rx_queue = xQueueCreate(CAN_RX_QUEUE_LEN, sizeof(CanRxMsg));

    putm_ev_can::CanDriver can_m;

    if (!can_m.Init(&hfdcan1))
    {
        Error_Handler();
    }

    can_m.RegisterCallback<PUTM_CAN_M_pc_main_data_t>(
        PUTM_CAN_M_PC_MAIN_DATA_FRAME_ID,
        [](const PUTM_CAN_M_pc_main_data_t& pc_main_data) {
            CanRxMsg msg{ .type = CanRxMsgType::PC_MAIN_DATA, .pc_main = pc_main_data };
            xQueueSendFromISR(can_rx_queue, &msg, nullptr);
        });

    can_m.RegisterCallback<PUTM_CAN_M_front_data_t>(
        PUTM_CAN_M_FRONT_DATA_FRAME_ID,
        [](const PUTM_CAN_M_front_data_t& front_data) {
            CanRxMsg msg{ .type = CanRxMsgType::FRONT_DATA, .front = front_data };
            xQueueSendFromISR(can_rx_queue, &msg, nullptr);
        });

    for (;;)
    {
        process_rx_queue();
        PUTM_CAN_M_rearbox_safety_t rearbox_safety = {
            .safety_tsmp          = safety.TSMP,
            .safety_rfu           = 0,
            .safety_hv_battery    = safety.hv,
            .safety_inv_hv        = safety.inv_hv,
            .safety_hvd           = safety.hvd,
            .safety_inv           = safety.inv,
            .safety_wheel_fl      = safety.wheel_fl,
            .safety_wheel_fr      = safety.wheel_fr,
            .safety_wheel_rl      = safety.wheel_rl,
            .safety_wheel_rr      = safety.wheel_rr,
            .safety_suspension_rl = safety.sus_rl,
            .safety_suspension_rr = safety.sus_rr,
            .safety_motor_front   = safety.motor_front,
        };
        can_m.Send(PUTM_CAN_M_REARBOX_SAFETY_FRAME_ID, rearbox_safety);

        PUTM_CAN_M_rearbox_temperature_t rearbox_temperature = {
            .mono_temperature        = temperature.mono,
            .coolant_temperature_in  = temperature.coolant_in,
            .coolant_temperature_out = temperature.coolant_out,
            .oil_temperature_l       = temperature.oil_l,
            .oil_temperature_r       = temperature.oil_r,
        };
        can_m.Send(PUTM_CAN_M_REARBOX_TEMPERATURE_FRAME_ID, rearbox_temperature);

        PUTM_CAN_M_rearbox_miscellaneous_t rearbox_miscellaneous = {
            .coolant_pressure_in  = data.coolant_pressure_in,
            .coolant_pressure_out = data.coolant_pressure_out,
            .suspension_l         = data.suspension_l,
            .suspension_r         = data.suspension_r,
        };
        can_m.Send(PUTM_CAN_M_REARBOX_MISCELLANEOUS_FRAME_ID, rearbox_miscellaneous);

       // HAL_IWDG_Refresh(&hiwdg);
        osDelay(100);
    }
}