/*
 * scheduler.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Admin
 */

#include "scheduler.h"
#include "main.h"
#include "stdint.h"
#include <stddef.h>
#include <stdlib.h>

void SCH_Init(void) {
	unsigned char i;
	for (i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete_Task(i);
	}

//	Error_code_G = 0;
//	Timer_init();
//	Watchdog_init();
}

void SCH_Update(void) {
	unsigned char Index;
	for (Index = 0; Index < SCH_MAX_TASKS; Index++){
		if (SCH_tasks_G[Index].pTask){
			if (SCH_tasks_G[Index].Delay == 0){
				SCH_tasks_G[Index].RunMe += 1;
				if (SCH_tasks_G[Index].Period){
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			} else {
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}

unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD) {
	unsigned char Index = 0;
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
		Index++;
	}

	if (Index == SCH_MAX_TASKS){
		//Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Period =PERIOD;
	SCH_tasks_G[Index].RunMe = 0;

	return Index;
}

void SCH_Dispatch_Tasks(void) {
	unsigned char Index;
	for (Index = 0; Index < SCH_MAX_TASKS; Index++){
		if (SCH_tasks_G[Index].RunMe > 0) {
			(*SCH_tasks_G[Index].pTask)();
			SCH_tasks_G[Index].RunMe -= 1;

			if (SCH_tasks_G[Index].Period == 0) {
				SCH_Delete_Task(Index);
			}
		}
	}
//	SCH_Report_Status();
//	SCH_Go_To_Sleep;
}

unsigned char SCH_Delete_Task(const tByte TASK_INDEX) {
	unsigned char Return_code;
	if (SCH_tasks_G[TASK_INDEX].pTask == 0){
		//Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		Return_code = RETURN_ERROR;
	} else {
		Return_code = RETURN_NORMAL;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	return Return_code;
}


//TaskList SCH_tasks_G;

//void SCH_Init(void) {
//	SCH_tasks_G.head = NULL;
//	SCH_tasks_G.size = 0;
//}
//
//void SCH_Update(void) {
//	if(SCH_tasks_G.head->task.Delay == 0) {
//		SCH_tasks_G.head->task.RunMe = 1;
//	}
//	else {
//		SCH_tasks_G.head->task.Delay--;
//	}
//}
//
//unsigned char SCH_Add_Task(void (*pFunc)(), unsigned int DELAY, unsigned int PERIOD) {
//	taskNode* node = (taskNode *) malloc(sizeof(taskNode));
//	node->task.pTask = pFunc;
//	node->task.Delay = DELAY;
//	node->task.Period = PERIOD;
//	node->task.RunMe = 0;
//	node->pNext = NULL;
//
//	uint8_t index = 0;
//	if (SCH_tasks_G.size == 0) {
//		SCH_tasks_G.head = node;
//	} else {
//		taskNode* current = SCH_tasks_G.head;
//		taskNode* previous = NULL;
//		while(current != NULL && node->task.Delay > current->task.Delay) {
//			node->task.Delay -= current->task.Delay;
//			previous = current;
//			current = current->pNext;
//			index++;
//		}
//		if (previous == NULL) {
//			node->pNext = current;
//			current->task.Delay -= node->task.Delay;
//			SCH_tasks_G.head = node;
//		} else {
//			previous->pNext = node;
//			node->pNext = current;
//
//			if(current) {
//				current->task.Delay -= node->task.Delay;
//			}
//		}
//	}
//	SCH_tasks_G.size++;
//	return index;
//}
//
//void SCH_Dispatch_Tasks(void) {
//	if (SCH_tasks_G.head != NULL) {
//		if (SCH_tasks_G.head->task.RunMe == 1) {
//			(*SCH_tasks_G.head->task.pTask)();
//
//			if (SCH_tasks_G.head->task.Period > 0) {
//				SCH_Add_Task(SCH_tasks_G.head->task.pTask, SCH_tasks_G.head->task.Period, SCH_tasks_G.head->task.Period);
//			}
//			SCH_Delete_Task(0);
//		}
//	}
//}
//
//unsigned char SCH_Delete_Task(const tByte TASK_INDEX) {
//	if (TASK_INDEX < 0 || TASK_INDEX >= SCH_tasks_G.size)
//		return RETURN_ERROR;
//
//	taskNode *temp = SCH_tasks_G.head;
//	if (TASK_INDEX == 0) {
//		SCH_tasks_G.head = temp->pNext;
//		SCH_tasks_G.head->task.Delay += temp->task.Delay;
//	} else {
//		uint32_t Index = 0;
//		taskNode *current = SCH_tasks_G.head;
//
//		while (Index < TASK_INDEX - 1) {
//			current = current->pNext;
//			Index++;
//		}
//		temp = current->pNext;
//		current->pNext = temp->pNext;
//		current->pNext->task.Delay += temp->task.Delay;
//	}
//	free(temp);
//	temp = NULL;
//	SCH_tasks_G.size--;
//	return RETURN_NORMAL;
//}
