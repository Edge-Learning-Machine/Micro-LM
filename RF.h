#ifdef RF

#ifndef RF_H

#define RF_H

#include "ELM.h"
#include <stdbool.h>


#include "PPParams.h"
#include "RF_params.h"

#ifdef REGRESSION
float randomForest_regression(float []);
#else
int randomForest_classification(float []);
#endif //REGRESSION

#endif //RF_H

#endif //RF

