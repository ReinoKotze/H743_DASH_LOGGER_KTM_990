#ifndef MCP2518FD_HPP
#define MCP2518FD_HPP

#include "spi.h"
#include <stdint.h>

namespace MCP2518FD {
enum class SetupStatus : uint32_t {
    NotStarted, InProgress, InvalidSpi, SpiError, ClockTimeout,
    ConfigurationTimeout, ReadbackError, ConfigurationReady, NormalModeTimeout, Ready
};

// Call after GPIO/SPI1 init. Fixed 20 MHz crystal, PLL off, SYSCLK /1.
// ISO CAN FD: 500 kbit/s arbitration, 2 Mbit/s data, 80% sample points.
// SPI remains /256 (750 kHz on this board). True means Normal mode is reached.
bool Setup(SPI_HandleTypeDef *spi);

struct Frame {
    uint32_t id = 0;
    uint8_t length = 0;
    uint8_t data[64] = {};
    bool extended = false;
    bool fd = true;
    bool brs = true;
    bool remote = false; // Receive metadata; sending remote frames is unsupported.
};
// Main-loop only. Send true = queued, not acknowledged.
// Legal FD lengths: 0..8, 12, 16, 20, 24, 32, 48, 64. No implicit padding.
bool Send(const Frame &frame);
void Service(); // Call frequently; drains up to 4 frames to an 8-frame software queue.
bool Receive(Frame &frame); // Pops oldest; consume regularly to avoid dropped frames.

extern volatile uint32_t rx_count, rx_dropped, rx_overflows;
extern volatile uint32_t tx_queued, last_trec;
// Diagnostics: inspect setup_status and SPI status if setup or service fails.
extern volatile SetupStatus setup_status;
extern volatile uint32_t last_hal_status;
extern volatile uint32_t last_hal_error;
extern volatile uint32_t last_osc;
extern volatile uint32_t last_cicon;
extern volatile uint32_t device_id;
}
#endif
