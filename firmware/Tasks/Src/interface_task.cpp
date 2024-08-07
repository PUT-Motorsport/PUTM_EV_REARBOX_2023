/**
 ******************************************************************************
 * @file           : interface_task.cpp
 * @brief          : Input/output interfacing task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "interface_task.h"
#include "ain.h"
#include "data.h"
#include "tca6416a.h"

#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "gpio.h"
#include "main.h"
#include "portable.h"
#include "task.h"

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
void Interface_Task(void* argument) {
    for(;;) {
        if(osMutexAcquire(dataMutexHandle, osWaitForever) == osOK) {
            // Analog inputs
            temperature.mono = AIN_GetTemperature(&hain_mono_temperature);
            temperature.coolant_in = AIN_GetTemperature(&hain_coolant_temperature_in);
            temperature.coolant_out = AIN_GetTemperature(&hain_coolant_temperature_out);
            temperature.oil_l = AIN_GetTemperature(&hain_oil_temperature_l);
            temperature.oil_r = AIN_GetTemperature(&hain_oil_temperature_r);

            data.coolant_pressure_in = AIN_GetPressure(&hain_coolant_pressure_in);
            data.coolant_pressure_out = AIN_GetPressure(&hain_coolant_pressure_out);
            data.suspension_l = AIN_GetResistance(&hain_suspension_potentiometer_l);
            data.suspension_r = AIN_GetResistance(&hain_suspension_potentiometer_r);

            // LEDs
            data.safety_led = safety.tripped;

            if(data.error_led || data.led_test) {
                TCA6416A_WritePin(&htca, PIN_ERROR_LED, TCA_PIN_SET);
            } else {
                TCA6416A_WritePin(&htca, PIN_ERROR_LED, TCA_PIN_RESET);
            }

            if(data.safety_led || data.led_test) {
                TCA6416A_WritePin(&htca, PIN_SAFETY_LED, TCA_PIN_SET);
            } else {
                TCA6416A_WritePin(&htca, PIN_SAFETY_LED, TCA_PIN_RESET);
            }

            if(data.fuse_led || data.led_test) {
                TCA6416A_WritePin(&htca, PIN_FUSE_LED, TCA_PIN_SET);
            } else {
                TCA6416A_WritePin(&htca, PIN_FUSE_LED, TCA_PIN_RESET);
            }

            // Brake Light
            if(data.brake_light) {
                HAL_GPIO_WritePin(BRAKE_LIGHT_GPIO_Port, BRAKE_LIGHT_Pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(BRAKE_LIGHT_GPIO_Port, BRAKE_LIGHT_Pin, GPIO_PIN_RESET);
            }

            // RTD
            if(data.rtd != data.rtd_prev) {
                if(data.rtd) {
                    HAL_GPIO_WritePin(RTDS_GPIO_Port, RTDS_Pin, GPIO_PIN_SET);
                    data.rtd_on_time = xTaskGetTickCount() * portTICK_PERIOD_MS;
                } else {
                    HAL_GPIO_WritePin(RTDS_GPIO_Port, RTDS_Pin, GPIO_PIN_RESET);
                }

                data.rtd_prev = data.rtd;
            }

            if(data.rtd) {
                if(xTaskGetTickCount() * portTICK_PERIOD_MS - data.rtd_on_time > RTD_SOUND_DURATION) {
                    data.rtd = false;
                }
            }

            osMutexRelease(dataMutexHandle);
        }

        osDelay(100);
    }
}
