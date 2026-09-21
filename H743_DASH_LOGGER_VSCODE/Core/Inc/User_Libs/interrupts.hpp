#ifndef USER_LIBS_INTERRUPTS_H
#define USER_LIBS_INTERRUPTS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint32_t rpm;
extern volatile uint32_t rpm_last_capture_ms;
extern volatile uint32_t SPEED;
extern volatile uint32_t SPEED_last_capture_ms;
extern volatile uint32_t Pulse_Per_Rotation;
extern volatile uint32_t Wheel_Circumfrance;
extern volatile uint8_t lvgl_timer_due;
extern volatile uint8_t ADS1115_alert_ready_due;
extern volatile uint8_t CAN_int_due;
void Interrupts_StartTimers(void);

#ifdef __cplusplus
}
#endif

#endif
