#include "ELM.h"

#ifdef RF

#include "RF.h"
#include <stdio.h>
#include <stdbool.h>

#ifdef DS_TEST
void randomForest_test_dataset(bool isRegression)
{

    #ifndef REGRESSION
        int predictedLabels[N_TEST];
    #else
        float predictions[N_TEST];
    #endif

    int nCorrect = 0;
    int i = 0;

    for (i = 0; i < N_TEST; i++)
    {
        #ifndef REGRESSION
        {
            predictedLabels[i] = randomForest_classification(X_test[i]);
            if (predictedLabels[i] == y_test[i])
            {
                nCorrect++;
            }
        }
        #else
        {
            predictions[i] = randomForest_regression(X_test[i]);
        }
        #endif
    }

    #ifndef REGRESSION
    {
        printf("\nRandom forest rate: %f\n", (float)nCorrect * 100.0f / (float)N_TEST);
        fflush(stdout);
    }
    #else
    {
        //TBD, figure for regression
    }
    #endif
}
#endif


#ifndef REGRESSION
int randomForest_classification(float X[])
{
    int currentNode = 0;
	float probab[FOREST_DIM][N_CLASS];
	bool next_tree = 0;
	
	int maxClass = -1;
    float maxValue = 0;
	
	//compute the classification for each tree
	for(int i=0; i< FOREST_DIM; i++)
	{
		next_tree=0;
		currentNode = 0;
		
		while (next_tree==0)
		{
			//travel the tree
			if (*(forest_feature[i] + currentNode) >= 0)
			{
				if (X[*(forest_feature[i] + currentNode)] <= *(forest_threshold[i] +currentNode))
				{
					currentNode = *(forest_children_left[i] +currentNode);
				}
				else
				{
					currentNode = *(forest_children_right[i] + currentNode);
				}
			}
			else
			{ // Leaf node
				{
					// inside each leaf note are stored the number of sample divided between the classes; the probability of each prediction is value/total samples
					int j;
					float total_samples=0;

					
					
					for (j = 0; j < N_CLASS; j++)
					{
						total_samples += (float)*(forest_values[i] + currentNode * N_CLASS + j);
					}
					for (j = 0; j < N_CLASS; j++)
					{
						probab[i][j]= (float)*(forest_values[i] + currentNode * N_CLASS + j) / (float)total_samples;
					}
					
				}
				next_tree = 1;
			}
		}
	}	

	/// once the prob array is built, it's required to compute the soft majority voting
	// for each classes the probability between all the trees are added togheter and the highest probability is the "winning" class 
	float result[N_CLASS];
	
	//init the array
	for(int i=0; i < N_CLASS; i++ )
		result[i]=0;
    
	for(int i=0; i< FOREST_DIM; i++)
	{
		for(int j=0; j < N_CLASS; j++ )
			result[j] += probab[i][j]; 
	}
	
	
    for (int j = 0; j < N_CLASS; j++)
    {
        if (result[j] >= maxValue)
        {
            maxValue = result[j];
            maxClass = target_classes[j];
        }
    }
	return maxClass;
}



#else
float randomForest_regression(float X[])
{
    int currentNode = 0;
	bool next_tree = 0;
	float result=0;
	
    for(int i=0; i< FOREST_DIM; i++)
	{
		next_tree=0;
		
		while (next_tree==0)
		{
			//travel the tree
			if ((*forest_feature[i])[currentNode] >= 0)
			{
				if (X[(*forest_feature[i])[currentNode]] <= (*forest_threshold[i])[currentNode])
				{
					currentNode = (*forest_children_left[i])[currentNode];
				}
				else
				{
					currentNode = (*forest_children_right[i])[currentNode];
				}
			}
        else
        { // Leaf node
            result +=  (*forest_values[i])[currentNode][0];
        }
		next_tree=1;
    }
	return result / (float)FOREST_DIM;
}
#endif

#endif