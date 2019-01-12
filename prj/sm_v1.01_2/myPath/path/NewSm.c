/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : NewSm.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/01/12 22:45:55
* Description  : 状态机NewSm定义及各状态动作定义源文件
* Others       : 
* History      : 190112 pxf 初次建立
***************************************************************************/

/*头文件包含*/
#include "./NewSm.h"

/*状态机NewSm定义
* 配置状态机相关处理状态
***********************************************/
SMDF(NewSm, NEWSM_LIST);

/*名称 : NewSm_act_init()
* 输入 : NewSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 初始状态操作函数
***********************************************/
void NewSm_act_init(void *NewSmRec){
    hNewSmRec hRec = (hNewSmRec)NewSmRec;

    // TODO

    hRec->next = NewSm_sta_default;
    hRec->last = NewSm_sta_init;
}

/*名称 : NewSm_act_default()
* 输入 : NewSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 默认状态操作函数
***********************************************/
void NewSm_act_default(void *NewSmRec){
    hNewSmRec hRec = (hNewSmRec)NewSmRec;

    // TODO

    hRec->next = NewSm_sta_default;
    hRec->last = NewSm_sta_default;
}

/*名称 : NewSm_act_examp()
* 输入 : NewSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态examp操作函数
***********************************************/
void NewSm_act_examp(void *NewSmRec){
    hNewSmRec hRec = (hNewSmRec)NewSmRec;

    // TODO

    hRec->next = NewSm_sta_default;
    hRec->last = NewSm_sta_examp;
}

/*名称 : NewSm_act_next()
* 输入 : NewSmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态next操作函数
***********************************************/
void NewSm_act_next(void *NewSmRec){
    hNewSmRec hRec = (hNewSmRec)NewSmRec;

    // TODO

    hRec->next = NewSm_sta_default;
    hRec->last = NewSm_sta_next;
}

/**************************** Copyright(C) pxf ****************************/
