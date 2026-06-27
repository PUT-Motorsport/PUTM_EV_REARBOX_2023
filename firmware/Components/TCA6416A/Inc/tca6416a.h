/**
 ******************************************************************************
 * @file           : tca6416a.h
 * @brief          : TCA6416A library
 *
 ******************************************************************************
 */

#ifndef __TCA6416A_H__
#define __TCA6416A_H__

/* Public includes -----------------------------------------------------------*/
#include "stdbool.h"
#include "stdint.h"
#include "stm32g4xx_hal.h"

/* Public typedefs -----------------------------------------------------------*/
typedef struct {
    I2C_HandleTypeDef* hi2c;
    uint8_t i2caddr;
    uint16_t pinState;
    uint16_t pinModes;
} TCA6416A_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/
#define TCA_PIN_SET 1
#define TCA_PIN_RESET 0
#define TCA_PIN_INPUT 0
#define TCA_PIN_OUTPUT 1

#define TCA_REG_INPUT0 0x00
#define TCA_REG_INPUT1 0x01
#define TCA_REG_OUTPUT0 0x02
#define TCA_REG_OUTPUT1 0x03
#define TCA_REG_CONFIG0 0x06
#define TCA_REG_CONFIG1 0x07

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern TCA6416A_Handle_TypeDef htca;

#ifdef __cplusplus
extern "C" {
#endif

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Initialize TCA6416A
 * @param  tca: TCA6416A handle
 * @param  hi2c: I2C handle
 * @param  addr_bit: I2C address bit
 * @retval true if successful, false otherwise
 */
bool TCA6416A_Init(TCA6416A_Handle_TypeDef* tca, I2C_HandleTypeDef* hi2c, uint8_t addr_bit);

/**
 * @brief  Set pin mode
 * @param  tca: TCA6416A handle
 * @param  pin_num: Pin number
 * @param  mode: Pin mode
 * @retval None
 */
void TCA6416A_SetPinMode(TCA6416A_Handle_TypeDef* tca, uint8_t pin_num, int mode);

/**
 * @brief  Read pin mode
 * @param  tca: TCA6416A handle
 * @retval Pin modes
 */
uint16_t TCA6416A_ReadMode(TCA6416A_Handle_TypeDef* tca);

/**
 * @brief  Write pin mode
 * @param  tca: TCA6416A handle
 * @param  modes: Pin modes
 * @retval None
 */
void TCA6416A_WriteMode(TCA6416A_Handle_TypeDef* tca, uint16_t modes);

/**
 * @brief  Read pin
 * @param  tca: TCA6416A handle
 * @param  pin_number: Pin number
 * @retval Pin level
 */
int TCA6416A_ReadPin(TCA6416A_Handle_TypeDef* tca, uint8_t pin_number);

/**
 * @brief  Write pin
 * @param  tca: TCA6416A handle
 * @param  pin_number: Pin number
 * @param  level: Pin level
 * @retval None
 */
void TCA6416A_WritePin(TCA6416A_Handle_TypeDef* tca, uint8_t pin_number, uint8_t level);

/**
 * @brief  Read port
 * @param  tca: TCA6416A handle
 * @retval Port value
 */
uint16_t TCA6416A_ReadPort(TCA6416A_Handle_TypeDef* tca);

/**
 * @brief  Write port
 * @param  tca: TCA6416A handle
 * @param  i2cportval: Port value
 * @retval None
 */
void TCA6416A_WritePort(TCA6416A_Handle_TypeDef* tca, uint16_t i2cportval);

#ifdef __cplusplus
}
#endif

#endif /* __TCA6416A_H__ */
