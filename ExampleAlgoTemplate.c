/*


#include "ELM.h"

#ifdef NEW_ALGO

#include "newAlgo.h"
#include <stdio.h>
#include <stdbool.h>


#ifdef REGRESSION
float (*pRegress)(float X[]) = newAlgo_regression;
#else
int (*pClassf)(float X[]) = newAlgo_classification;
#endif


#ifndef REGRESSION
int newAlgo_classification(float X[])
{
	// classification algorithm implementation
}
#else
float newAlgo_regression(float X[])
{
	// regression algorithm implementation
}
#endif

#endif

*/
