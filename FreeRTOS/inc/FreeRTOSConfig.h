/*
 * FreeRTOS Kernel V10.0.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#ifndef __IASMARM__
/* For SystemCoreClock */
#include "board.h"
#endif

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *----------------------------------------------------------*/

    
#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			0
#define configMAX_PRIORITIES		( 8 )
#define configUSE_TICK_HOOK			0
#define configCPU_CLOCK_HZ			( (uint32_t) SystemCoreClock )
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 100 )
#define configTOTAL_HEAP_SIZE		( ( size_t ) ( 32 * 1024 ) )
#define configMAX_TASK_NAME_LEN		( 12 )
#define configUSE_TRACE_FACILITY	1
#define configUSE_STATS_FORMATTING_FUNCTIONS 1    
#define configUSE_16_BIT_TICKS		0
#define configIDLE_SHOULD_YIELD		0
#define configUSE_CO_ROUTINES 		0
#define configUSE_MUTEXES			1

#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

#define configUSE_COUNTING_SEMAPHORES 	1
#define configUSE_ALTERNATIVE_API 		0
#define configCHECK_FOR_STACK_OVERFLOW	2
#define configUSE_RECURSIVE_MUTEXES		1
#define configQUEUE_REGISTRY_SIZE		10
#define configGENERATE_RUN_TIME_STATS	0
#define configUSE_MALLOC_FAILED_HOOK	1
    
#define configUSE_TIMERS                0
#define configUSE_NEWLIB_REENTRANT      1

#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H 1
#define configRECORD_STACK_HIGH_ADDRESS 1

/* Backward compatibility breaks task aware debugging on MCUXpresso so it must be disabled */
#define configENABLE_BACKWARD_COMPATIBILITY 0

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet			1
#define INCLUDE_uxTaskPriorityGet			1
#define INCLUDE_vTaskDelete					1
#define INCLUDE_vTaskCleanUpResources		0
#define INCLUDE_vTaskSuspend				1
#define INCLUDE_vTaskDelayUntil				1
#define INCLUDE_vTaskDelay					1
#define INCLUDE_uxTaskGetStackHighWaterMark	1
#define INCLUDE_eTaskGetState				1

/* The following gives two altenatives for collecting runtime statistics
 * - Extremely accurate timing using CPU core for short time statistics
 * - Slightly less accurate timing using LPC timers for collecting stats over extended time periods
 */
#if 1
/* This enables processor core cycle counter for runtime statistics
 * Internal cycle counter gives very accurate results but overflows in couple of minutes */
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()    (CoreDebug->DEMCR |= 1 << 24, DWT->CTRL |= 1)
#define portGET_RUN_TIME_COUNTER_VALUE()    DWT->CYCCNT

#else
/* NOTE: we need to provide implementation of vConfigureTimerForRunTimeStats()
 * It is called to set up high resolution timer that is needed for accurate runtime
 * measurement. I assume that we use SCTSMALL1 (SCTimer3) in unified mode so this function
 * must set up SCTSMALL1.
 */
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
/* The value is read directly from the counter register for efficiency and low overhead. */
#define portGET_RUN_TIME_COUNTER_VALUE() LPC_SCTSMALL1->COUNT_U

#if 0 /* never enable this code in a header file */
/* The following is required if runtime statistics are to be collected
 * Copy the code to the source file where other you initialize hardware */
extern "C" {

void vConfigureTimerForRunTimeStats( void ) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}
/* end runtime statictics collection */
#endif

#endif


 /**
  * Configure the number of priority bits.
  * LPC1549 has 8 priority levels (3 bits)
  */
 #define configPRIO_BITS       __NVIC_PRIO_BITS

 /* The lowest interrupt priority that can be used in a call to a "set priority"
    function. */
 #define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         0x1f

 /* The highest interrupt priority that can be used by any interrupt service
    routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
    INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
    PRIORITY THAN THIS! (higher priorities are lower numeric values. */
 #define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

 /* Interrupt priorities used by the kernel port layer itself.  These are generic
    to all Cortex-M ports, and do not rely on any particular library functions. */
 #define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
 #define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )


/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
   standard names - or at least those used in the unmodified vector table. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
