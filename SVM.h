#ifdef SVM
#ifndef SVM_H

#define SVM_H

#include <stdbool.h>


#include "PPParams.h"
#include "SVM_params.h"
#include "ELM.h"

float svm_regression(float []);
int svm_classification(float []);

#endif

#endif // SVM
