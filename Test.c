#include "ELM.h"

#ifdef DS_TEST

#include "Test.h"


void RunTest()
{

#ifndef REGRESSION
	int predictedLabels[N_TEST];
#else
	float predictions[N_TEST];
#endif

	int nCorrect = 0;
	int i = 0;
	int j;

	float temp[N_FEATURE];

	float* X_t;

	for (i = 0; i < N_TEST; i++)
	{
		for (j = 0; j < N_FEATURE; j++)
		{
#ifdef DEBUG
//			printf("\n Feature %d = %f ", j, X_test[i][j]);
#endif
			temp[j] = X_test[i][j];
		}
		X_t = preprocess(temp);

#ifdef DEBUG
		for (j = 0; j < N_FEATURE; j++)
		{
//			printf("\n Feature %d after PP = %f ", i, X_t[j]);
		}
#endif

#ifndef REGRESSION
		{

			predictedLabels[i] = (*pClassf)(X_t);

			printf("Test %d: Predicted %d   Test %d\n", i, predictedLabels[i], y_test[i]);
			if (predictedLabels[i] == y_test[i])
			{
				nCorrect++;
			}
		}
#else
		{
			predictions[i] = (*pRegress)(X_t);
		}
#endif
	}

#ifndef REGRESSION
	{
		printf("\nClassifier rate: %f\n", (float)nCorrect * 100.0f / (float)N_TEST);
		//fflush(stdout);
	}
#else
	{
		//TBD, figure for regression
	}
#endif
}

#endif //DS_TEST
