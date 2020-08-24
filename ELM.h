#ifndef ELM_H
#define ELM_H

#include <stdbool.h>

/*
 * Define the ML algorithm
 */
#define SVM
//#define DT
//#define KNN
//#define TripleES //Holt-Winters Triple exponential smoothing

//If it is a whole dataset performance analysis. Otherwise it is one shot
//#define DS_TEST

//If it is a regression problem
//#define REGRESSION

float *preprocess(float *);

#ifdef SVM
void svm_test_dataset(bool);
float svm_regression(float[]);
int svm_classification(float[]);
#endif

#ifdef DT
void decisionTree_test_dataset(bool);
float decisionTree_regression(float[]);
int decisionTree_classification(float[]);
#endif

#ifdef KNN
void knn_test_dataset(bool);
float knn_regression(float[]);
int knn_classification(float[]);
#endif

#ifdef TripleES
#include "TripleES_params.h"
int* HW_TripleExpoSmoothing(int arrayD[], int vlen, double alpha, double beta,
		            double gamma,int slen, int n_preds, double scaling_factor);
#endif

#endif
