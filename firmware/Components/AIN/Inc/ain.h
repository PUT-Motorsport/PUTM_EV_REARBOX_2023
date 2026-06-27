/**
 ******************************************************************************
 * @file           : ain.h
 * @brief          : AIN library
 *
 ******************************************************************************
 */

#ifndef __AIN_H__
#define __AIN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Public includes -----------------------------------------------------------*/
#include "ain_conf.h"
#include "stm32g4xx_hal.h"
#include <stdint.h>

/* Public typedefs -----------------------------------------------------------*/
/**
 * @brief A structure describing the analg input.
 *
 *        Contains Wheatstone bridge resistor values and the In-Amp gain.
 *
 *
 *       ┌───[ R3 ]──(Vout+)──[ Rx ]───┐
 *       │                             │
 * VIN ──┤                             ├── GND
 *       │                             │
 *       └───[ R1 ]──(Vout-)──[ R2 ]───┘
 *
 */

typedef struct {
    const int r0; // Nominal resistance
    const int r1; // Wheatstone bridge resistor values
    const int r2;
    const int r3;
    const float gain;  // Instrumentation amplifier gain
    uint16_t* adc_raw; // ADC register pointer
} AIN_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern uint16_t AIN_ADC1_REGISTER[AIN_ADC1_CHANNELS];
extern uint16_t AIN_ADC2_REGISTER[AIN_ADC2_CHANNELS];

extern AIN_Handle_TypeDef hain_mono_temperature;
extern AIN_Handle_TypeDef hain_coolant_temperature_in;
extern AIN_Handle_TypeDef hain_coolant_temperature_out;

extern AIN_Handle_TypeDef hain_coolant_pressure_in;
extern AIN_Handle_TypeDef hain_coolant_pressure_out;
extern AIN_Handle_TypeDef hain_oil_temperature_l;
extern AIN_Handle_TypeDef hain_oil_temperature_r;
extern AIN_Handle_TypeDef hain_suspension_potentiometer_l;
extern AIN_Handle_TypeDef hain_suspension_potentiometer_r;

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Get resistance from analog input
 * @param  handle: AIN handle
 * @retval Resistance in Ohms
 */
float AIN_GetResistance(AIN_Handle_TypeDef* handle);

/**
 * @brief  Get temperature from analog input
 * @param  handle: AIN handle
 * @retval Temperature in Celsius
 */
uint8_t AIN_GetTemperature(AIN_Handle_TypeDef* handle);

/**
 * @brief  Get pressure from analog input
 * @param  handle: AIN handle
 * @retval Pressure in Bars
 */
uint8_t AIN_GetPressure(AIN_Handle_TypeDef* handle);

#ifdef __cplusplus
}
#endif

#endif /* __AIN_H__ */
