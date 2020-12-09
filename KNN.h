#ifdef KNN

#ifndef KNN_H

#define KNN_H

#include <stdbool.h>


#include "PPParams.h"

#include "ELM.h"
#include "training_set.h"
#include "KNN_params.h"

#ifdef REGRESSION
float knn_regression(float[]);
#else
int knn_classification(float[]);
#endif // REGRESSION

#endif

#endif // KNN
