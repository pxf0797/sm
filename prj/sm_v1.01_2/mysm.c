/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : mysm.c
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/01/12 22:15:08
* Description  : 
* Others       : 
* History      : 190112 pxf 初建立
***************************************************************************/

/*头文件包含*/
#include "./mysm.h"

/*状态机mysm定义
* 配置状态机相关处理状态
***********************************************/
SMDF(mysm, MYSM_LIST);

/*名称 : mysm_act_init()
* 输入 : mysmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 初始状态操作函数
***********************************************/
void mysm_act_init(void *mysmRec){
    hmysmRec hRec = (hmysmRec)mysmRec;

    // TODO

    hRec->next = mysm_sta_default;
    hRec->last = mysm_sta_init;
}

/*名称 : mysm_act_default()
* 输入 : mysmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 默认状态操作函数
***********************************************/
void mysm_act_default(void *mysmRec){
    hmysmRec hRec = (hmysmRec)mysmRec;

    // TODO

    hRec->next = mysm_sta_default;
    hRec->last = mysm_sta_default;
}

/*名称 : mysm_act_examp()
* 输入 : mysmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态examp操作函数
***********************************************/
void mysm_act_examp(void *mysmRec){
    hmysmRec hRec = (hmysmRec)mysmRec;

    // TODO

    hRec->next = mysm_sta_default;
    hRec->last = mysm_sta_examp;
}

/*名称 : mysm_act_next()
* 输入 : mysmRec - 状态记录参数指针
* 输出 : 无
* 其他 : 状态next操作函数
***********************************************/
void mysm_act_next(void *mysmRec){
    hmysmRec hRec = (hmysmRec)mysmRec;

    // TODO

    hRec->next = mysm_sta_default;
    hRec->last = mysm_sta_next;
}

/**************************** Copyright(C) pxf ****************************/
