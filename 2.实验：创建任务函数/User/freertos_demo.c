/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS ��ֲʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� F407���������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
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
/*FreeRTOS����*/

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
 * @brief       FreeRTOS������ں���
 * @param       ��
 * @retval      ��
 */
void freertos_demo(void)
{    
    
	
	xTaskCreate((TaskFunction_t )					start_task,
				(char * )							"start_task", 
				(configSTACK_DEPTH_TYPE ) 			START_TASK_STACK_SIZE,
				(void * )							NULL,
				(UBaseType_t )						START_TASK_PRIO,
				(TaskHandle_t *)					&start_task_handler );
				
	//�������������			
	vTaskStartScheduler();
	
}

void start_task( void * pvParameters )
{
	//�����ٽ��� �ر��ж� 
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
				
	//�˳��ٽ��� ���ж� 
	taskEXIT_CRITICAL();
	
}

//����1��ʵ��led0ÿ500ms��תһ��
void task1( void * pvParameters )
{
	while(1)
	{
		printf("Task1�������У�\n");
		LED0_TOGGLE();
		vTaskDelay(500);
		
	}
	
}

//����2��ʵ��led1ÿ500ms��תһ��
void task2( void * pvParameters )
{
	while(1)
	{
		printf("Task2�������У�\n");
		LED1_TOGGLE();
		vTaskDelay(500);
	}
}

//����3��ɾ������1
void task3( void * pvParameters )
{
	uint8_t key = 0;
	while(1)
	{
		key = key_scan(0);
		if(key == KEY0_PRES)
		{	
			printf("Task3�������У�\n");
			vTaskDelete(task1_handler);
		}
		vTaskDelay(10);
	}
	
}
