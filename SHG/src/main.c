#include "stm32f4xx_hal.h"
#include <defines.h>
#include <tm_stm32_disco.h>
#include <tm_stm32_spi.h>
#include <tm_stm32_usart.h>
#include <tm_stm32_i2c.h>
#include <string.h>


#define LED_PIN                                GPIO_PIN_5
#define LED_GPIO_PORT                          GPIOA
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()

uint8_t Transmit[15], Receive[15];

int main(void)
{
  uint8_t i=0;

  TM_RCC_InitSystem();

  HAL_Init();

  TM_DISCO_LedInit();

  TM_SPI_Init(SPI2, TM_SPI_PinsPack_2);
  TM_USART_Init(USART1, TM_USART_PinsPack_2, 9600);

  TM_I2C_Init(I2C2, TM_I2C_PinsPack_1, TM_I2C_CLOCK_STANDARD);


uint8_t READED=0xFF;

//TEST READING AND WRITING VALUE ON THE ACTUATOR
 if(TM_I2C_IsDeviceConnected(I2C2, 0x00)==TM_I2C_Result_Ok){
   while(1){
  //Disabled
  TM_I2C_WriteNoRegister(I2C2, 0x00,0x00); 
  TM_I2C_ReadNoRegister(I2C2, 0X00, &READED);
  HeatingSystemOUT(READED);
  

  HAL_Delay(10);  
//ENABLED
  TM_I2C_WriteNoRegister(I2C2, 0x00,0x01);
  TM_I2C_ReadNoRegister(I2C2, 0X00, &READED);
  HeatingSystemOUT(READED);
  
  HAL_Delay(10);
//ERROR
  TM_I2C_WriteNoRegister(I2C2, 0x00,0x15);
  TM_I2C_ReadNoRegister(I2C2, 0X00, &READED);
  HeatingSystemOUT(READED);
   }
 }


  TM_I2C_Write(I2C2, 0x00, 0xE5,0x12);

  LED_GPIO_CLK_ENABLE();
  
  GPIO_InitTypeDef GPIO_InitStruct;
  
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct); 

  while (1)
  {
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    
    HAL_Delay(1000);

    TM_USART_Puts(USART1, "hello world.\n\r");

          /* Send multi bytes */
    
    Transmit[i] = i;
        
    /* Check for receive */
    Receive[i] = TM_SPI_Send(SPI2, Transmit[i]);
    
    i=i+1;

  }
}

void HeatingSystemOUT(uint8_t READED){
  char buffer[1024];
  if(READED==0x00){
    snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Heating System status: OFF\n\r");
  }
  else if(READED==0x01){
    snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Heating System status: ON\n\r");
  }else
  {
    snprintf(buffer, sizeof(buffer), "[SHG:ERROR]: Heating System status: OFF(forced)\n\r");
  }
  TM_USART_Puts(USART1,buffer);
  return;
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1) {}
}


void MemManage_Handler(void)
{
  while (1) {}
}

void BusFault_Handler(void)
{
  while (1) {}
}

void UsageFault_Handler(void)
{
  while (1) {}
}

void SVC_Handler(void)
{
}


void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}