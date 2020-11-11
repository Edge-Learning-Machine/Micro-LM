#ifndef RF_H

#define RF_H

#include "ELM.h"
#include <stdbool.h>


//#ifdef SAMPLE_TESTINGSET
//#include "minimal_testing_set.h"
//#else
#include "testing_set.h"
//#endif

#include "PPParams.h"
#include "RF_params.h"


void randomForest_test_dataset(bool);
float randomForest_regression(float []);
int randomForest_classification(float []);
#endif
