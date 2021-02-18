#include "../inc/SHG_runner.h"
#include "../../FreeRTOS-CMSIS/FreeRTOS.h"
#include "../../FreeRTOS-CMSIS/task.h"
#include "../..//FreeRTOS-CMSIS/main.h"
#include "../../FreeRTOS-CMSIS/cmsis_os.h"
#include <tm_stm32_i2c.h>


#define TEMP_SENSOR_ADDRESS (0x02<<1)
#define LIGHT_SENSOR_ADDRESS (0x04<<1)
#define HUM_SENSOR_ADDRESS (0x08<<1)
#define HEATING_ADDRESS (0x02<<1)
#define LIGHT_SYS_ADDRESS (0x04<<1)
#define WATER_SYS_ADDRESS (0x08<<1)

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
    if(powered=ON){
     if(SHG_getTemperature()<temp_thrs)
        heatingSys=ON;
      else
        heatingSys=OFF;
      if(SHG_getHumidity()<temp_thrs)
        waterSys=ON;
      else
        waterSys=OFF;
      if(SHG_getLight()<temp_thrs)
        lightSys=ON;
      else
        lightSys=OFF;
    }
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

    bool SHG_getHeatingSystemStatus(){
      return heatingSys;
    }
    bool SHG_getWaterSystemStatus(){
      return waterSys;
    }
    bool SHG_getLightSystemStatus(){
      return lightSys;
    }

    int SHG_getTemperature(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C1, TEMP_SENSOR_ADDRESS)==TM_I2C_Result_Ok){
        TM_I2C_ReadNoRegister(I2C1, TEMP_SENSOR_ADDRESS, &value);
      return value;

      }
    }
    int SHG_getLight(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C1, LIGHT_SENSOR_ADDRESS)==TM_I2C_Result_Ok){
        TM_I2C_ReadNoRegister(I2C1, LIGHT_SENSOR_ADDRESS, &value);
      return value;
    }
    int SHG_getHumidity(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C1, HUM_SENSOR_ADDRESS)==TM_I2C_Result_Ok){
        TM_I2C_ReadNoRegister(I2C1, HUM_SENSOR_ADDRESS, &value);
      return value;
    }

    bool SHG_getPowered(){
      return powered;
    }
    bool SHG_getPairStatus(){
      return paired;
    }

    int SHG_getTresholdTemperature(){
      return temp_thrs;
    }
    int SHG_getTresholdHumidity(){
      return hum_thrs;
    }
    int SHG_getTresholdLight(){
      return light_thrs;
    }
    void SHG_setTresholdTemperature(int Temperature){
      temp_thrs=Temperature;
      return;
    }
    void SHG_setTresholdHumidity(int Humidity){
      hum_thrs=Humidity;
    }
    void SHG_setTresholdLight(int Light){
      light_thrs=Light;
    }
