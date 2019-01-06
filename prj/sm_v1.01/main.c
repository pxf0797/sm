/*
 * main.c
 *
 *  Created on: 2019Äê1ÔÂ6ÈÕ
 *      Author: pxf
 */

#include "mysm.h"

void test(void){
    while(1){SMR(mysm);};
}
void test2(void){
    static mysmRec mysmRunRec = {mysm_sta_init};
    while(1){SMRE(mysm, mysmRunRec);};
}

int main(void)
{
//    test2();

    return 0;
}
