/**
 ******************************************************************************
 * @file    stm32f4xx_it.c
 * @author  Ac6
 * @version V1.0
 * @date    02-Feb-2015
 * @brief   Default Interrupt Service Routines.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

extern DMA_HandleTypeDef hdma_sdio_rx;
extern DMA_HandleTypeDef hdma_sdio_tx;
extern SD_HandleTypeDef hsd;

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/*void SysTick_Handler(void)
{
	HAL_IncTick();
}*/

/**
 * @brief This function handles SDIO global interrupt.
 */
void SDIO_IRQHandler(void)
{
	/* USER CODE BEGIN SDIO_IRQn 0 */

	/* USER CODE END SDIO_IRQn 0 */
	HAL_SD_IRQHandler(&hsd);
	/* USER CODE BEGIN SDIO_IRQn 1 */

	/* USER CODE END SDIO_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream3 global interrupt.
 */
void DMA2_Stream3_IRQHandler(void)
{
	/* USER CODE BEGIN DMA2_Stream3_IRQn 0 */

	/* USER CODE END DMA2_Stream3_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_sdio_rx);
	/* USER CODE BEGIN DMA2_Stream3_IRQn 1 */

	/* USER CODE END DMA2_Stream3_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream6 global interrupt.
 */
void DMA2_Stream6_IRQHandler(void)
{
	/* USER CODE BEGIN DMA2_Stream6_IRQn 0 */

	/* USER CODE END DMA2_Stream6_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_sdio_tx);
	/* USER CODE BEGIN DMA2_Stream6_IRQn 1 */

	/* USER CODE END DMA2_Stream6_IRQn 1 */
}
