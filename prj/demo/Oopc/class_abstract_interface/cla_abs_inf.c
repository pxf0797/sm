/*
 * cla_abs_inf.c
 *
 *  Created on: 2018年2月8日
 *      Author: pxf
 */

#include "..\Rte.h"

ACC(Bbb)
{
	// 如果需要则进行一些特殊的操作，否则直接返回cthis就行
	// 抽象类的函数一般在实类初始化时进行初始化，因为函数操作的是地实类
	cthis->AbsParam = 0;
	return cthis;
}
ACD(Bbb)
{
	// 如果需要则进行一些特殊的操作，否则直接返回OOPC_TRUE就行
	cthis->AbsParam = 0;
	return OOPC_TRUE;
}

// 接口、抽象类函数、及自身需要的函数进行定义
//void Ccc_Aaa_InfFun(void)
//{
//	;
//}
void Ccc_Aaa_InfFun2(hAaa t)
{
	SUB(t, Aaa, Ccc);
	cthis->ClaParam++;
}

void Ccc_Bbb_AbsFun(void)
{
	;
}
void Ccc_Bbb_AbsFun2(hBbb t)
{
	SUB(t, Bbb, Ccc);
	cthis->ClaParam2++;
}

void Ccc_ClaFun(void)
{
	;
}
// 可定义到其他文件，通过传参形式进行初始化
void Ccc_ClaFun2(hCcc t)
{
	t->ClaParam3++;
}

/*
 * 接口、抽象类函数可以定义到其他文件，因为实类对其初始化都是通过init传参形式进行调用
 * 实类函数也可以定义到其他文件，通过init传参进行初始化
 * 实类函数定义到与构造函数同一文件内的函数最好使用FS形式进行配置，以便于优化
 * init函数必须与实类构造函数定义到同一文件内，并且使用FS进行配置
 * */


/*
 * 实类初始化函数尽量只进行一些传参的配置操作
 * 实类其他一些操作尽量在构造函数中进行操作
 * */
hCcc Ccc_init(hCcc cthis,
		void (*AaaInf)(hAaa t2),
		void (*BbbFun)(void),
		void (*BbbFun2)(hBbb t3),
		void (*CccFun2)(hCcc t4))
{
	hCcc Rtv = OOPC_NULL;
	if (OOPC_NULL != cthis)
	{
		cthis->Aaa.InfFun2 = AaaInf;
		cthis->Bbb.AbsFun = BbbFun;
		cthis->Bbb.AbsFun2 = BbbFun2;
		cthis->ClaFun2 = CccFun2;
		Rtv = cthis;
	}
	else
	{
		Rtv = OOPC_NULL;
	}
	return Rtv;
}

// 构造出实类前，必须先把把需要的接口、抽象类函数、及自身需要的函数先定义出来
CC(Ccc)
{
	hCcc Rtv = OOPC_NULL;
	if (OOPC_NULL != CACC(Bbb))
	{
		FS(init, Ccc_init);
		FS(ClaFun, Ccc_ClaFun);
		//FS(ClaFun2, Ccc_ClaFun2); // 在定义为同一文件下应使用FS设置

		cthis->ClaParam = 0;
		cthis->ClaParam2 = 0;
		cthis->ClaParam3 = 0;

		Rtv = cthis;
	}
	else
	{
		Rtv = OOPC_NULL;
	}

	return Rtv;
}

CD(Ccc)
{
	int Rtv = OOPC_FALSE;
	if (OOPC_FALSE != CACD(Bbb))
	{
		Rtv = OOPC_TRUE;
	}
	else
	{
		Rtv = OOPC_FALSE;
	}

	return Rtv;
}






















