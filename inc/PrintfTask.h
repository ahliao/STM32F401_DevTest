/************************
 * File: PrintfTask
 * Brief: RTOS Task for handling debug printf statements
 */

#ifndef _PRINTFTASK
#define _PRINTFTASK

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "stdio.h"

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

//TaskHandle_t PrintfTaskHandle;

QueueHandle_t printfQueue;

void PrintfTask(void * argument);

void USART2_IRQHandler(void);

#endif
