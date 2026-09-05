# Display and SDRAM configuration

The project H743_DASH_LOGGER.ioc has been updated directly. These are the
settings to retain in STM32CubeMX/CubeIDE Device Configuration.

## FMC SDRAM bank 1
- Base address: 0xC0000000, 32 MB.
- 9 column bits; 13 row bits; 16-bit data; four internal banks.
- CAS latency: 3.
- SD clock period: 3 FMC clocks.
- Read burst: disabled. Read-pipe delay: 1.
- Timing cycles: load-to-active 3, exit-self-refresh 8, self-refresh time 5,
  row-cycle 8, write-recovery 4, row-precharge 3, row-to-column 3.
- FMC kernel source remains PLL2, 121.6 MHz; SDRAM clock approximately
  40.533 MHz. Do not copy another project's refresh count after changing clocks.

## SDRAM MPU region 2
- Base 0xC0000000; size 32 MB; full access; execution disabled.
- TEX level 1, cacheable disabled, bufferable disabled, shareable disabled.
- This is Normal non-cacheable memory. CPU D-cache remains enabled elsewhere.

## LCD FMC SRAM bank 1
- 16-bit asynchronous SRAM interface; extended mode disabled.
- Write FIFO disabled.
- Address setup 4; address hold 8; data setup 15; bus turnaround 1; access mode A.
- Preserve the existing data/control pin assignments and clocks.

## TE and timer
- PD3: GPIO_EXTI3, rising edge, no pull, label TE_LCD.
- EXTI3 interrupt enabled, priority 5.
- TIM2 is not used for TE; it is removed from the .ioc configuration.
- TIM6 continues to request LVGL timer servicing every 5 ms.
- Keep existing TIM1 RPM input-capture configuration.

## Custom code CubeMX does not configure
- Core/Src/User_Libs/bsp_sdram.c initializes the SDRAM:
  1 ms startup wait, precharge, eight auto-refresh cycles, burst length 2,
  sequential burst, CAS 3, single-location writes, refresh count 296.
  Count 296 applies to the current clock and the 64 ms/8192 refresh requirement
  at temperatures up to 85 C. Above 85 C this chip requires faster refresh.
- Core/Src/User_Libs/st7365_3.5Inch.c enables vertical-only TE (0x35, 0x00).
  This selects the TE output mode; it does not program the panel frame rate.
- Core/Src/User_Libs/ALTmain.cpp services timers and refreshes in one main-loop
  context. TE never calls LVGL or waits. A coalesced pending edge is retained
  if it arrives during rendering.
- After 50 ms without TE, a non-blocking 16/17/17 ms deadline schedule targets
  60 Hz. With TE present, the physical panel's TE rate controls refresh.
- Drivers/lv_conf.h retains LV_DEF_REFR_PERIOD=17 and LV_USE_OS=LV_OS_NONE.
- LCD transfers remain synchronous CPU writes from internal staging memory.
  No SDRAM diagnostics, per-byte verification, frame capture, or per-pixel
  barriers run in the active display path.
- STM32H743IITX_FLASH.ld must retain the .lvgl_draw_buffers NOLOAD section in
  RAM_D2 for the staging buffer. CubeMX does not manage this custom section.
- Preserve setup() and tasks() calls in main.c USER CODE regions.
- The GPIO EXTI callback is in the custom display library; CubeMX generates
  EXTI3_IRQHandler from the .ioc. Do not add a second copy.

## Checking actual rate
Watch lcd_te_period_ms (typically alternating 16/17 for a 60 Hz panel),
lcd_te_count, lcd_refresh_count, lcd_fallback_count, lcd_last_refresh_ms.
An increasing fallback counter means TE is absent for at least 50 ms.
The target is 60 refresh opportunities/second, not guaranteed 60 rendered FPS.
Rendering and synchronous transfers must fit the frame budget. Static screens
do not need to send pixels every frame.

## Validation
The firmware was compiled and linked. The generated dependency paths were
normalized for Windows make, and a subsequent incremental build was checked.
The .ioc was edited as text; CubeMX regeneration was not run in this session.
After regeneration, review the diff and build to confirm the custom linker
section and USER CODE calls remain intact.