#include "../inc/OutputConsole.h"
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

#define BOOL2STRING(v)   ( ( v== true) ? "true" : "false" )

/* USER CODE BEGIN Header_OutputConsole */
/**
* @brief Function implementing the UartTX thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OutputConsole */


#define SHG_OUTPUTCONSOLE_DELAY 2000




void OutputConsole(void const * argument)
{
  /* USER CODE BEGIN OutputConsole */
  /* Infinite loop */

    bool SHG_HsStatus,SHG_WsStatus,SHG_LsStatus ;
    int SHG_Temp,SHG_Light,SHG_Hum;
    bool SHG_PairStatus,SHG_On;
    int SHG_ThresholdTemp,SHG_ThresholdHum,SHG_ThresholdLight;
  
    char buffer[256] = "";
    char env_buffer[10] = "";

  while(1){

    SHG_HsStatus =  SHG_getHeatingSystemStatus();
    SHG_WsStatus =  SHG_getWaterSystemStatus();
    SHG_LsStatus =  SHG_getLightSystemStatus();
    SHG_Temp = SHG_getTemperature();
    SHG_Light =  SHG_getLight();
    SHG_Hum = SHG_getHumidity();    
    SHG_On = SHG_getPowered();
    SHG_PairStatus = SHG_getPairStatus();
    SHG_ThresholdTemp = SHG_getTresholdTemperature();
    SHG_ThresholdHum = SHG_getTresholdHumidity();
    SHG_ThresholdLight = SHG_getTresholdLight();

    strcat(buffer,"[SHG:BLUETOOTH]\tPairing status:");
    strcat(buffer, BOOL2STRING(SHG_PairStatus)); 
    strcat(buffer,"\n");

    strcat(buffer,"[SHG:STATUS] Power on :");
    strcat(buffer, BOOL2STRING(SHG_On)); 
    strcat(buffer," , ");
    strcat(buffer,"HS status :");
    strcat(buffer, BOOL2STRING(SHG_HsStatus)); 
    strcat(buffer," , ");
    strcat(buffer,"WS status :");
    strcat(buffer, BOOL2STRING(SHG_WsStatus)); 
    strcat(buffer," , ");
    strcat(buffer,"LS status :");
    strcat(buffer, BOOL2STRING(SHG_LsStatus)); 
    strcat(buffer,"\n");

    strcat(buffer,"[SHG:THRESHOLDS] Humidity threshold :");
    strcat(buffer, itoa(SHG_ThresholdHum,env_buffer,10)); 
    strcat(buffer," , ");
    strcat(buffer,"Temperature threshold :");
    strcat(buffer,itoa(SHG_ThresholdTemp,env_buffer,10) ); 
    strcat(buffer," , ");
    strcat(buffer,"Light threshold :");
    strcat(buffer,itoa(SHG_ThresholdLight,env_buffer,10)); 
    strcat(buffer,"\n");

    strcat(buffer,"[SHG:ENVIROMENT] Humidy :");
    strcat(buffer, itoa(SHG_Hum,env_buffer,10)); 
    strcat(buffer," , ");
    strcat(buffer,"Temperature :");
    strcat(buffer,itoa(SHG_Temp,env_buffer,10) ); 
    strcat(buffer," , ");
    strcat(buffer,"Light :");
    strcat(buffer,itoa(SHG_Light,env_buffer,10)); 
    strcat(buffer,"\n");


     TM_USART_Puts(USART1,buffer);
     memset(buffer, 0,256);
     osDelay(SHG_OUTPUTCONSOLE_DELAY);
    //HAL_Delay(SHG_OUTPUTCONSOLE_DELAY);
  }
  /* USER CODE END OutputConsole */

}



