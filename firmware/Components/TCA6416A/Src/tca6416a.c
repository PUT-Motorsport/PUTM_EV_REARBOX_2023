/**
 ******************************************************************************
 * @file           : tca6416a.c
 * @brief          : TCA6416A library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tca6416a.h"
#include "main.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
TCA6416A_Handle_TypeDef htca = {
    .hi2c = NULL,
    .i2caddr = 0,
    .pinState = 0,
    .pinModes = 0,
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
bool TCA6416A_Init(TCA6416A_Handle_TypeDef* tca, I2C_HandleTypeDef* hi2c, uint8_t addr_bit) {
    tca->hi2c = hi2c;
    tca->i2caddr = 0x20 | addr_bit;

    if(HAL_I2C_IsDeviceReady(tca->hi2c, tca->i2caddr << 1, 2, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }

    TCA6416A_ReadPort(tca);
    TCA6416A_ReadMode(tca);

    return true;
}

void TCA6416A_SetPinMode(TCA6416A_Handle_TypeDef* tca, uint8_t pin_number, int mode) {
    uint16_t mask = 1 << pin_number;

    if(mode == TCA_PIN_INPUT) {
        tca->pinModes |= mask;
    } else {
        tca->pinModes &= ~mask;
    }

    TCA6416A_WriteMode(tca, tca->pinModes);
}

uint16_t TCA6416A_ReadMode(TCA6416A_Handle_TypeDef* tca) {
    uint8_t data[2];
    HAL_I2C_Mem_Read(tca->hi2c, tca->i2caddr << 1, TCA_REG_CONFIG0, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY);

    tca->pinModes = data[0] | (data[1] << 8);

    return tca->pinModes;
}

void TCA6416A_WriteMode(TCA6416A_Handle_TypeDef* tca, uint16_t modes) {
    uint8_t data[3];
    data[0] = TCA_REG_CONFIG0;
    data[1] = modes & 0xFF;
    data[2] = modes >> 8;

    HAL_I2C_Master_Transmit(tca->hi2c, tca->i2caddr << 1, data, 3, HAL_MAX_DELAY);

    tca->pinModes = modes;
}

int TCA6416A_ReadPin(TCA6416A_Handle_TypeDef* tca, uint8_t pin_number) {
    uint16_t mask = 1 << pin_number;

    TCA6416A_ReadPort(tca);

    if((tca->pinState & mask) == mask) {
        return 1;
    } else {
        return 0;
    }
}

void TCA6416A_WritePin(TCA6416A_Handle_TypeDef* tca, uint8_t pin_number, uint8_t level) {
    uint16_t mask = 1 << pin_number;

    if(level == TCA_PIN_SET) {
        tca->pinState |= mask;
    } else {
        tca->pinState &= ~mask;
    }

    TCA6416A_WritePort(tca, tca->pinState);
}

uint16_t TCA6416A_ReadPort(TCA6416A_Handle_TypeDef* tca) {
    uint8_t data[2];
    HAL_I2C_Mem_Read(tca->hi2c, tca->i2caddr << 1, TCA_REG_INPUT0, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY);
    uint16_t input = data[0] | (data[1] << 8);
    tca->pinState = (tca->pinState & ~tca->pinModes) | (input & tca->pinModes);

    return tca->pinState;
}

void TCA6416A_WritePort(TCA6416A_Handle_TypeDef* tca, uint16_t i2cportval) {
    uint8_t data[3];
    data[0] = TCA_REG_OUTPUT0;
    data[1] = i2cportval & 0xFF;
    data[2] = i2cportval >> 8;

    HAL_I2C_Master_Transmit(tca->hi2c, tca->i2caddr << 1, data, 3, HAL_MAX_DELAY);

    tca->pinState = i2cportval;
}
