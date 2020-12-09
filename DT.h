#ifdef DT

#ifndef DT_H

#define DT_H

#include "ELM.h"
#include <stdbool.h>


#include "PPParams.h"
#include "DT_params.h"


#ifdef REGRESSION
float decisionTree_regression(float []);
#else
int decisionTree_classification(float []);
#endif // REGRESSION

#endif

#endif // DT
