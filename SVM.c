#include "ELM.h"

#ifdef SVM

#include "svm.h"
#include <stdio.h>
#include <stdbool.h>

#ifdef DS_TEST
#ifdef REGRESSION
float (*pRegress)(float X[]) = svm_regression;
#else
int (*pClassf)(float X[]) = svm_classification;
#endif
#endif

float *PCA_transform(float *);




#ifndef REGRESSION
int svm_classification(float X[])
{
    int m;
    if (N_CLASS == 2)
    {
        float y = bias[0];
        int k;
        for (k = 0; k < N_FEATURE; k++)
        {
            y += support_vectors[0][k] * X[k];
        }
        if (y < 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        float bestDistance = -1000000;
        for (m = 0; m < N_CLASS; m++)
        {
            float y = bias[m];
            int k;
            for (k = 0; k < N_FEATURE; k++)
            {
                y += support_vectors[m][k] * X[k];
            }
            if (y > bestDistance)
            {
                bestDistance = y;
                return m;
            }
        }
    }
}
#endif

#ifdef REGRESSION
float svm_regression(float X[])
{
    float y = bias[0];
    int k;
    for (k = 0; k < N_FEATURE; k++)
    {
        y += support_vectors[0][k] * X[k];
    }

    /*
    #ifdef MINMAX_SCALING
        y = y / S_Y;
    #elif defined (STANDARD_SCALING)
        y = y * S_Y + U_Y;
    #endif
	*/
    return y;
}
#endif

#endif

