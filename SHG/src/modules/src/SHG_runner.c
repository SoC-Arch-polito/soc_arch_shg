#include "../inc/SHG_runner.h"
#include "../../FreeRTOS-CMSIS/FreeRTOS.h"
#include "../../FreeRTOS-CMSIS/task.h"
#include "../..//FreeRTOS-CMSIS/main.h"
#include "../../FreeRTOS-CMSIS/cmsis_os.h"

/* USER CODE BEGIN Header_SHG_runner */
/**
* @brief Function implementing the SHG_core thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SHG_runner */
void SHG_runner(void const * argument)
{
  /* USER CODE BEGIN SHG_runner */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END SHG_runner */
}
