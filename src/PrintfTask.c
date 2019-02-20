/*
 * PrintfTask.c
 *
 *  Created on: Jan 22, 2019
 *      Author: Alex
 */

#include "FreeRTOS.h"
#include "PrintfTask.h"
#include "semphr.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_it.h"

// Defines
#define		PRINTF_TASK_DELAY		pdMS_TO_TICKS(1)

// Semaphores
volatile SemaphoreHandle_t printfTXEBinary;

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
	// e.g. write a character to the EVAL_COM1 and Loop until the end of transmission
	/*while (!LL_USART_IsActiveFlag_TXE(USART2))
	{
	}*/
	//LL_USART_TransmitData8(USART2, ch);
	xQueueSendToBack(printfQueue, &ch, 0);

  return ch;
}

void PrintfTask(void * argument)
{
	BaseType_t xStatus;
	char printchar;

	printfQueue = xQueueCreate(64, sizeof(char));
	printfTXEBinary = xSemaphoreCreateBinary();
	//LL_USART_EnableIT_TXE(USART2);

	while(1)
	{
		xStatus = xQueueReceive(printfQueue, &printchar, portMAX_DELAY);

		if (xStatus == pdPASS)
		{
			//_Printf_Char = printchar;


			while (!LL_USART_IsActiveFlag_TXE(USART2))
			{
				vTaskDelay(PRINTF_TASK_DELAY);
			}


			LL_USART_TransmitData8(USART2, printchar);
			//LL_USART_EnableIT_TXE(USART2);
			//xSemaphoreTake(printfTXEBinary, portMAX_DELAY);
		}
		vTaskDelay(PRINTF_TASK_DELAY);
	}
}

void USART2_IRQHandler(void)
{
	if(LL_USART_IsEnabledIT_TXE(USART2) && LL_USART_IsActiveFlag_TXE(USART2))
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		/* TXE flag will be automatically cleared when writing new data in DR register */

		/* Call function in charge of handling empty DR => will lead to transmission of next character */
		/* Disable TXE interrupt */
		//LL_USART_DisableIT_TXE(USART2);
		//xSemaphoreGiveFromISR(printfTXEBinary, &xHigherPriorityTaskWoken);

		//portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

		/* Enable TC interrupt */
		//LL_USART_EnableIT_TC(USART2);

		/* Fill DR with a new char */
		//LL_USART_TransmitData8(USART2, _Printf_Char);
	}

	/*if(LL_USART_IsEnabledIT_TC(USART2) && LL_USART_IsActiveFlag_TC(USART2))
	{
		// Clear TC flag
		//LL_USART_ClearFlag_TC(USART2);
		// Call function in charge of handling end of transmission of sent character
        //and prepare next character transmission
		//USART_CharTransmitComplete_Callback();
	}*/

	if(LL_USART_IsEnabledIT_ERROR(USART2) && LL_USART_IsActiveFlag_NE(USART2))
	{
		/* Call Error function */
		//Error_Callback();
		/*BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		LL_USART_DisableIT_TXE(USART2);
		xSemaphoreGiveFromISR(printfTXEBinary, &xHigherPriorityTaskWoken);

		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);*/
	}

}
