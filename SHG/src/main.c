#include "stm32f4xx_hal.h"
#include <defines.h>
#include <tm_stm32_disco.h>
#include <tm_stm32_spi.h>
#include <tm_stm32_usart.h>
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