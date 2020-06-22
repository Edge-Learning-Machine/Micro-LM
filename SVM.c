#include "ELM.h"

#ifdef SVM

#include "svm.h"
#include <stdio.h>
#include <stdbool.h>

float *PCA_transform(float *);

#ifdef REGRESSION
void svr_test_dataset();
#else
void svc_test_dataset();
#endif

#ifdef DS_TEST
void svm_test_dataset(bool isRegression)
{
#ifdef REGRESSION
    svr_test_dataset();
#else
    svc_test_dataset();
#endif
}

#ifndef REGRESSION
void svc_test_dataset()
{
    int predictedLabels[N_TEST];
    int nCorrect = 0;
    int i = 0;

    nCorrect = 0;
    for (i = 0; i < N_TEST; i++)
    {
        predictedLabels[i] = svm_classification(X_test[i]);
        if (predictedLabels[i] == y_test[i])
        {
            nCorrect++;
        }
    }
    printf("\nLinear SVM rate: %f\n", (float)nCorrect * 100.0f / (float)N_TEST);
    fflush(stdout);
}
#endif

#ifdef REGRESSION
void svr_test_dataset()
{
    float predictions[N_TEST];
    int i = 0;

    for (i = 0; i < N_TEST; i++)
    {
        predictions[i] = svm_regression(X_test[i]);
    }

    //TBD
    //Compute final figure
}
#endif
#endif

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
