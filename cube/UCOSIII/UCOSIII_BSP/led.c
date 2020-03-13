/*****************************************************
* @Author  :  Fengzhaoliang
* @File    :  led.c
* @Date    :  2017-04-29
* @Function:  UCOSIII transplant template
******************************************************/
#include "led.h"

static void Bsp_Led_Gpio_Init()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
       
}

void  Led_On(void)
{
    // GPIO_SetBits(GPIOE, GPIO_PIN_6 | GPIO_PIN_7);
    HAL_GPIO_WritePin (GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
}

void  Led_Off(void)
{
    // GPIO_ResetBits(GPIOE, GPIO_PIN_6 | GPIO_PIN_7);
    HAL_GPIO_WritePin (GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
}

void Bsp_Led_Init(void)
{
    Bsp_Led_Gpio_Init();
}