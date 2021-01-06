#include "../inc/CommandConsole.h"
#include "../inc/SHG_runner.h"
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
#define WELCOME_STRING "******Welcome! This is the Smart Hydroponic Greenhouse!******\n\r"
#define PRESENTATION_STRING "Write 'help' to have the list of available commands.\n\r"

/* USER CODE BEGIN Header_CommandConsole */
/**
* @brief Function implementing the UartRX thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CommandConsole */

/*****************COMMANDS TODO*****************/
/*
- start         -> to start the SHG (read from sensors and write to actuators);
- log           -> to output info messages about the recent history of the machine;
- status        -> to outupt the values of the environmental variables;
- clear         -> clear the UART command line;
- help          -> to show the available commands;
- stop          -> pause the SHG;
- setThs  -> force the three thresholds to a user defined thresholds;
- getTresholds  -> print the three thresholds to the user;
- reset         -> reset to the default state of the machine;
*/
/***********************************************/

void CommandConsole(void const * argument)
{
  enum command  SHG_cmd = stop; //DEFAULT VALUE
  //stamp to UART2 the welcome string
  TM_USART_Puts(USART2,WELCOME_STRING);
  TM_USART_Puts(USART2,PRESENTATION_STRING);
  
  /* USER CODE BEGIN CommandConsole */
  /* Infinite loop */
  for(;;)
  {
    TM_USART_Puts(USART2,"UART2 NEUROMORPHIC PURE IOO\n\r");
    osDelay(1000);
  }
  /* USER CODE END CommandConsole */
}

