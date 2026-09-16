#ifndef USER_LIBS_ADS1115_HPP
#define USER_LIBS_ADS1115_HPP

#include "i2c.h"
#include <stdint.h>

// Plain C symbols are easy to watch from any CubeIDE debugger stack frame.
extern "C" {
extern volatile uint32_t ads1115_i2c_error_count;
extern volatile uint32_t ads1115_conversion_timeout_count;
extern volatile uint32_t ads1115_sample_count;
extern volatile uint32_t ads1115_last_hal_status;
extern volatile uint32_t ads1115_last_hal_error;
// 1=address probe; 0x10+register=read; 0x20+register=write.
extern volatile uint32_t ads1115_last_error_stage;
extern volatile uint32_t ads1115_last_config_written;
extern volatile uint32_t ads1115_last_config_read;
extern volatile uint32_t ads1115_config_read_count;
}

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
