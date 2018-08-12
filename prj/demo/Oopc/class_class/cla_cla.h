/*
 * cla_cla.h
 *
 *  Created on: 2018年2月8日
 *      Author: pxf
 */

#ifndef CLA_CLA_H_
#define CLA_CLA_H_

INF(ClaFaInf)
{
	void (*CFInf)(hClaFaInf t);
};

CL(ClaFa)
{
	hClaFa self;
	hClaFa (*init)(hClaFa t,
			void ClaFaInfFun(hClaFaInf t2),
			void (*ClaFaFun)(hClaFa t3),
			void (*ClaFaFun2)(hhClaFa t4));

	i32 ClaFaParam;
	i32 ClaFaParam2;
	i32 ClaFaParam3;
	void (*ClaFaFun)(hClaFa t5);
	void (*ClaFaFun2)(hhClaFa t6);

	IMPL(ClaFaInf);
};

INF(ClaInf)
{
	void (*CInf)(hClaInf t);
};

/*
 * 继承实类init函数参数结构（参数顺序）
 * 子类，子类接口，子类抽象类函数，子类函数
 * 父类，父类接口，父类抽象类函数，父类函数
 * */
CL(Cla)
{
	hCla self;
	hCla (*init)(hCla t,
			void ClaInfFun(hClaInf t2),
			void (*ClaFun)(hCla t3),
			hClaFa ClaFaaa,
			void ClaFaInfFun(hClaFaInf t4),
			void ClaFaFun(hClaFa t5),
			void ClaFaFun2(hhClaFa t6));

	i32 ClaParam;
	i32 ClaParam2;
	i32 ClaParam3;
	void (*ClaFun)(hCla t7);

	IMPL(ClaInf);
	EXT(ClaFa);
};


// 外部函数声明
void ClaFaInfFun(hClaFaInf t);
void ClaFaFun(hClaFa t);
void ClaFaFun2(hhClaFa t);
void ClaInfFun(hClaInf t);
void ClaFun(hCla t);

#endif /* CLA_CLA_H_ */
