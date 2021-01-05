#include <stm32f4xx_hal.h>
#include <defines.h>
#include <tm_stm32_disco.h>
#include <tm_stm32_spi.h>
#include <tm_stm32_usart.h>
#include <tm_stm32_i2c.h>
#include <string.h>
#include <stdio.h>
#include <FreeRTOS.h>
#include <stm32f4xx.h>
#include <task.h>




#define LIGHT_SENSOR_ADDRESS (0x04<<1)
#define TEMPHUM_SENSOR_ADDRESS (0x02<<1)
#define HEATINGS_ACTUATOR_ADDRESS (0x02<<1)
#define LED_PIN                                GPIO_PIN_5
#define LED_GPIO_PORT                          GPIOA
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()


#define CCM_RAM __attribute__((section(".ccmram")))

uint8_t Transmit[15], Receive[15];


#define H_TASK_STACK_SIZE 256

StackType_t fpuTaskStack[H_TASK_STACK_SIZE] CCM_RAM;  // Put task stack in CCM
StaticTask_t fpuTaskBuffer CCM_RAM;  // Put TCB in CCM

StackType_t fpuTaskStack2[H_TASK_STACK_SIZE] CCM_RAM;  // Put task stack in CCM
StaticTask_t fpuTaskBuffer2 CCM_RAM;  // Put TCB in CCM

void test_FPU_test(void* p);


void HeatingSystemOUT();
void HeatingSystemOUT2();

int main(void)
{
  TM_RCC_InitSystem();
  HAL_Init();

  TM_USART_Init(USART1, TM_USART_PinsPack_1, 9600);
  TM_USART_Init(USART2, TM_USART_PinsPack_2, 9600);






  //xTaskCreateStatic(HeatingSystemOUT, "Name1", H_TASK_STACK_SIZE, NULL, 1, fpuTaskStack, &fpuTaskBuffer);
  //xTaskCreateStatic(HeatingSystemOUT2, "Name2", H_TASK_STACK_SIZE, NULL, 1, fpuTaskStack2, &fpuTaskBuffer2);


  printf("System Started!\n");
  vTaskStartScheduler();  // should never return

  for (;;);


  /*
  uint8_t i=0;

  TM_RCC_InitSystem();
  HAL_Init();

  TM_DISCO_LedInit();

  TM_SPI_Init(SPI2, TM_SPI_PinsPack_2);
  TM_USART_Init(USART1, TM_USART_PinsPack_2, 9600);

  TM_I2C_Init(I2C2, TM_I2C_PinsPack_2, TM_I2C_CLOCK_STANDARD);
  TM_I2C_Init(I2C1, TM_I2C_PinsPack_1, TM_I2C_CLOCK_STANDARD);

uint8_t READED=0xFF;
char buffer[1024];
//TEST READING AND WRITING VALUE ON THE ACTUATOR
 if(TM_I2C_IsDeviceConnected(I2C2, HEATINGS_ACTUATOR_ADDRESS)==TM_I2C_Result_Ok){
   while(1){
  //Disabled
  if(TM_I2C_IsDeviceConnected(I2C1, LIGHT_SENSOR_ADDRESS)==TM_I2C_Result_Ok){
    while(READED!=100){
      HAL_Delay(1000);
      TM_I2C_ReadNoRegister(I2C1, LIGHT_SENSOR_ADDRESS, &READED);
      snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Light Sensor value: %d\n\r",READED);
      TM_USART_Puts(USART1,buffer);
    }
    snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Light Sensor EXIT\n\r");
      TM_USART_Puts(USART1,buffer);
  }
  else
  {
    TM_USART_Puts(USART1,"[SHG:ERROR]: NO LIGHT SENSOR FOUND\n\r");
  }

  uint8_t data[2];
  uint8_t reciv[2];
  data[0]=0;
  data[1]=7;

  while(1){
      TM_I2C_WriteMultiNoRegister(I2C2, HEATINGS_ACTUATOR_ADDRESS,data,3); 
      HAL_Delay(1000);
      TM_I2C_ReadMultiNoRegister(I2C2, HEATINGS_ACTUATOR_ADDRESS, reciv,3);
      HeatingSystemOUT(reciv);
  }

  HAL_Delay(10);  
//ENABLED
  TM_I2C_WriteNoRegister(I2C2, HEATINGS_ACTUATOR_ADDRESS,0x01);
  TM_I2C_ReadNoRegister(I2C2, HEATINGS_ACTUATOR_ADDRESS, &READED);
  HeatingSystemOUT(READED);
  
  HAL_Delay(10);
//ERROR
  TM_I2C_WriteNoRegister(I2C2, HEATINGS_ACTUATOR_ADDRESS,0x15);
  TM_I2C_ReadNoRegister(I2C2, HEATINGS_ACTUATOR_ADDRESS, &READED);
  HeatingSystemOUT(READED);
   }
 }else
 {
   TM_USART_Puts(USART1,"[SHG:ERROR]: NO HS FOUND\n\r");
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
    /*
    Transmit[i] = i;
        
    /* Check for receive */
    /*
    Receive[i] = TM_SPI_Send(SPI2, Transmit[i]);
    
    i=i+1;

  }
  */
}

void HeatingSystemOUT(){
   char buffer[1024];
  uint8_t READED[2];
  READED[0]=0;
  READED[1]=7;
  while(1){
  if(READED[0]==0x00){
    snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Heating System status: OFF value %d\n\r",READED[1]);
  }
  else if(READED[0]==0x01){
    snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Heating System status: ON %d\n\r",READED[1]);
  }else
  {
    snprintf(buffer, sizeof(buffer), "[SHG:ERROR]: Heating System status: OFF(forced) %d\n\r",READED[1]);
  }
  TM_USART_Puts(USART1,buffer);
  }
}

void HeatingSystemOUT2(){
   char buffer[1024];
  uint8_t READED[2];
  READED[0]=0;
  READED[1]=7;
  while(1){
  if(READED[0]==0x00){
    snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Heating System status: OFF value %d\n\r",READED[1]);
  }
  else if(READED[0]==0x01){
    snprintf(buffer, sizeof(buffer), "[SHG:INFO]: Heating System status: ON %d\n\r",READED[1]);
  }else
  {
    snprintf(buffer, sizeof(buffer), "[SHG:ERROR]: Heating System status: OFF(forced) %d\n\r",READED[1]);
  }
  TM_USART_Puts(USART2,buffer);
  }
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

