/*************************************************
 * Copyright © person
 * File name    : fifo.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2018/3/9
 * Description  : 本文件内定义了队列类；
 *                队列主要提供以下几个功能：
 *                1.队列存储数据使用push函数
 *                2.队列使用堆栈功能弹出后进数据使用pop函数
 *                3.队列获取先进数据使用fout函数
 *                4.队列还提供某类数据删除功能使用del函数
 * Others       : 无
 * History      : 180309 pxf 初次建立
 ************************************************/

#ifndef FIFO_H_
#define FIFO_H_

#include "..\comDataTypes_v1.00\comDataTypes.h"
#include "..\oopc_v1.01\oopc.h"

// 版本定义---------------------------------------------------------------------
#define FIFO_CLASS_VERSION        0xC00D00    // C代表v，D代表.，当前版本v1.00

// Fifo类定义-------------------------------------------------------------------
CL(Fifo)
{
    hFifo self;
    hFifo (*init)(hFifo cthis, void *listBuffer, int16 listBuffSize, int16 fifoObjSize);

    int8 *listBuffer;                                         // 缓存队列起始地址
    int16 listBuffSize;                                       // 缓存队列总大小
    int16 fifoObjSize;                                        // 缓存队列的缓存对象大小

    int16 saveObjMaxLen;                                      // 缓存队列缓存缓存对象的最大个数
    int16 currLen;                                            // 缓存队列已缓存缓存对象个数
    int16 top;                                                // 最新缓存对象进来的存放位置
    int16 bottom;                                             // 第一个缓存对象进来的存放位置

    int16 (*push)(hFifo t, void *data);                       // 入列
    int16 (*pop)(hFifo t, void *data);                        // 最后入列数据出列
    int16 (*fout)(hFifo t, void *data);                       // 最先入列数据出列，first out
    int16 (*del)(hFifo t, void *data, void *fifoObjTempBuff); // 删除队列中的某个数据；为删除数据需要提供一个对象临时缓存区FifoObjTempBuff
};

#endif /* FIFO_H_ */
