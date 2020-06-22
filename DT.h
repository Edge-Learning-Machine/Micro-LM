#ifndef DT_H

#define DT_H

#include "ELM.h"
#include <stdbool.h>


//#ifdef SAMPLE_TESTINGSET
//#include "minimal_testing_set.h"
//#else
#include "testing_set.h"
//#endif

#include "PPParams.h"
#include "DT_params.h"


void decisionTree_test_dataset(bool);
float decisionTree_regression(float []);
int decisionTree_classification(float []);
#endif
