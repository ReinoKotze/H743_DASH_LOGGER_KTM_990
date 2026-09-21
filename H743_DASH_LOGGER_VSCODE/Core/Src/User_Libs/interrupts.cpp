

#include "INCLUDES.hpp"

volatile uint32_t rpm = 0U;
volatile uint32_t rpm_last_capture_ms = 0U;
volatile uint32_t SPEED = 0U;
volatile uint32_t SPEED_last_capture_ms = 0U;
volatile uint32_t Pulse_Per_Rotation = 6U;
volatile uint32_t Wheel_Circumfrance = 2100U; /* mm */
volatile uint8_t lvgl_timer_due = 0U;
volatile uint8_t ADS1115_alert_ready_due = 0U;
volatile uint8_t CAN_int_due = 0U;

#define TIMER_CAPTURE_CLOCK_KHZ 240U

void Interrupts_StartTimers(void)
{
    if (HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1) != HAL_OK ||
        HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2) != HAL_OK ||
        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1) != HAL_OK ||
        HAL_TIM_Base_Start_IT(&htim6) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
    {
        const uint32_t period = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
        if (period != 0U)
        {
            rpm = (TIMER_CAPTURE_CLOCK_KHZ * 60U) / period;
            rpm_last_capture_ms = HAL_GetTick();
        }
    }

    if (htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        static uint8_t first_capture_seen = 0U;
        const uint32_t period = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
        if (first_capture_seen == 0U)
        {
            first_capture_seen = 1U;
            return;
        }

        const uint32_t pulses = Pulse_Per_Rotation;
        const uint32_t circumference = Wheel_Circumfrance;
        if (period != 0U && pulses != 0U)
        {
            const uint64_t numerator = (uint64_t)circumference * 240000ULL * 3600ULL;
            const uint64_t denominator = (uint64_t)period * pulses * 1000000ULL;
            SPEED = (uint32_t)(numerator / denominator);
            SPEED_last_capture_ms = HAL_GetTick();
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        lvgl_timer_due = 1U;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
    if (pin == TE_LCD_Pin)
    {
        lv_port_disp_te_isr();
    }
    else if (pin == ADS1115_alert_ready_Pin)
    {
        ADS1115_alert_ready_due = 1U;
    }
    else if (pin == CAN_INT_Pin)
    {
        CAN_int_due = 1U;
    }   
}
