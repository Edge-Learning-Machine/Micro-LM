#ifdef DS_TEST

#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stdio.h>
#include "ELM.h"

#ifdef REGRESSION
extern float (*pRegress)(float X[]);
#else
extern int (*pClassf)(float X[]);
#endif

void RunTest();


#endif
#endif