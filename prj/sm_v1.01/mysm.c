/**************************************************************************
* @copyright    :Copyright(C), 2019, pxf, person.
* @file         :mysm.c
* @author       :pxf
* @version      :v1.0
* @date         :2019/01/06 16:39:09
* @brief        :状态机mysm定义及各状态动作定义源文件
* @others       :
* @history      :190106 pxf 初建立
***************************************************************************/

#include "mysm.h"

/*状态机mysm定义
* 配置状态机相关处理状态
***********************************************/
SMDF(mysm, MYSM_LIST);


/*名称 :mysm_act_init()
* 输入 :mysmRec - 状态记录参数指针
* 输出 :无
* 其他 :初始状态操作函数
***********************************************/
void mysm_act_init(void *mysmRec){
    hmysmRec hRec = (hmysmRec)mysmRec;

    // TODO

    hRec->next = mysm_sta_default;
    hRec->last = mysm_sta_init;
}

/*名称 :mysm_act_default()
* 输入 :mysmRec - 状态记录参数指针
* 输出 :无
* 其他 :默认状态操作函数
***********************************************/
void mysm_act_default(void *mysmRec){
    hmysmRec hRec = (hmysmRec)mysmRec;

    // TODO

    hRec->next = mysm_sta_default;
    hRec->last = mysm_sta_default;
}

/*名称 :mysm_act_examp()
* 输入 :mysmRec - 状态记录参数指针
* 输出 :无
* 其他 :状态examp操作函数
***********************************************/
void mysm_act_examp(void *mysmRec){
    hmysmRec hRec = (hmysmRec)mysmRec;

    // TODO

    hRec->next = mysm_sta_default;
    hRec->last = mysm_sta_examp;
}

/*名称 :mysm_act_next()
* 输入 :mysmRec - 状态记录参数指针
* 输出 :无
* 其他 :状态next操作函数
***********************************************/
void mysm_act_next(void *mysmRec){
    hmysmRec hRec = (hmysmRec)mysmRec;

    // TODO

    hRec->next = mysm_sta_default;
    hRec->last = mysm_sta_next;
}

/**************************** Copyright(C) pxf ****************************/

