#include "../inc/SHG_runner.h"
#include "../../FreeRTOS-CMSIS/FreeRTOS.h"
#include "../../FreeRTOS-CMSIS/task.h"
#include "../..//FreeRTOS-CMSIS/main.h"
#include "../../FreeRTOS-CMSIS/cmsis_os.h"



#define ON 1
#define OFF 0
#define OK 1
#define NOT_OK 0
#define DEFAULT_TEMP 25
#define DEFAULT_HUM 50
#define DEFAULT_LIGHT 60 

static bool powered=OFF;

static bool lightSys=OFF;
static bool waterSys=OFF;
static bool heatingSys=OFF;

static bool paired=NOT_OK;

static int hum_thrs=0;
static int temp_thrs=0;
static int light_thrs=0;

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

    void SHG_start(){  
      hum_thrs=DEFAULT_HUM;
      temp_thrs=DEFAULT_TEMP;
      light_thrs=DEFAULT_LIGHT;
      powered=ON;
    }


    void SHG_stop(){
      lightSys=OFF;
      waterSys=OFF;
      heatingSys=OFF;
      powered=OFF;
    }

    void SHG_rst(){
      hum_thrs=DEFAULT_HUM;
      temp_thrs=DEFAULT_TEMP;
      light_thrs=DEFAULT_LIGHT;
      lightSys=OFF;
      waterSys=OFF;
      heatingSys=OFF;
      powered=OFF;
    }

    void SHG_connect(){
      paired=OK;
    }

    bool SHG_getHeatingSystemStatus(){}
    int SHG_getWaterSystemStatus();
    int SHG_getLightSystemStatus();
    int SHG_getTemperature();
    int SHG_getLight();
    int SHG_getHumidity();    
    bool SHG_getPowered();
    bool SHG_getPairStatus();
    int SHG_getTresholdTemperature();
    int SHG_getTresholdHumidity();
    int SHG_getTresholdLight();
    void SHG_setTresholdTemperature(int Temperature);
    void SHG_setTresholdHumidity(int Humidity);
    void SHG_setTresholdLight(int Light);
