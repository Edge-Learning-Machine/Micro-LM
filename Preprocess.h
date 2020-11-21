#ifndef PREPROCESS_H
#define PREPROCESS_H

#include "ELM.h"

#include "PPParams.h"

extern float X_t[PCA_N_FEATURE];

#ifdef STANDARD_SCALING
normalize_std(float* X, float* s_x, float* u_x);
#elif defined(MINMAX_SCALING)
normalize_mm(float* X, float* s_x);
#endif

float* PCA_transform(float* X);

float* preprocess(float* X);

float* preprocess_TS(float* X);


#endif

