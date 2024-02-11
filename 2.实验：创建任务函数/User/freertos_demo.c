/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS 移植实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 F407电机开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
/*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"

/******************************************************************************************************/
/*FreeRTOS配置*/

#define START_TASK_PRIO					1
#define START_TASK_STACK_SIZE 			128  
TaskHandle_t start_task_handler;
void start_task( void * pvParameters );

#define TASK1_PRIO					2
#define TASK1_STACK_SIZE 			128  
TaskHandle_t task1_handler;
void task1( void * pvParameters );
	
#define TASK2_PRIO					3
#define TASK2_STACK_SIZE 			128  
TaskHandle_t task2_handler;	
void task2( void * pvParameters );

#define TASK3_PRIO					4
#define TASK3_STACK_SIZE 			128  
TaskHandle_t task3_handler;	
void task3( void * pvParameters );

/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{    
    
	
	xTaskCreate((TaskFunction_t )					start_task,
				(char * )							"start_task", 
				(configSTACK_DEPTH_TYPE ) 			START_TASK_STACK_SIZE,
				(void * )							NULL,
				(UBaseType_t )						START_TASK_PRIO,
				(TaskHandle_t *)					&start_task_handler );
				
	//开启任务调度器			
	vTaskStartScheduler();
	
}

void start_task( void * pvParameters )
{
	//进入临界区 关闭中断 
	taskENTER_CRITICAL();
	
	xTaskCreate((TaskFunction_t )					task1,
				(char * )							"task1", 
				(configSTACK_DEPTH_TYPE ) 			TASK1_STACK_SIZE,
				(void * )							NULL,
				(UBaseType_t )						TASK1_PRIO,
				(TaskHandle_t *)					&task1_handler );
				
	xTaskCreate((TaskFunction_t )					task2,
				(char * )							"task2", 
				(configSTACK_DEPTH_TYPE ) 			TASK2_STACK_SIZE,
				(void * )							NULL,
				(UBaseType_t )						TASK2_PRIO,
				(TaskHandle_t *)					&task2_handler );

	xTaskCreate((TaskFunction_t )					task3,
				(char * )							"task3", 
				(configSTACK_DEPTH_TYPE ) 			TASK3_STACK_SIZE,
				(void * )							NULL,
				(UBaseType_t )						TASK3_PRIO,
				(TaskHandle_t *)					&task3_handler );
				
	vTaskDelete(NULL);
				
	//退出临界区 打开中断 
	taskEXIT_CRITICAL();
	
}

//任务1，实现led0每500ms翻转一次
void task1( void * pvParameters )
{
	while(1)
	{
		printf("Task1正在运行！\n");
		LED0_TOGGLE();
		vTaskDelay(500);
		
	}
	
}

//任务2，实现led1每500ms翻转一次
void task2( void * pvParameters )
{
	while(1)
	{
		printf("Task2正在运行！\n");
		LED1_TOGGLE();
		vTaskDelay(500);
	}
}

//任务3，删除任务1
void task3( void * pvParameters )
{
	uint8_t key = 0;
	while(1)
	{
		key = key_scan(0);
		if(key == KEY0_PRES)
		{	
			printf("Task3正在运行！\n");
			vTaskDelete(task1_handler);
		}
		vTaskDelay(10);
	}
	
}
