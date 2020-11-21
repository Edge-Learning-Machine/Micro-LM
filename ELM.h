#ifndef ELM_H
#define ELM_H

#include <stdbool.h>

/*
 * Define the ML algorithm
 */
//#define SVM   //Support Vector Machine
#define DT    //Decisional Tree 
//#define KNN   //K-Nearest Neighbours
//#define TripleES //Holt-Winters Triple exponential smoothing
//#define RF    //Random Forest

//Define if it is a regression problem
//#define REGRESSION

//Define if it's a test about the Test Set
#define DS_TEST


//#ifdef SAMPLE_TESTINGSET
//#include "minimal_testing_set.h"
//#endif

#include "Preprocess.h"

#ifdef DS_TEST
#include "testing_set.h"
#endif

#ifdef SVM
#include "SVM.h"
#endif

#ifdef DT
#include "DT.h"
#endif

#ifdef KNN
#include "KNN.h"
#endif

#ifdef RF
#include "RF.h"
#endif

#ifdef TripleES
#include "TripleES_params.h"
int* HW_TripleExpoSmoothing(int arrayD[], int vlen, double alpha, double beta,
	double gamma, int slen, int n_preds, double scaling_factor);
#endif


#endif
