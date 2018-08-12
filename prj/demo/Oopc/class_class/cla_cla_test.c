/*
 * cla_cla_test.c
 *
 *  Created on: 2018Äê2ÔÂ8ÈÕ
 *      Author: pxf
 */

#include "..\Rte.h"

void ClaClaTest(void)
{
	ClaFa CFa;
	Cla CChild;

	CN(Cla, &CChild,
			ClaInfFun,
			ClaFun,
			&CFa,
			ClaFaInfFun,
			ClaFaFun, ClaFaFun2);
	if ((OOPC_NULL != OPRS(CChild)) && (OOPC_NULL != OPRS(CFa)))
	{
		;
	}
	else
	{
		;
	}

	CChild.ClaInf.CInf(&CChild.ClaInf);
	CChild.ClaFun(CChild.self);

	CChild.ClaFa->ClaFaInf.CFInf(&CChild.ClaFa->ClaFaInf);
	CChild.ClaFa->ClaFaFun(CChild.ClaFa);
	CChild.ClaFa->ClaFaFun2(&CChild.ClaFa);


	CF(Cla, CChild.self);
	if ((OOPC_NULL != OPRS(CChild)) || (OOPC_NULL != OPRS(CFa)))
	{
		;
	}
	else
	{
		;
	}
}



