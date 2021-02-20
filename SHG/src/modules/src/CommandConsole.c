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
  uint8_t commths = 0;
  uint8_t prev_commths = 0;
  uint8_t comm = 0;
  uint8_t prev_comm = 1;
  int repeated = 0;
  int paired = 0;
  int already_started = 0;
  int Temperature, Humidity, Light;
  int Temperatureths, Humidityths, Lightths;
  char buf[10];
  char buffer[256];

  /* USER CODE BEGIN CommandConsole */
  /* Infinite loop */

if(TM_I2C_IsDeviceConnected(I2C1, BLUETOOTH_RX_ADDRESS)==TM_I2C_Result_Ok){
  while(1){
       TM_I2C_ReadNoRegister(I2C1, BLUETOOTH_RX_ADDRESS, &comm);
       //repeated is used in order to avoid multiple instances of the same command in sequence
        if(prev_comm != comm){
          repeated = 0;
        } else {
          repeated = 1;
        }

      cmd = ParseCommand(comm);
      //handle status command
      if(cmd == status){
        TM_USART_Puts(USART2,"\e[2J\e[;H");
        TM_USART_Puts(USART2,WELCOME_STRING);
        TM_USART_Puts(USART2,PRESENTATION_STRING);
        TM_USART_Puts(USART2,COMMANDLIST);
        TM_USART_Puts(USART2,STATUSSTRING);
        Temperature = SHG_getTemperature();
        Light = SHG_getLight();
        Humidity = SHG_getHumidity();
        strcat(buffer, "The heating system is -> ");
        strcat(buffer, (SHG_getHeatingSystemStatus() ? "ON  \n" : "OFF \n"));
        strcat(buffer,"The current temperature is: ");
        strcat(buffer,itoa(Temperature,buf,10));
        strcat(buffer,"\n");

        strcat(buffer, "The water system is -> ");
        strcat(buffer, (SHG_getWaterSystemStatus() ? "ON  \n" : "OFF \n"));
        strcat(buffer,"The current humidity is: ");
        strcat(buffer,itoa(Humidity,buf,10));
        strcat(buffer,"\n");

        strcat(buffer, "The light system is -> ");
        strcat(buffer, (SHG_getLightSystemStatus() ? "ON  \n" : "OFF \n"));
        strcat(buffer,"The current light is: ");
        strcat(buffer,itoa(Light,buf,10));
        strcat(buffer,"\n");
        TM_USART_Puts(USART2,buffer);
        TM_USART_Puts(USART2,LINEBREAK);
        memset(buffer,0,256);
      }

      //handle pair command, you can  pair the device only if you have not already paired it.
      if(cmd == pair && !paired && !repeated){
          TM_USART_Puts(USART2,"The Device is paired!\n");
          paired = 1;
          SHG_connect();
      }

      //handle wait_pair command
      if(cmd == wait_pair && !paired && !repeated){
          TM_USART_Puts(USART2,"The Device is pairing with the user...\n");
      }

      //handle the remaining commands, you can enter only if you have paired the device
      if(!repeated && paired && cmd != status && cmd != wait_pair && cmd != pair){
        switch (cmd){
         case start:
          if(!already_started){
           SHG_start();
           TM_USART_Puts(USART2,"\e[2J\e[;H");
           TM_USART_Puts(USART2,WELCOME_STRING);
           TM_USART_Puts(USART2,PRESENTATION_STRING);
           TM_USART_Puts(USART2,COMMANDLIST);
          }
          already_started = 1;
           break;
         case stop:
           TM_USART_Puts(USART2,"\e[2J\e[;H");
           TM_USART_Puts(USART2,WELCOME_STRING);
           TM_USART_Puts(USART2,PRESENTATION_STRING);
           TM_USART_Puts(USART2,COMMANDLIST);
           TM_USART_Puts(USART2,"The SHG is stopped!\n\r");
           already_started = 0;
           SHG_stop();
           break;
         case setThs:
           TM_USART_Puts(USART2,"\e[2J\e[;H");
           TM_USART_Puts(USART2,WELCOME_STRING);
           TM_USART_Puts(USART2,PRESENTATION_STRING);
           TM_USART_Puts(USART2,COMMANDLIST);
         //l'utente deve mandare th1 e 'ok1' (110), th2 e 'ok2' (120), th3 e 'ok3' (130)
           TM_USART_Puts(USART2,TEMPSTRINGTHS);
           while(1){
              TM_I2C_ReadNoRegister(I2C1, BLUETOOTH_RX_ADDRESS, &commths);
              if(commths == 110)
                break;
              prev_commths = commths;
           }
           Temperatureths = prev_commths; 
           SHG_setTresholdTemperature(Temperatureths);

           TM_USART_Puts(USART2,HUMSTRINGTHS);
           while(1){
              TM_I2C_ReadNoRegister(I2C1, BLUETOOTH_RX_ADDRESS, &commths);
              if(commths == 120)
                break;
              prev_commths = commths;
           }
           Humidityths = prev_commths; 
           SHG_setTresholdHumidity(Humidityths);
           
           TM_USART_Puts(USART2,LIGHTSTRINGTHS);
           while(1){
              TM_I2C_ReadNoRegister(I2C1, BLUETOOTH_RX_ADDRESS, &commths);
              if(commths == endThs)
                break;
              prev_commths = commths;
           }
           Lightths = prev_commths; 
           SHG_setTresholdLight(Lightths);

           TM_USART_Puts(USART2,CONFIRMSTRING);
           break;
         case getThs:
          TM_USART_Puts(USART2,"\e[2J\e[;H");
          TM_USART_Puts(USART2,WELCOME_STRING);
          TM_USART_Puts(USART2,PRESENTATION_STRING);
          TM_USART_Puts(USART2,COMMANDLIST);
          Temperature = SHG_getTresholdTemperature();
          Light = SHG_getTresholdLight();
          Humidity = SHG_getTresholdHumidity();
          strcat(buffer,"The current temperature threshold is: ");
          strcat(buffer,itoa(Temperature,buf,10));
          strcat(buffer,"\n");
          TM_USART_Puts(USART2,buffer);
          memset(buffer,0,256);

          strcat(buffer,"The current humidity threshold is: ");
          strcat(buffer,itoa(Humidity,buf,10));
          strcat(buffer,"\n");
          TM_USART_Puts(USART2,buffer);
          memset(buffer,0,256);

          strcat(buffer,"The current light threshold is: ");
          strcat(buffer,itoa(Light,buf,10));
          strcat(buffer,"\n");
          TM_USART_Puts(USART2,buffer);
          memset(buffer,0,256);
           break;
         case reset:
           TM_USART_Puts(USART2,"\e[2J\e[;H");
           TM_USART_Puts(USART2,WELCOME_STRING);
           TM_USART_Puts(USART2,PRESENTATION_STRING);
           TM_USART_Puts(USART2,COMMANDLIST);
           TM_USART_Puts(USART2,RESETMACHINE);
           SHG_rst();
           break;
         case endThs: 
          break;
         default:
           TM_USART_Puts(USART2,"\e[2J\e[;H");
           TM_USART_Puts(USART2,WELCOME_STRING);
           TM_USART_Puts(USART2,PRESENTATION_STRING);
           TM_USART_Puts(USART2,COMMANDLIST);
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
      SHG_cmd = stop;
    } else if(cmd == 5){
      SHG_cmd = setThs;
    } else if(cmd == 6){
      SHG_cmd = getThs;
    } else if(cmd == 7){
      SHG_cmd = reset;
    } else if (cmd == 130){
      SHG_cmd = endThs;
    }
    return SHG_cmd;
}

