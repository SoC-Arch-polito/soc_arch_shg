#include "../inc/OutputConsole.h"
#include "../../FreeRTOS-CMSIS/FreeRTOS.h"
#include "../../FreeRTOS-CMSIS/task.h"
#include "../..//FreeRTOS-CMSIS/main.h"
#include "../../FreeRTOS-CMSIS/cmsis_os.h"
#include <stm32f4xx_hal.h>
#include <defines.h>
#include <tm_stm32_disco.h>
#include <tm_stm32_spi.h>
#include <tm_stm32_usart.h>
#include <tm_stm32_i2c.h>
#include <string.h>
#include <stdio.h>
/* USER CODE BEGIN Header_OutputConsole */
/**
* @brief Function implementing the UartTX thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OutputConsole */

void OutputConsole(void const * argument)
{
  

  /* USER CODE BEGIN OutputConsole */
  /* Infinite loop */
  for(;;)
  {
    TM_USART_Puts(USART1,"UART1 NEUROMORPHIC PURE IOO\n\r");
    osDelay(1000);
  }
  /* USER CODE END OutputConsole */
}

