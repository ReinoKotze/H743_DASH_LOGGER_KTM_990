/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


#include "w25q128.h"
#include "st7365_3.5Inch.h"
#include "lvgl.h"
#include "LVGL_LCD_LINK.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */




/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for init */
osThreadId_t initHandle;
const osThreadAttr_t init_attributes = {
  .name = "init",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh7,
};
/* Definitions for testing */
osThreadId_t testingHandle;
const osThreadAttr_t testing_attributes = {
  .name = "testing",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LVGL_Timer */
osThreadId_t LVGL_TimerHandle;
const osThreadAttr_t LVGL_Timer_attributes = {
  .name = "LVGL_Timer",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LVGL_Tick */
osThreadId_t LVGL_TickHandle;
const osThreadAttr_t LVGL_Tick_attributes = {
  .name = "LVGL_Tick",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Init_Functions(void *argument);
void Task_Testing(void *argument);
void LVGLTimer(void *argument);
void LVGLTick(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	lv_init();
	lv_port_disp_init();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of init */
  initHandle = osThreadNew(Init_Functions, NULL, &init_attributes);

  /* creation of testing */
  testingHandle = osThreadNew(Task_Testing, NULL, &testing_attributes);

  /* creation of LVGL_Timer */
  LVGL_TimerHandle = osThreadNew(LVGLTimer, NULL, &LVGL_Timer_attributes);

  /* creation of LVGL_Tick */
  LVGL_TickHandle = osThreadNew(LVGLTick, NULL, &LVGL_Tick_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Init_Functions */
/**
  * @brief  Function implementing the init thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Init_Functions */
void Init_Functions(void *argument)
{
  /* USER CODE BEGIN Init_Functions */

//    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);
//
//    /*Create a white label, set its text and align it to the center*/
//    lv_obj_t * label = lv_label_create(lv_screen_active());
//    lv_label_set_text(label, "Hello world");
//    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
//    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);


//
//	  (void)argument;
//
//	  lv_obj_t *screen = lv_screen_active();
//
//	  lv_obj_set_style_bg_color(screen,
//	                            lv_color_hex(0x003A57),
//	                            LV_PART_MAIN);
//
//	  lv_obj_set_style_bg_opa(screen,
//	                          LV_OPA_COVER,
//	                          LV_PART_MAIN);
//
//	  lv_obj_t *label = lv_label_create(screen);
//
//	  lv_label_set_text(label, "Hello world");
//
//	  lv_obj_set_style_text_color(label,
//	                               lv_color_hex(0xFFFFFF),
//	                               LV_PART_MAIN);
//
//	  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
//
//	  /* Force LVGL to redraw the screen on its next lv_timer_handler() call. */
//	  lv_obj_invalidate(screen);
//
//	  /* Create the UI once, then permanently end this task. */
//	  osThreadExit();
//
//	  /* USER CODE END Init_Functions */




  /* Infinite loop */
  for(;;)
  {


    osDelay(1);


  }
  /* USER CODE END Init_Functions */
}

/* USER CODE BEGIN Header_Task_Testing */
/**
* @brief Function implementing the testing thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Testing */
void Task_Testing(void *argument)
{
  /* USER CODE BEGIN Task_Testing */
  /* Infinite loop */
  for(;;)
  {

	HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

//	Fill(WHITE);
//	osDelay(200);
//	Fill(BLACK);
//    osDelay(200);

	// Change the active screen's background color



    osDelay(200);
  }
  /* USER CODE END Task_Testing */
}

/* USER CODE BEGIN Header_LVGLTimer */
/**
* @brief Function implementing the LVGL_Timer thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LVGLTimer */
void LVGLTimer(void *argument)
{
  /* USER CODE BEGIN LVGLTimer */
  /* Infinite loop */
  for(;;)
  {
	  lv_timer_handler();
	     osDelay(20);

  }
  /* USER CODE END LVGLTimer */
}

/* USER CODE BEGIN Header_LVGLTick */
/**
* @brief Function implementing the LVGL_Tick thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LVGLTick */
void LVGLTick(void *argument)
{
  /* USER CODE BEGIN LVGLTick */
  /* Infinite loop */
  for(;;)
  {
	  lv_tick_inc(10);
	    osDelay(10);
  }
  /* USER CODE END LVGLTick */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

