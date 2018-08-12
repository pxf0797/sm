/*
 * cla_abs_inf.h
 *
 *  Created on: 2018年2月8日
 *      Author: pxf
 */

#ifndef CLA_ABS_INF_H_
#define CLA_ABS_INF_H_

INF(Aaa)
{
//	void (*InfFun)(void);
	void (*InfFun2)(hAaa t);
};

AC(Bbb)
{
	i32 AbsParam;
	void (*AbsFun)(void);
	void (*AbsFun2)(hBbb t);
};

CL(Ccc)
{
	hCcc self;
	hCcc (*init)(hCcc t,
			void (*AaaInf)(hAaa t2),
			void (*BbbFun)(void),
			void (*BbbFun2)(hBbb t3),
			void (*CccFun2)(hCcc t4));

	i32 ClaParam;
	i32 ClaParam2;
	i32 ClaParam3;
	void (*ClaFun)(void);
	void (*ClaFun2)(hCcc t5);

	IMPL(Aaa);
	IMPL(Bbb);
};


// 传参函数声明-----------------------
//void Ccc_Aaa_InfFun(void);
void Ccc_Aaa_InfFun2(hAaa t);
void Ccc_Bbb_AbsFun(void);
void Ccc_Bbb_AbsFun2(hBbb t);
void Ccc_ClaFun2(hCcc t);



#endif /* CLA_ABS_INF_H_ */
