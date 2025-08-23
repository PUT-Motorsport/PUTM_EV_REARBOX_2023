/**
 ******************************************************************************
 * @file           : data.c
 * @brief          : Rearbox data
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "data.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
Data_TypeDef data = {
    .led_test = true,
    .error_led = false,
    .safety_led = false,
    .fuse_led = false,
    .brake_light = false,
    .rtd = false,
    .rtd_prev = false,
    .rtd_buzzer = false,
    .assi = false,
    .assi_buzzer = false,
    .rtd_on_time = 0,
    .coolant_pressure_in = 0,
    .coolant_pressure_out = 0,
    .suspension_l = 0,
    .suspension_r = 0,
};

Safety_TypeDef safety = {
    .tripped = false,
    .sus_rl = false,
    .sus_rr = false,
    .TSMP = false,
    .motor_front = false,
    .hv = false,
    .inv_hv = false,
    .hvd = false,
    .inv = false,
    .wheel_fl = false,
    .wheel_fr = false,
    .wheel_rl = false,
    .wheel_rr = false,
};

Temperature_TypeDef temperature = {
    .mono = 0,
    .coolant_in = 0,
    .coolant_out = 0,
    .oil_l = 0,
    .oil_r = 0,
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
