/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "main.h"
//#include "stm32f4xx_it.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"

#include "inttypes.h"

#include "PrintfTask.h"
#include "NHD-24-240320.h"

#include "fatfs.h"

void SystemClock_Config(void);
void Pin_Config(void);
void ConfigureSDIO(void);
void ConfigureUART(void);
void ConfigureDMA(void);

SD_HandleTypeDef hsd;
DMA_HandleTypeDef hdma_sdio_rx;
DMA_HandleTypeDef hdma_sdio_tx;

/* USER CODE BEGIN PV */
FRESULT res;

TaskHandle_t LEDBlinkTaskHandle;
TaskHandle_t PrintfTaskHandle;

void LEDBlinkTask(void * argument);

void Error_Handler();

int main(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

	/* Configure the system clock */
	SystemClock_Config();

	Pin_Config();
	ConfigureUART();
	ConfigureDMA();
	ConfigureSDIO();

	// Create the tasks
	xTaskCreate(LEDBlinkTask, "LED Blink", 128, NULL, 1, &LEDBlinkTaskHandle);
	xTaskCreate(PrintfTask, "Printf", 128, NULL, 1, &PrintfTaskHandle);

	vTaskStartScheduler();

	while(1)
	{
		//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		//HAL_Delay(1000);
	}
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/**Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 14;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
void Pin_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

	/*Configure GPIO pin : PA5 */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void ConfigureUART(void)
{
	// Enable peripheral clock of GPIO port
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	// Configure Tx Pin on USART2
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_2, LL_GPIO_AF_7);
	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_2, LL_GPIO_PULL_UP);

	// Configure Rx Pin on USART2
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_3, LL_GPIO_AF_7);
	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_3, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_3, LL_GPIO_PULL_UP);

	// NVIC config for USART2 interrupts
	NVIC_SetPriority(USART2_IRQn, 0);
	NVIC_EnableIRQ(USART2_IRQn);

	// Enable USART peripheral clock and clock source
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

	// Set USART2 direction
	LL_USART_SetTransferDirection(USART2, LL_USART_DIRECTION_TX_RX);

	// 8 data bits, 1 start bit, 1 stop bit, no parity
	LL_USART_ConfigCharacter(USART2, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

	//LL_USART_SetHWFlowCtrl(USART2, LL_USART_HWCONTROL_NONE);

	//LL_USART_SetOverSampling(USART2, LL_USART_OVERSAMPLING_16);

	// Set baud rate 115200
	LL_USART_SetBaudRate(USART2, SystemCoreClock/2, LL_USART_OVERSAMPLING_16, 115200);

	// Enable USART
	LL_USART_Enable(USART2);
}

void ConfigureDMA(void)
{
	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream3_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	/* DMA2_Stream6_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
}

void ConfigureSDIO(void)
{
	hsd.Instance = SDIO;
	hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
	hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
	hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
	hsd.Init.BusWide = SDIO_BUS_WIDE_4B;
	hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
	hsd.Init.ClockDiv = 0;
}

void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hsd->Instance==SDIO)
	{
		/* USER CODE BEGIN SDIO_MspInit 0 */

		/* USER CODE END SDIO_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_SDIO_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**SDIO GPIO Configuration
	    PC8     ------> SDIO_D0
	    PC9     ------> SDIO_D1
	    PC10     ------> SDIO_D2
	    PC11     ------> SDIO_D3
	    PC12     ------> SDIO_CK
	    PD2     ------> SDIO_CMD
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		/* SDIO DMA Init */
		/* SDIO_RX Init */
		hdma_sdio_rx.Instance = DMA2_Stream3;
		hdma_sdio_rx.Init.Channel = DMA_CHANNEL_4;
		hdma_sdio_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_sdio_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_sdio_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_sdio_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
		hdma_sdio_rx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
		hdma_sdio_rx.Init.Mode = DMA_PFCTRL;
		hdma_sdio_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_sdio_rx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
		hdma_sdio_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		hdma_sdio_rx.Init.MemBurst = DMA_MBURST_INC4;
		hdma_sdio_rx.Init.PeriphBurst = DMA_PBURST_INC4;
		if (HAL_DMA_Init(&hdma_sdio_rx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(hsd,hdmarx,hdma_sdio_rx);

		/* SDIO_TX Init */
		hdma_sdio_tx.Instance = DMA2_Stream6;
		hdma_sdio_tx.Init.Channel = DMA_CHANNEL_4;
		hdma_sdio_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_sdio_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_sdio_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_sdio_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
		hdma_sdio_tx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
		hdma_sdio_tx.Init.Mode = DMA_PFCTRL;
		hdma_sdio_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_sdio_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
		hdma_sdio_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		hdma_sdio_tx.Init.MemBurst = DMA_MBURST_INC4;
		hdma_sdio_tx.Init.PeriphBurst = DMA_PBURST_INC4;
		if (HAL_DMA_Init(&hdma_sdio_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(hsd,hdmatx,hdma_sdio_tx);

		/* SDIO interrupt Init */
		HAL_NVIC_SetPriority(SDIO_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(SDIO_IRQn);
		/* USER CODE BEGIN SDIO_MspInit 1 */

		/* USER CODE END SDIO_MspInit 1 */
	}
}

void LEDBlinkTask(void * argument)
{
	uint16_t index = 0;
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

	TFT_Config_Pins();
	TFT_Init();
	printf("Hello\r\n");

	TFT_DrawString("Hello World", 50, 25, RED);
	printf("Starting loop\r\n");

	MX_FATFS_Init();

	printf("Linked SD Card\r\n");
	FRESULT fr = f_mount(&SDFatFS, (TCHAR const*)SDPath, 1);
	if(fr != FR_OK) {
		printf("Error mounting\r\n");
	}
	//## Open and create a text file #################################

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	fr = f_open(&SDFile, "BoomLvL2.txt", FA_WRITE | FA_CREATE_ALWAYS);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	if (fr != FR_OK){
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	char data[] = "Verion2_dma\n\0";
	UINT written;
	UINT len = (UINT)strlen(data);
	//## Write data to the text file ################################
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	fr = f_write(&SDFile, &data[0],len, &written);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	if (fr != FR_OK || written != len) {
		printf("Error writing\r\n");
	} else {
		printf("Wrote test file to SD Card\r\n");
	}
	//## Close the open text file #################################
	fr = f_close(&SDFile);

	//## Set the LD2 so know all good #################################
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		//TFT_Clear(TFT_RGBto16Bit(red, green, blue));
		/*TFT_DrawPixel(x++ % LCDWIDTH, y % LCDHEIGHT, TFT_RGBto16Bit(red, green, blue));
		if (x > LCDMAXWIDTH) {
			x = 0;
			++y;
			if (blue_neg) {
				if (++blue > 31) blue_neg = 0;
			} else {
				if (--blue < 0) blue_neg = 1;
			}
			if (green_neg) {
				if (++green > 63) green_neg = 0;
			} else {
				if (--green < 0) green_neg = 1;
			}
			if (red_neg) {
				if (++red > 31) red_neg = 0;
			} else {
				if (--red < 0) red_neg = 1;
			}
		}*/
		TFT_FillRect(50, 100, 100, 260, LIME);
		TFT_DrawHLine(10, 120, 75, RED);
		TFT_DrawVLine(200, 10, 240, GREEN);
		TFT_DrawLine(0, 0, 200, 200, BLACK);
		TFT_LCD_putCh('C', 50, 25, BLACK, WHITE);
		TFT_LCD_putCh('B', 60, 25, BLACK, WHITE);
		//LL_GPIO_SetOutputPin(GPIOC, GPIO_PIN_4);

		if (!(index % 32)) {
			printf("Hello World %" PRIu16 "\r\n", index);
		}
		index += 1;
		vTaskDelay(250);
	}
}

void Error_Handler()
{
	printf("Error\r\n");
	while(1) {

	}
}
