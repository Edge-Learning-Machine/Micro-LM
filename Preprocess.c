#include "preprocess.h"
//ccc

float X_t[N_FEATURE];



#ifdef STANDARD_SCALING
//normalize_std(float* X, float* s_x, float* u_x) {
scale_std(float* X) {
	int i = 0;
	for (i = 0; i < N_ORIG_FEATURE; i++) {
		X[i] = (X[i] - u_x[i]) / s_x[i];
	}
}
#elif defined(MINMAX_SCALING)
scale_mm(float* X) {
	int i = 0;
	for (i = 0; i < N_ORIG_FEATURE; i++) {
		X[i] = (s_x[i] * X[i]) + m_x[i];
	}
}
#endif


float *PCA_transform(float *X){
	int i=0, j=0;
	#ifdef DO_PCA
	for (i=0; i<N_FEATURE; i++) {
		X_t[i]=0;
		for (j=0; j<N_ORIG_FEATURE; j++) {
			X_t[i] += (X[j]-pca_means[j])*pca_components[i][j];
		}
	}
	#else
	for (i=0; i<N_FEATURE; i++) {
		X_t[i]=X[i];
	}
	#endif
	return X_t;
}

float* preprocess(float* X)
{
#ifdef STANDARD_SCALING
	scale_std(X);
#elif defined(MINMAX_SCALING)
	scale_mm(X);
#endif
	return PCA_transform(X);
}

