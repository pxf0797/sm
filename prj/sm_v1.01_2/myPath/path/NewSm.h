/**************************************************************************
* Copyright    : Copyright(C), 2019, pxf, person.
* File name    : NewSm.h
* Author       : pxf
* Version      : v1.0
* Created on   : 2019/01/12 22:45:55
* Description  : 状态机NewSm声明及状态机使用示例头文件
* Others       : 
* History      : 190112 pxf 初次建立
***************************************************************************/

#ifndef NEWSM_H_
#define NEWSM_H_

/*头文件包含*/
#include "../../sm_v1.01/sm.h"

/*状态机NewSm使用示例：
* 当前状态机已在SMDF中定义出实体NewSm，需要做的只是让其运行起来
* 状态机运行方式有两种直接给时钟驱动的SMR和使用自定义记录状态后进驱动的SMRE
***********************************************
* SMR方式
***********************************************
void test(void){
    while(1){SMR(NewSm);};
}
***********************************************
* SMRE方式
***********************************************
void test2(void){
    static NewSmRec NewSmRunRec = {NewSm_sta_init};
    while(1){SMRE(NewSm, NewSmRunRec);};
}
***********************************************/


/*状态机NewSm状态序列定义
* 注意其中NewSm_init,NewSm_default未在此定义，默认会给出
***********************************************/
#define NEWSM_LIST(_)    \
    _(NewSm, examp)      \
    _(NewSm, next)


/*状态机NewSm声明
* 已给出状态记录next,及上一状态last，其他参数需自行添加
***********************************************/
SMDC(NewSm, NEWSM_LIST){
    sta next; // 运行状态记录
    sta last; // 上一状态记录
    // TODO
};

#endif /*NEWSM_H_*/

/**************************** Copyright(C) pxf ****************************/
