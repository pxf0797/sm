/*
 * oopc.h
 *
 *  Created on: 2018年2月8日
 *      Author: pxf
 */

#ifndef OOPC_H_
#define OOPC_H_

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 通用宏定义-------------------------------------------------------------------
#define OOPC_FALSE                      0
#define OOPC_TRUE                       1
#define OOPC_NULL                       ((void *)0)

// 配置选项---------------------------------------------------------------------
// 配置宏(两种配置选其一):
#define USE_STDDEF_OFFSETOF             0   // 表示使用C标准定义的offsetof
#define USE_USER_DEFINED_OFFSETOF       1   // 表示使用用户自定义的oopc_offsetof宏
#define OOPC_USE_OFFSETOF               USE_USER_DEFINED_OFFSETOF

#define oopc_return_datatype            int // 定义函数返回数据类型

// OOPC相关实现-----------------------------------------------------------------
// 偏移地址选择
#if (OOPC_USE_OFFSETOF == USE_STDDEF_OFFSETOF)
    #include <stddef.h>
// size_t offsetof(structName, memberName);
// 第一个参数是结构体的名字，第二个参数是结构体成员的名字。
// 该宏返回结构体structName中成员memberName的偏移量。偏移量是size_t类型的。
    #define OOPC_OFFSETOF               offsetof
#else
    // 有些环境可能不支持，不过，这种情形极少出现
    #define OOPC_OFFSETOF(type, member) (size_t)&(((type*)0)->member)
#endif
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 接口及类的继承关系 implement,extends------------------------------------------

// 接口、抽象类进行继承Implement
#define IMPL(type)                      type type
// 实类进行继承Extends
#define EXT(type)                       h##type type

// ----------------------------------------------------------------------------
// 类的继承建议一级继承，多级继承不是不可以，但在c语言中有点给自己找麻烦

// 实类继承子类（继承类）指针 subordinate,self pointer---------------------------
#define SUBC(selfpointer, hselftype, childtype)                      \
h##childtype cthis = ((h##childtype)((char*)(*selfpointer) - OOPC_OFFSETOF(childtype, hselftype)))
// 抽象类或接口继承子类（继承类）指针
#define SUB(selfpointer, selftype, childtype)                        \
h##childtype cthis = ((h##childtype)((char*)selfpointer - OOPC_OFFSETOF(childtype, selftype)))

// 在构造函数中对类的参数进行配置 function,setting--------------------------------
// 在一个类中如果是通用的配置，那么尽量使用FS放在构造函数中，而不是通过init配置一些可变的参数

// FunctionSetting配置类函数
#define FS(ClassFunction, SourceFunction) cthis->ClassFunction = SourceFunction
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 接口及类的定义---------------------------------------------------------------
// 抽象类(abstract)和接口(interface)的构造函数没有返回值的成功与否，因为继承之后都是实体

// Interface接口进行声明
#define INF(type)                                                    \
typedef struct type *h##type, type;                                  \
struct type
// AbstractClass抽象类进行声明
#define AC(type)                                                     \
typedef struct type *h##type, type;                                  \
struct type
// Class实类进行声明
// 类声明中必须要以下self,init两个有参数定义
// self指向自身，最好放在参数的第一个，h##type self
// init有参数要求并且返回自身类型指针，h##type (*init)(classptr cthis,...)
// init参数中类指针必须声明为cthis，而其他所有函数参数中都不可以有cthis的参数出现
// 接口函数、抽象类函数、以及类自身不在同一文件内的函数可以通过init函数传参进行初始化
// 类其余在同一文件内函数最好通过FS直接进行配置
// 示例：
// CL(Aaa)
// {
//	   hAaa self;
//	   hAaa (*init)(hAaa cthis, ...);
//	   ...
// }
#define CL(type)                                                     \
typedef struct type **hh##type, *h##type, type;                      \
h##type type##_new(void *self);                                      \
oopc_return_datatype type##_delete(h##type t);                       \
struct type
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 构造函数及析构函数定义--------------------------------------------------------
// 文件内内联函数只在.c文件中声明就行，放在头文件中声明会报错！！！

// 定义抽象类构造函数，需要返回值cthis/OOPC_NULL
#define ACC(type)                                                    \
static inline h##type type##_ctor(h##type cthis);                    \
static inline h##type type##_ctor(h##type cthis)
// 定义抽象类析构函数，需要返回值OOPC_TRUE/OOPC_FALSE
#define ACD(type)                                                    \
static inline oopc_return_datatype type##_dtor(h##type cthis);       \
static inline oopc_return_datatype type##_dtor(h##type cthis)
// 定义实类构造函数，需要返回值cthis/OOPC_NULL
#define CC(type)                                                     \
static inline h##type type##_ctor(h##type cthis);                    \
h##type type##_new(void *self){                                      \
    h##type cthis = (h##type)self;                                   \
    h##type Rtv = OOPC_NULL;                                         \
    if (OOPC_NULL != cthis){                                         \
        cthis->self = cthis;                                         \
        if (OOPC_NULL == type##_ctor(cthis)){                        \
            cthis->self = OOPC_NULL;                                 \
            Rtv = OOPC_NULL;                                         \
        } else {                                                     \
            Rtv = cthis;                                             \
        }                                                            \
    } else {                                                         \
    	Rtv = OOPC_NULL;                                             \
    }                                                                \
    return Rtv;                                                      \
    /* 当前不去获取内存，只对传输进来的内存进行配置 */                  \
}                                                                    \
static inline h##type type##_ctor(h##type cthis)
// 定义实类析构函数，需要返回值OOPC_TRUE/OOPC_FALSE
#define CD(type)                                                     \
static inline oopc_return_datatype type##_dtor(h##type cthis);       \
oopc_return_datatype type##_delete(h##type cthis){                   \
	oopc_return_datatype Rtv = OOPC_FALSE;                           \
	if (OOPC_NULL != cthis){                                         \
		cthis->self = OOPC_NULL;                                     \
	    if (OOPC_TRUE == type##_dtor(cthis)){                        \
            Rtv = OOPC_TRUE;                                         \
        } else {                                                     \
            Rtv = OOPC_FALSE;                                        \
        }                                                            \
	} else {                                                         \
		Rtv = OOPC_FALSE;                                            \
	}                                                                \
	return Rtv;                                                      \
	/* 当前不去释放内存，只对传输进来的内存进行配置 */                  \
}                                                                    \
static inline oopc_return_datatype type##_dtor(h##type cthis)
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 类实例化时，构造及析构调用----------------------------------------------------

// 调用抽象类构造函数，有返回值cthis/OOPC_NULL
#define _ACC(father)                    father##_ctor(&(cthis->father))
// 调用抽象类析构函数，有返回值OOPC_TRUE/OOPC_FALSE
#define _ACD(father)                    father##_dtor(&(cthis->father))

// 调用实类构造、析构函数
// 调用类构造函数，有返回值cthis/OOPC_NULL
// 调用完此构造函数必须对cthis->father进行判断，因为当前构造函数调用没有返回值
#define _CC(father, fatherptr, ...)                                  \
do{                                                                  \
    cthis->father = father##_new((void *)(fatherptr));               \
    if (OOPC_NULL != cthis->father){                                 \
        if (OOPC_NULL == cthis->father->init(cthis->father, __VA_ARGS__)){ \
        	if (OOPC_TRUE == father##_delete(cthis->father)){        \
        		;                                                    \
        	} else {                                                 \
        		;                                                    \
        	}                                                        \
        	cthis->father = OOPC_NULL;                               \
        } else {                                                     \
        	;                                                        \
        }                                                            \
    } else {                                                         \
    	;                                                            \
    }                                                                \
} while (0)
// 调用类析构函数，有返回值OOPC_TRUE/OOPC_FALSE
#define _CD(father)                     father##_delete((cthis->father))
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 类初始化宏定义，参数个数任意--------------------------------------------------
// 这里的多个参数是由被继承类初始化参数个数决定的 class,new
// ClassNew对类进行初始化
#define CN(type, classptr, ...)                                      \
do{                                                                  \
    if (OOPC_NULL != type##_new((void *)(classptr))){                \
		if (OOPC_NULL == (classptr)->init((classptr), __VA_ARGS__)){ \
        	if (OOPC_TRUE == type##_delete(classptr)){               \
        		;                                                    \
        	} else {                                                 \
        		;                                                    \
        	}                                                        \
        } else {                                                     \
        	;                                                        \
        }                                                            \
    } else {                                                         \
        ;                                                            \
    }                                                                \
} while (0)
// ClassFree对类资源进行释放
#define CF(type, classptr)                                           \
do{                                                                  \
	if (OOPC_NULL != (classptr)){                                    \
		if (OOPC_TRUE == type##_delete(classptr)){                   \
            ;                                                        \
        } else {                                                     \
        	;                                                        \
        }                                                            \
	} else {                                                         \
		;                                                            \
	}                                                                \
} while (0)
// 由于CN/CF/_CC调用后没有返回值，通过以下宏查看操作结果operation result，self/OOPC_NULL
#define OPRS(class)                     (class).self
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif /* OOPC_H_ */
