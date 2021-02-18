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

#define BLUETOOTH_RX_ADDRESS (0x10 << 1)
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
- status        -> to outupt the values of the environmental variables;
- clear         -> clear the UART command line;
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
  uint8_t comm = 0;
  uint8_t prev_comm = 1;
  int repeated = 0;
  int paired = 0;
  int already_started = 0;

  /* USER CODE BEGIN CommandConsole */
  /* Infinite loop */

if(TM_I2C_IsDeviceConnected(I2C1, BLUETOOTH_RX_ADDRESS)==TM_I2C_Result_Ok){
  while(1){
       TM_I2C_ReadNoRegister(I2C1, BLUETOOTH_RX_ADDRESS, &comm);
        if(prev_comm != comm){
          repeated = 0;
        } else {
          repeated = 1;
        }

      cmd = ParseCommand(comm);
      if(cmd == status)
        //bla bla
      if(!repeated && (cmd != status)){
       switch (cmd){
         case wait_pair:
          if(!paired)
            //pairing...ADD TO USART1
            TM_USART_Puts(USART2,"The Device is pairing with the user...\n");
           break;
         case pair:
          if(!paired){
            //device paired ADD TO USART1
            TM_USART_Puts(USART2,"The Device is paired!\n");
            paired = 1;
          }
           break;
         case start:
          if(!already_started)
           TM_USART_Puts(USART2,WELCOME_STRING);
           TM_USART_Puts(USART2,PRESENTATION_STRING);
          already_started = 1;
           break;
         case status:
           break;
         case clear:
           break;
         case stop:
           break;
         case setThs:
         //l'utente deve mandare th1 e 'ok' (codice x es 110), th2 e 'ok', th3 e 'ok'
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
     osDelay(1000);
     prev_comm = comm;
   }
//   /* USER CODE END CommandConsole */
  } else {
    TM_USART_Puts(USART2,UNKNOWNCOMMAND);
  }
}

enum command ParseCommand(uint8_t cmd) {
    enum command  SHG_cmd = error; //DEFAULT VALUE
    if(cmd == 0){
      SHG_cmd = wait_pair;
    } else if(cmd == 1){
      SHG_cmd = pair;
    } else if(cmd == 2){
      SHG_cmd = start;
    } else if(cmd == 3){
      SHG_cmd = status;
    } else if(cmd == 4){
      SHG_cmd = clear;
    } else if(cmd == 5){
      SHG_cmd = stop;
    } else if(cmd == 6){
      SHG_cmd = setThs;
    } else if(cmd == 7){
      SHG_cmd = getThs;
    } else if(cmd == 8){
      SHG_cmd = stop;
    }
    return SHG_cmd;
  }

