/*
 * thread_stm32.c
 *
 *  Created on: 28 сент. 2023 г.
 *      Author: Professional
 */

#include "hal_thread.h"
#include "cmsis_os2.h"

struct sThread {

	// СДЕЛАТЬ ЛОГИКУ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//ThreadExecutionFunction function;
	void* parameter;
	//HANDLE handle;
	//int state;
	//bool autodestroy;
};

void Thread_sleep(int millies)
{

	osDelay(millies);

}
