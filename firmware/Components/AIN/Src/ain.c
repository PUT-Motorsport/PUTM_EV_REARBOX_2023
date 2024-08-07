/**
 ******************************************************************************
 * @file           : ain.c
 * @brief          : AIN library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "ain.h"
#include "main.h"
#include <math.h>

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define NOMINAL_RESISTANCE 100.0f
#define BETA_VALUE 3950.0f
#define REFERENCE_TEMPERATURE 25.0f

/* Private variables ---------------------------------------------------------*/
AIN_Handle_TypeDef hain_mono_temperature = {1000, 3000, 1000, 2000, 4.09f, &AIN_ADC1_REGISTER[ADC_CHANNEL_MONO_TEMPERATURE]};
AIN_Handle_TypeDef hain_coolant_pressure_in = {1000, 3000, 1000, 2000, 4.09f, &AIN_ADC1_REGISTER[ADC_CHANNEL_COOLANT_IN_PRESSURE]};
AIN_Handle_TypeDef hain_coolant_pressure_out = {1000, 3000, 1000, 2000, 4.09f, &AIN_ADC1_REGISTER[ADC_CHANNEL_COOLANT_OUT_PRESSURE]};
AIN_Handle_TypeDef hain_coolant_temperature_in = {1000, 3000, 1000, 2000, 4.09f, &AIN_ADC1_REGISTER[ADC_CHANNEL_COOLANT_IN_TEMPERATURE]};
AIN_Handle_TypeDef hain_coolant_temperature_out = {1000, 3000, 1000, 2000, 4.09f, &AIN_ADC1_REGISTER[ADC_CHANNEL_COOLANT_OUT_TEMPERATURE]};
AIN_Handle_TypeDef hain_oil_temperature_l = {1000, 3000, 1000, 2000, 4.09f, &AIN_ADC2_REGISTER[ADC_CHANNEL_OIL_L_TEMPERATURE]};
AIN_Handle_TypeDef hain_oil_temperature_r = {1000, 3000, 1000, 2000, 4.09f, &AIN_ADC2_REGISTER[ADC_CHANNEL_OIL_R_TEMPERATURE]};
AIN_Handle_TypeDef hain_suspension_potentiometer_l = {1000, 3000, 1000, 2000, 4.09f, &AIN_ADC2_REGISTER[ADC_CHANNEL_SUSPENSION_POTENTIOMETER_L]};
AIN_Handle_TypeDef hain_suspension_potentiometer_r = {1000, 3000, 1000, 2000, 4.09f, &AIN_ADC2_REGISTER[ADC_CHANNEL_SUSPENSION_POTENTIOMETER_R]};

/* Public variables ----------------------------------------------------------*/
uint16_t AIN_ADC1_REGISTER[AIN_ADC1_CHANNELS];
uint16_t AIN_ADC2_REGISTER[AIN_ADC2_CHANNELS];

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
float AIN_GetResistance(AIN_Handle_TypeDef* handle) {
    if(handle == NULL || handle->adc_raw == NULL) {
        return 0.0f;
    }

    float v_out = (*(handle->adc_raw) * 3.3f) / 4095 / handle->gain;
    float resistance =
        (handle->r2 * handle->r3 + handle->r3 * (handle->r1 + handle->r2) * v_out / 3.3f) / (handle->r1 - (handle->r1 + handle->r2) * (v_out / 3.3f));

    return resistance;
}

uint8_t AIN_GetTemperature(AIN_Handle_TypeDef* handle) {
    if(handle == NULL || handle->adc_raw == NULL) {
        return 0;
    }

    float v_out = (*(handle->adc_raw) * 3.3f) / 4095 / handle->gain;
    float resistance =
        (handle->r2 * handle->r3 + handle->r3 * (handle->r1 + handle->r2) * v_out / 3.3f) / (handle->r1 - (handle->r1 + handle->r2) * (v_out / 3.3f));

    double steinhart = log(resistance / BETA_VALUE);
    steinhart /= BETA_VALUE;
    steinhart += 1.0f / REFERENCE_TEMPERATURE;
    steinhart = 1.0f / steinhart;

    return (uint8_t)steinhart;
}

uint8_t AIN_GetPressure(AIN_Handle_TypeDef* handle) {
    if(handle == NULL || handle->adc_raw == NULL) {
        return 0;
    }

    float v_out = (*(handle->adc_raw) * 3.3f) / 4095 / handle->gain;
    float pressure = 0.5f + (v_out - 0.5f) * 1000.0f / 4.0f;
    pressure /= 100.0f;

    return (uint8_t)pressure;
}
