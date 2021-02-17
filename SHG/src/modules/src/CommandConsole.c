#include "../inc/CommandConsole.h"
#include "../inc/SHG_runner.h"
#include "../../FreeRTOS-CMSIS/FreeRTOS.h"
#include "../../FreeRTOS-CMSIS/task.h"
#include "../..//FreeRTOS-CMSIS/main.h"
#include "../../FreeRTOS-CMSIS/cmsis_os.h"
#include "../../FreeRTOS-CMSIS/usart.h"
#include <stm32f4xx_hal.h>
#include <defines.h>
#include <tm_stm32_disco.h>
#include <tm_stm32_spi.h>
#include <tm_stm32_usart.h>
#include <tm_stm32_i2c.h>
#include <string.h>
#include <stdio.h>

#define BLUETOOTH_RX_ADDRESS (0x10<<1)
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
enum command ParseCommand(uint8_t cmd);
void CommandConsole(void const * argument)
{
  enum command cmd;
  uint8_t comm=0;
  //stamp to UART2 the welcome string
  TM_USART_Puts(USART2,WELCOME_STRING);
  TM_USART_Puts(USART2,PRESENTATION_STRING);
  
  /* USER CODE BEGIN CommandConsole */
  /* Infinite loop */

    
  if(TM_I2C_IsDeviceConnected(I2C1, BLUETOOTH_RX_ADDRESS)==TM_I2C_Result_Ok){
while(1){
       TM_I2C_ReadNoRegister(I2C1, BLUETOOTH_RX_ADDRESS, &comm);
//       snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Light Sensor value: %d\n\r",READED);
//       TM_USART_Puts(USART1,buffer);
//     }
//     snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Light Sensor EXIT\n\r");
//       TM_USART_Puts(USART1,buffer);
//   }
//   else
//   {
//     TM_USART_Puts(USART1,"[SHG:ERROR]: NO LIGHT SENSOR FOUND\n\r");
   


       cmd = ParseCommand(comm);
       switch (cmd){
         case idle:
         TM_USART_Puts(USART2,"GIANNI\n");
           break;
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
     osDelay(1000);
   }
//   /* USER CODE END CommandConsole */
  } else {
    TM_USART_Puts(USART2,UNKNOWNCOMMAND);
  }
}

enum command ParseCommand(uint8_t cmd) {
    enum command  SHG_cmd = error; //DEFAULT VALUE
    if(cmd == 0){
      SHG_cmd=idle;
    } else if(cmd == 1){
      SHG_cmd = start;
    } else if(cmd == 2){
      SHG_cmd = log;
    } else if(cmd == 3){
      SHG_cmd = status;
    } else if(cmd == 4){
      SHG_cmd = clear;
    } else if(cmd == 5){
      SHG_cmd = help;
    } else if(cmd == 6){
      SHG_cmd = stop;
    } else if(cmd == 7){
      SHG_cmd = setThs;
    } else if(cmd == 8){
      SHG_cmd = getThs;
    } else if(cmd == 9){
      SHG_cmd = stop;
    }
    return SHG_cmd;
  }

