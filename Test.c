#include "Test.h"
#include "ELM.h"

void RunTest()
{

    #ifndef REGRESSION
        int predictedLabels[N_TEST];
    #else
        float predictions[N_TEST];
    #endif

    int nCorrect = 0;
    int i = 0;
	int j,k;
	
	float temp[N_FEATURE];
	
	float *X_t;
	
    for (i = 0; i < N_TEST; i++)
    {
		for(j =0; j< N_FEATURE; j++)
		{
			temp[j] = X_test[i][j];
		}
		X_t = preprocess(temp);
		
        #ifndef REGRESSION
        {
			
            predictedLabels[i] = (*pClassf)(X_t);
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

