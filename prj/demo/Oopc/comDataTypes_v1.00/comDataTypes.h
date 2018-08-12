/*
 * commonDataTypes.h
 *
 *  Created on: 2018年3月9日
 *      Author: pxf
 */

#ifndef COMMONDATATYPES_H_
#define COMMONDATATYPES_H_

// 版本定义---------------------------------------------------------------------
#define COM_DATA_TYPES_VERSION    0xC00D00    // C代表v，D代表.，当前版本v1.00

// 基本数据类型定义
#ifndef FALSE
#define FALSE    0
#endif
#ifndef TRUE
#define TRUE     1
#endif
#ifndef NULL
#define NULL     ((void *)0)
#endif

// 整型
typedef char                  int8;
typedef short                 int16;
typedef long                  int32;
typedef long long             int64;

// 无符整型
typedef unsigned char         uint8;
typedef unsigned short        uint16;
typedef unsigned long         uint32;
typedef unsigned long long    uint64;

// 浮点
typedef float                 float32;
typedef double                float64;



#endif /* COMMONDATATYPES_H_ */
