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

static bool HS=OFF;
static bool WS=OFF;
static bool LS=OFF;
static int hum_thrs=DEFAULT_HUM;
static int temp_thrs=DEFAULT_TEMP;
static int light_thrs=DEFAULT_LIGHT;
static int temp=0;
static int hum=0;
static int lig=0;

/* USER CODE BEGIN Header_SHG_runner */
/**
* @brief Function implementing the SHG_core thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SHG_runner */

  int SHG_getTemperature_INTERNAL();
  int SHG_getHumidity_INTERNAL();
  int SHG_getLight_INTERNAL();

void SHG_runner(void const * argument)
{
  /* USER CODE BEGIN SHG_runner */
  /* Infinite loop */
  for(;;)
  {
    temp=SHG_getTemperature_INTERNAL();
    hum=SHG_getHumidity_INTERNAL();
    lig=SHG_getLight_INTERNAL();
    if(powered){
     if(temp<temp_thrs){
       SHG_heatingSystemOn();
       HS=ON;
     }
      else{
        SHG_heatingSystemOff();
        HS=OFF;
      }
      if(hum<hum_thrs){
        SHG_waterSystemOn();
        WS=ON;
      }
      else{
        SHG_waterSystemOff();
        WS=OFF;
      }
      if(lig<light_thrs){
        SHG_lightSystemOn();
        LS=ON;
      }
      else{
        SHG_lightSystemOff();
        LS=OFF;
      }
    }else{
      HS=OFF;
      WS=OFF;
      LS=OFF;
      SHG_waterSystemOff();
      SHG_heatingSystemOff();
      SHG_lightSystemOff();
    }
    osDelay(10);
  }
  /* USER CODE END SHG_runner */
}

   int SHG_getTemperature_INTERNAL(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C1, TEMP_SENSOR_ADDRESS)==TM_I2C_Result_Ok)
        TM_I2C_ReadNoRegister(I2C1, TEMP_SENSOR_ADDRESS, &value);
      return value;
    }
   int SHG_getHumidity_INTERNAL(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C1, HUM_SENSOR_ADDRESS)==TM_I2C_Result_Ok)
        TM_I2C_ReadNoRegister(I2C1, HUM_SENSOR_ADDRESS, &value);
      return value;
    }
   int SHG_getLight_INTERNAL(){
      uint8_t value=0;
      if(TM_I2C_IsDeviceConnected(I2C1, LIGHT_SENSOR_ADDRESS)==TM_I2C_Result_Ok)
        TM_I2C_ReadNoRegister(I2C1, LIGHT_SENSOR_ADDRESS, &value);
      return value;
    }

    void SHG_start(){  
      powered=ON;
    }


    void SHG_stop(){
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
        return HS;
    }
    bool SHG_getWaterSystemStatus(){
        return WS;  
    }
    bool SHG_getLightSystemStatus(){
        return LS;  
    }
    int SHG_getTemperature(){
      return temp;
    }
    int SHG_getLight(){
      return lig;
    }
    int SHG_getHumidity(){
      return hum;
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
