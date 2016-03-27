/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include <nucleo_hal_bsp.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

void MX_TIM2_Init(void);

int main(void) {
  HAL_Init();

  Nucleo_BSP_Init();
  MX_TIM2_Init();

  HAL_TIM_Base_Start_IT(&htim2);

  while (1);
}

/* TIM2 init function */
void MX_TIM2_Init(void) {
  TIM_ClockConfigTypeDef sClockSourceConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 16383;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim2);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_ETRMODE2;
  sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_NONINVERTED;
  sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
  sClockSourceConfig.ClockFilter = 0;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base) {

  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_base->Instance==TIM2)  {
    /* Peripheral clock enable */
    __TIM2_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();

    /**TIM2 GPIO Configuration
    PA0     ------> TIM2_ETR
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
 }
}

void TIM2_IRQHandler(void) {
  HAL_TIM_IRQHandler(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if(htim->Instance == TIM2)
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
