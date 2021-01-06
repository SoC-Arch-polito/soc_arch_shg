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
- setThs        -> force the three thresholds to a user defined thresholds;
- getThs        -> print the three thresholds to the user;
- reset         -> reset to the default state of the machine;
*/
/***********************************************/

// receive the command and return the related enum
enum command ParseCommand(char* cmd);

void CommandConsole(void const * argument)
{
  enum command cmd;
  char comm[COMMANDLENGTH];
  //stamp to UART2 the welcome string
  TM_USART_Puts(USART2,WELCOME_STRING);
  TM_USART_Puts(USART2,PRESENTATION_STRING);
  
  /* USER CODE BEGIN CommandConsole */
  /* Infinite loop */
  for(;;)
  {
    /* Waiting for \n at the end of string */
    if(TM_USART_Gets(USART2, comm, sizeof(comm))){
      //in base on the command we do a different stuff
      cmd = ParseCommand(comm);
      switch (cmd){
        case start:
          TM_USART_Puts(USART2,WELCOME_STRING);
          break;
        case log:
          break;
        case status:
          break;
        case clear:
          break;
        case help:
          break;
        case stop:
          break;
        case setThs:
          break;
        case getThs:
          break;
        case reset:
          break;
        default:
          TM_USART_Puts(USART2,UNKNOWNCOMMAND);
          break;
      }
    }
    TM_USART_Puts(USART2,"UART2 NEUROMORPHIC PURE IOO\n\r");
    osDelay(1000);
  }
  /* USER CODE END CommandConsole */
}

enum command ParseCommand(char* cmd) {
    enum command  SHG_cmd = error; //DEFAULT VALUE
    if(strcmp(cmd, "start") == 0){
      SHG_cmd = start;
    } else if(strcmp(cmd, "log") == 0){
      SHG_cmd = log;
    } else if(strcmp(cmd, "status") == 0){
      SHG_cmd = status;
    } else if(strcmp(cmd, "clear") == 0){
      SHG_cmd = clear;
    } else if(strcmp(cmd, "help") == 0){
      SHG_cmd = help;
    } else if(strcmp(cmd, "stop") == 0){
      SHG_cmd = stop;
    } else if(strcmp(cmd, "setThs") == 0){
      SHG_cmd = setThs;
    } else if(strcmp(cmd, "getThs") == 0){
      SHG_cmd = getThs;
    } else if(strcmp(cmd, "stop") == 0){
      SHG_cmd = stop;
    }
    return SHG_cmd;
  }

