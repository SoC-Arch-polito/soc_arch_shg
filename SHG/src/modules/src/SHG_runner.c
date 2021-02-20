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
    if(powered){
     if(SHG_getTemperature()<temp_thrs)
       SHG_heatingSystemOn();
      else
        SHG_heatingSystemOff();
      if(SHG_getHumidity()<hum_thrs)
        SHG_waterSystemOn();
      else
        SHG_waterSystemOff();
      if(SHG_getLight()<light_thrs)
        SHG_lightSystemOn();
      else
        SHG_lightSystemOff();
    }
    osDelay(10);
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
      SHG_waterSystemOff();
      SHG_heatingSystemOff();
      SHG_lightSystemOff();
      powered=OFF;
    }

    void SHG_rst(){
      hum_thrs=DEFAULT_HUM;
      temp_thrs=DEFAULT_TEMP;
      light_thrs=DEFAULT_LIGHT;
    }

    void SHG_connect(){
      paired=OK;
    }

    bool SHG_getHeatingSystemStatus(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C2, HEATING_ADDRESS)==TM_I2C_Result_Ok)
        TM_I2C_ReadNoRegister(I2C2, HEATING_ADDRESS, &value);
      if (value==0x00)
        return 0;
      else
        return 1;
    }
    bool SHG_getWaterSystemStatus(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C2, WATER_SYS_ADDRESS)==TM_I2C_Result_Ok)
        TM_I2C_ReadNoRegister(I2C2, WATER_SYS_ADDRESS, &value);
      if (value==0x00)
        return 0;
      else
        return 1;
    }
    bool SHG_getLightSystemStatus(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C2, LIGHT_SYS_ADDRESS)==TM_I2C_Result_Ok)
        TM_I2C_ReadNoRegister(I2C2, LIGHT_SYS_ADDRESS, &value);
      if (value==0x00)
        return 0;
      else
        return 1;
    }

    int SHG_getTemperature(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C1, TEMP_SENSOR_ADDRESS)==TM_I2C_Result_Ok)
        TM_I2C_ReadNoRegister(I2C1, TEMP_SENSOR_ADDRESS, &value);
      return value;

    }
    int SHG_getLight(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C1, LIGHT_SENSOR_ADDRESS)==TM_I2C_Result_Ok)
        TM_I2C_ReadNoRegister(I2C1, LIGHT_SENSOR_ADDRESS, &value);
      return value;
    }
    int SHG_getHumidity(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C1, HUM_SENSOR_ADDRESS)==TM_I2C_Result_Ok)
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
      return;
    }
    void SHG_setTresholdLight(int Light){
      light_thrs=Light;
      return;
    }

    void SHG_heatingSystemOn(){
      if(TM_I2C_IsDeviceConnected(I2C2, HEATING_ADDRESS)==TM_I2C_Result_Ok)
         TM_I2C_WriteNoRegister(I2C2, HEATING_ADDRESS,0x01);
    }
    void SHG_waterSystemOn(){
      if(TM_I2C_IsDeviceConnected(I2C2, WATER_SYS_ADDRESS)==TM_I2C_Result_Ok)
         TM_I2C_WriteNoRegister(I2C2, WATER_SYS_ADDRESS,0x01);
    }
    void SHG_lightSystemOn(){
      if(TM_I2C_IsDeviceConnected(I2C2, LIGHT_SYS_ADDRESS)==TM_I2C_Result_Ok)
         TM_I2C_WriteNoRegister(I2C2, LIGHT_SYS_ADDRESS,0x01);
    }
    
    void SHG_heatingSystemOff(){
      if(TM_I2C_IsDeviceConnected(I2C2, HEATING_ADDRESS)==TM_I2C_Result_Ok)
         TM_I2C_WriteNoRegister(I2C2, HEATING_ADDRESS,0x00);
    }
    void SHG_waterSystemOff(){
      if(TM_I2C_IsDeviceConnected(I2C2, WATER_SYS_ADDRESS)==TM_I2C_Result_Ok)
         TM_I2C_WriteNoRegister(I2C2, WATER_SYS_ADDRESS,0x00);
    }
    void SHG_lightSystemOff(){
      if(TM_I2C_IsDeviceConnected(I2C2, LIGHT_SYS_ADDRESS)==TM_I2C_Result_Ok)
         TM_I2C_WriteNoRegister(I2C2, LIGHT_SYS_ADDRESS,0x00);
    }
