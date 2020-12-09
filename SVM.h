#ifdef SVM
#ifndef SVM_H

#define SVM_H

#include <stdbool.h>


#include "PPParams.h"
#include "SVM_params.h"
#include "ELM.h"

#ifdef REGRESSION
float svm_regression(float []);
#else
int svm_classification(float []);
#endif // REGRESSION

#endif

#endif // SVM
