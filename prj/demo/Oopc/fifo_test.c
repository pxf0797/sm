/*
 * fifo_test.c
 *
 *  Created on: 2018年3月10日
 *      Author: pxf
 */

#include "Rte.h"

void printfFifoSta(hFifo t);

typedef struct fifoObj
{
	int16 data[4];
} fifoObj;

fifoObj fifoBuffer[20];
Fifo uint64Fifo;

fifoObj saveData;
fifoObj tempBuff;

void fifo_test(void)
{
	int16 i = 0;

	CN(Fifo, &uint64Fifo, fifoBuffer, sizeof(fifoBuffer), sizeof(fifoObj));
	if (OOPC_NULL != OPRS(uint64Fifo))
	{
		;
	}
	else
	{
		;
	}

	saveData.data[0] = 0;
	saveData.data[1] = 0;
	saveData.data[2] = 0;
	saveData.data[3] = 0;

	for (i = 0; i < 8; i++)
	{
		saveData.data[0] = (i + 5);
		uint64Fifo.push(uint64Fifo.self, &saveData);

		printfFifoSta(uint64Fifo.self);
	}

	saveData.data[0] = 9;
	uint64Fifo.push(uint64Fifo.self, &saveData);
	printfFifoSta(uint64Fifo.self);
	uint64Fifo.del(uint64Fifo.self, &saveData, &tempBuff);
	printfFifoSta(uint64Fifo.self);

	uint64Fifo.fout(uint64Fifo.self, &saveData);
	printfFifoSta(uint64Fifo.self);
	uint64Fifo.fout(uint64Fifo.self, &saveData);
	printfFifoSta(uint64Fifo.self);

	uint64Fifo.pop(uint64Fifo.self, &saveData);
	printfFifoSta(uint64Fifo.self);
	uint64Fifo.pop(uint64Fifo.self, &saveData);
	printfFifoSta(uint64Fifo.self);

	CF(Fifo, uint64Fifo.self);
	if (OOPC_NULL == OPRS(uint64Fifo))
	{
		;
	}
	else
	{
		;
	}
}

void printfFifoSta(hFifo t)
{
	printf("\n当前队列状态如下：\n");
	printf("listBuffer：%lx\n listBuffSize：%d\n fifoObjSize：%d\n",
			(uint32)(t->listBuffer),t->listBuffSize,t->fifoObjSize);
	printf("saveObjMaxLen：%d\n currLen：%d\n top：%d\n bottom：%d\n",
			t->saveObjMaxLen,t->currLen,t->top,t->bottom);
}
















