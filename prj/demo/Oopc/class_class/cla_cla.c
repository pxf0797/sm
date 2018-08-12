/*
 * cla_cla.c
 *
 *  Created on: 2018年2月8日
 *      Author: pxf
 */

#include "..\Rte.h"

// 父类相关配置

/*
 * 接口只解决继承类的功能，即只对继承类进行作用
 * 类还有继承不建议再深层次配置操作
 * */

void ClaFaInfFun(hClaFaInf t)
{
	SUB(t, ClaFaInf, ClaFa);
	cthis->ClaFaParam++;
}

// 假设当前函数定义在其他文件
void ClaFaFun(hClaFa t)
{
	t->ClaFaParam2++;
}

// 定义可操作子类的功能函数
// 此类函数尽量少定义，毕竟可以直接使用子类直接进行操作
void ClaFaFun2(hhClaFa t)
{
	SUBC(t, ClaFa, Cla);
	cthis->ClaParam2++;
}

hClaFa ClaFa_init(hClaFa cthis,
		void ClaFaInfFun(hClaFaInf t1),
		void (*ClaFaFun)(hClaFa t2),
		void (*ClaFaFun2)(hhClaFa t3))
{
	hClaFa Rtv = OOPC_NULL;
	if (OOPC_NULL != cthis)
	{
		cthis->ClaFaInf.CFInf = ClaFaInfFun;
		cthis->ClaFaFun = ClaFaFun;
		cthis->ClaFaFun2 = ClaFaFun2;
		Rtv = cthis;
	}
	else
	{
		Rtv = OOPC_NULL;
	}

	return Rtv;
}


CC(ClaFa)
{
	FS(init, ClaFa_init);

	cthis->ClaFaParam = 0;
	cthis->ClaFaParam2 = 0;
	cthis->ClaFaParam3 = 0;

	return cthis;
}

CD(ClaFa)
{
	cthis->ClaFaParam = 0;
	cthis->ClaFaParam2 = 0;
	cthis->ClaFaParam3 = 0;

	return OOPC_TRUE;
}



// 子类相关配置

void ClaInfFun(hClaInf t)
{
	SUB(t, ClaInf, Cla);
	cthis->ClaParam++;
}

void ClaFun(hCla t)
{
	t->ClaParam3++;
}

/*
 * 继承父类必须通过init进行传参配置
 * 因为在配置时父类还未进行实例化
 * 子类必须声明为cthis
 * */
hCla Cla_init(hCla cthis,
		void ClaInfFun(hClaInf t2),
		void (*ClaFun)(hCla t3),
		hClaFa ClaFaaa,
		void ClaFaInfFun(hClaFaInf t4),
		void ClaFaFun(hClaFa t5),
		void ClaFaFun2(hhClaFa t6))
{
	hCla Rtv = OOPC_NULL;
	if (OOPC_NULL != cthis)
	{
		cthis->ClaInf.CInf = ClaInfFun;
		cthis->ClaFun = ClaFun;

		// 传参配置父类
		cthis->ClaFa = ClaFaaa;
		CCC(ClaFa, ClaFaaa, ClaFaInfFun, ClaFaFun, ClaFaFun2);
		if (OOPC_NULL == OPRS(*ClaFaaa))
		{
			if (OOPC_TRUE == CCD(ClaFa))
			{
				;
			}
			else
			{
				;
			}

			Rtv = OOPC_NULL;
		}
		else
		{
			Rtv = cthis;
		}
	}
	else
	{
		Rtv = OOPC_NULL;
	}

	return Rtv;
}


CC(Cla)
{
	FS(init, Cla_init);

	cthis->ClaParam = 0;
	cthis->ClaParam2 = 0;
	cthis->ClaParam3 = 0;

	return cthis;
}

CD(Cla)
{
	int Rtv = OOPC_FALSE;
	if (OOPC_NULL != cthis->ClaFa)
	{
		if (OOPC_TRUE == CCD(ClaFa))
		{
			cthis->ClaParam = 0;
			cthis->ClaParam2 = 0;
			cthis->ClaParam3 = 0;
			Rtv = OOPC_TRUE;
		}
		else
		{
			Rtv = OOPC_FALSE;
		}
	}
	else
	{
		Rtv = OOPC_FALSE;
	}

	return Rtv;
}

/*
 * 无论是父类还是子类都得分别进行初始化
 * 初始化的顺序最好是先进行子类再进行父类的
 *
 * */































