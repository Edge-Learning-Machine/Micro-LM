#ifdef DT

#ifndef DT_H

#define DT_H

#include "ELM.h"
#include <stdbool.h>


#include "PPParams.h"
#include "DT_params.h"


void decisionTree_test_dataset();
float decisionTree_regression(float []);
int decisionTree_classification(float []);
#endif

#endif // DT
