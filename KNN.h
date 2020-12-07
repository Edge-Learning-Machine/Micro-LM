#ifdef KNN

#ifndef KNN_H

#define KNN_H

#include <stdbool.h>


#include "PPParams.h"

#include "ELM.h"
#include "training_set.h"
#include "KNN_params.h"

float knn_regression(float[]);
int knn_classification(float[]);
#endif

#endif // KNN
