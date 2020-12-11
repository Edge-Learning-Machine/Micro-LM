#ifndef ELM_H
#define ELM_H

#include <stdbool.h>

/*
* Begin configuration
*/

//Define the ML algorithm

//#define SVM   //Support Vector Machine
//#define DT    //Decisional Tree
//#define KNN   //K-Nearest Neighbours
//#define TripleES //Holt-Winters Triple exponential smoothing
#define RF    //Random Forest


//Define if it is a regression problem

//#define REGRESSION

//Define if it's a test on the Test Set

//#define DS_TEST

//Define if you need debug messages
//#define DEBUG


//end configuration


//guard to prevent compiling without an algorithm
#if !defined(RF) && !defined(DT) && !defined(KNN) && !defined(SVM) && !defined(TripleEs)
#error You have to define one algorithm
#endif

#ifdef DS_TEST
#include "testing_set.h"
#include "Test.h"
#endif

#include "Preprocess.h"



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


#ifdef REGRESSION
extern float (*pRegress)(float X[]);
#else
extern int (*pClassf)(float X[]);
#endif

#endif
