#ifndef USER_LIBS_ADS1115_HPP
#define USER_LIBS_ADS1115_HPP

#include "i2c.h"
#include <stdint.h>

namespace ADS1115 {

constexpr uint8_t Address7Bit = 0x48U; // ADDR tied to GND.
constexpr uint8_t EngineChannel = 1U; // AIN1 relative to GND.
constexpr uint8_t AmbientChannel = 2U; // AIN2 relative to GND.

// Call after MX_I2C1_Init(). Configures ALERT/RDY as active-low conversion ready.
bool Setup(I2C_HandleTypeDef *i2c);

// Raw 16-bit register access. The ADS1115 transmits the high byte first.
bool ReadRegister(uint8_t reg, uint16_t *value);
bool WriteRegister(uint8_t reg, uint16_t value);

// Start a single conversion and service it from the main loop, never an ISR.
bool StartConversion(uint8_t channel);
void Service();

// Returns false until a valid sample has been received for this channel.
bool ReadMillivolts(uint8_t channel, int32_t *millivolts);

} // namespace ADS1115

#endif
