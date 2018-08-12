/*
 * sm_test.c
 *
 *  Created on: 2018Äê3ÔÂ10ÈÕ
 *      Author: pxf
 */

#include "Rte.h"

#define MY_SM_LIST(_)    \
	_(mySm, upCnt)       \
	_(mySm, downCnt)     \
	_(mySm, done)

SMDC(mySm, MY_SM_LIST)
{
	sta next;
	sta last;
	int16 cnt;
};

SMDF(mySm, MY_SM_LIST);


void mySm_act_init(void *smRec)
{
	hmySmRec hRec = (hmySmRec)smRec;

	hRec->last = mySm_sta_init;
	hRec->cnt = 0;
	hRec->next = mySm_sta_upCnt;
}
void mySm_act_upCnt(void *smRec)
{
	hmySmRec hRec = (hmySmRec)smRec;

	hRec->last = mySm_sta_upCnt;
	hRec->cnt++;

	if (hRec->cnt >= 4)
	{
		hRec->next = mySm_sta_downCnt;
	}
	else
	{
		hRec->next = mySm_sta_upCnt;
	}
}
void mySm_act_downCnt(void *smRec)
{
	hmySmRec hRec = (hmySmRec)smRec;

	hRec->last = mySm_sta_downCnt;
	hRec->cnt--;

	if (hRec->cnt < 3)
	{
		hRec->next = mySm_sta_done;
	}
	else
	{
		hRec->next = mySm_sta_downCnt;
	}
}
void mySm_act_done(void *smRec)
{
	hmySmRec hRec = (hmySmRec)smRec;

	hRec->last = mySm_sta_done;
	hRec->cnt--;
	hRec->next = mySm_sta_default;
}
void mySm_act_default(void *smRec)
{
	hmySmRec hRec = (hmySmRec)smRec;

	hRec->last = mySm_sta_default;
	hRec->cnt = 0;
	hRec->next = mySm_sta_default;
}

void sm_test(void)
{
	int16 i = 0;
//	static mySmRec mySmRunRec = {mySm_sta_init};
//	mySm[mySmRunRec.next](&mySmRunRec);

	for (i = 0; i < 20; i++)
	{
		SMR(mySm);
	}

}



