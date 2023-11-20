/*
 * scheduler.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

typedef struct {
	void (* pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask ;

typedef struct taskNode {
    sTask task;
    struct taskNode *pNext;
} taskNode;

typedef struct {
    taskNode *head;
    uint32_t size;
} TaskList;

typedef unsigned char tByte;
typedef unsigned int  tWord;
typedef unsigned long tLong;

#define RETURN_NORMAL 0
#define RETURN_ERROR 1
#define ERROR_SCH_TOO_MANY_TASKS 1
#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK 2
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER 3
#define ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START 4
#define ERROR_SCH_LOST_SLAVE 5
#define ERROR_SCH_CAN_BUS_ERROR 6
#define ERROR_I2C_WRITE_BYTE_AT24C64 7
#define ERROR_SCH_CANNOT_DELETE_TASK 8

#define SCH_MAX_TASKS 5
#define NO_TASK_ID 0

void SCH_Init(void);
void SCH_Update(void);
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
void SCH_Dispatch_Tasks(void);
unsigned char SCH_Delete_Task(const tByte TASK_INDEX);
void SCH_Report_Status(void);

#endif /* INC_SCHEDULER_H_ */
