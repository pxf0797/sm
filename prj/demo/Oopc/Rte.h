/*
 * Rte.h
 *
 *  Created on: 2018Äê2ÔÂ8ÈÕ
 *      Author: pxf
 */

#ifndef RTE_H_
#define RTE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include ".\comDataTypes_v1.00\comDataTypes.h"
#include "UniDataTypes.h"
//#include ".\oopc\oopc.h"
//#include ".\oopc_v1.0\oopc.h"
#include ".\oopc_v1.01\oopc.h"
#include ".\fifo_v1.00\fifo.h"
#include ".\sm_v1.00\sm.h"

#include ".\class_abstract_interface\cla_abs_inf.h"
#include ".\class_class\cla_cla.h"
void ClaAbsInfTest(void);
void ClaClaTest(void);

void sm_test(void);
void fifo_test(void);


#endif /* RTE_H_ */
