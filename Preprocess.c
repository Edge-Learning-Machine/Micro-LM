#include "preprocess.h"
//ccc

float X_t[PCA_N_FEATURE];

#ifdef STANDARD_SCALING
normalize_std(float* X, float* s_x, float* u_x) {
	int i = 0;
	for (i = 0; i < PCA_N_ORIG_FEATURE; i++) {
		X[i] = (X[i] - u_x[i]) / s_x[i];
	}
}
#elif defined(MINMAX_SCALING)
normalize_mm(float* X, float* s_x) {
	int i = 0;
	for (i = 0; i < PCA_N_ORIG_FEATURE; i++) {
		X[i] = s_x[i] * X[i];
	}
}
#endif

float* PCA_transform(float* X) {
	int i = 0, j = 0;
	/*float debug[PCA_N_ORIG_FEATURE];
	for (j=0; j<PCA_N_ORIG_FEATURE; j++) {
		debug[j]=X[j];
	}*/
	for (i = 0; i < PCA_N_FEATURE; i++) {
		X_t[i] = 0;
		for (j = 0; j < PCA_N_ORIG_FEATURE; j++) {
			X_t[i] += X[j] * pca_components[i][j];
		}
	}
	return X_t;
}

float* preprocess(float* X)
{
#ifdef STANDARD_SCALING
	normalize_std(X, s_x, u_x);
#elif defined(MINMAX_SCALING)
	normalize_mm(X, s_x);
#endif
	return PCA_transform(X);
}


float* preprocess_TS(float* X)
{
	float *temp[N_TEST];
	int i, j;

	for (i = 0; i < N_TEST; i++)
	{
		temp[i] = preprocess((X+i* N_FEATURE));
	}
	for ( i = 0; i < N_TEST; i++)
	{
		for (j = 0; j < N_FEATURE; j++)
			(X+i)[j] = temp[i][j];
	}
	return X;
}
