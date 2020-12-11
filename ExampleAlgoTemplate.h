/*
///////////////////////////////////////////////////////////////////////////
This is a template on how to implement new ML algorithm on Micro-LM to make it compatible with all the feature of this application
To make it fully compatible with the test function the ELM.h should be modified too: the define for the new algorithm must be added .
Also don't forget to add your define to the guard that prevents the compiling without an algorithm selected.


#ifdef NEW_ALGO

#ifndef NEW_ALGO_H

#define NEW_ALGO_H

#include "ELM.h"
#include <stdbool.h>


#include "PPParams.h"
#include "Algo_params.h"


#ifdef REGRESSION
float newAlgo_regression(float []);
#else
int newAlgo_classification(float []);
#endif // REGRESSION

#endif //NEW_ALGO_H

#endif // NEW_ALGO


*/
