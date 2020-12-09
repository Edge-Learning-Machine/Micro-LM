#include "ELM.h"

#ifdef RF

#include "RF.h"
#include <stdio.h>
#include <stdbool.h>

#ifdef DS_TEST
#ifdef REGRESSION
float (*pRegress)(float X[]) = randomForest_regression;
#else
int (*pClassf)(float X[]) = randomForest_classification;
#endif
#endif


#ifndef REGRESSION
int randomForest_classification(float X[])
{
	int currentNode = 0;
	float probab[FOREST_DIM][N_CLASS];
	bool next_tree = 0;

	int maxClass = -1;
	float maxValue = 0;

	float result[N_CLASS];

	//compute the classification for each tree
	for (int i = 0; i < FOREST_DIM; i++)
	{
		next_tree = 0;
		currentNode = 0;

#ifdef DEBUG
		printf("\n\nalbero %d della forest", i);
#endif
		while (next_tree == 0)
		{
			
			//travel the tree
			if (*(forest_feature[i] + currentNode) >= 0)
			{
				if (X[*(forest_feature[i] + currentNode)] <= *(forest_threshold[i] + currentNode))
				{
					#ifdef DEBUG
					printf("\ncurrent node: %d, X:%f <= %f\n", currentNode, X[*(forest_feature[i] + currentNode)], *(forest_threshold[i] + currentNode));
					fflush(stdout);
					#endif
													
					currentNode = *(forest_children_left[i] + currentNode);
				}
				else
				{
					#ifdef DEBUG
					printf("\ncurrent node: %d, X:%f <= %f\n", currentNode, X[*(forest_feature[i] + currentNode)], *(forest_threshold[i] + currentNode));
					fflush(stdout);
					#endif
							
					currentNode = *(forest_children_right[i] + currentNode);
				}
			}
			else
			{ // Leaf node

				// inside each leaf note are stored the number of sample divided between the classes; the probability of each prediction is value/total samples
				int j, k;
				int total_samples = 0;

				for (k = 0; k < forest_num_leaves[i]; k++)
				{
					if (*(forest_leaves[i] + k * (N_CLASS + 2)) == currentNode)
					{
						for (j = 0; j < N_CLASS; j++)
						{
							total_samples += *(forest_leaves[i] + k * (N_CLASS + 2) + j + 2);
						}
						for (j = 0; j < N_CLASS; j++)
						{
							probab[i][j] = (float)*(forest_leaves[i] + k * (N_CLASS + 2) + j + 2) / (float)total_samples;
#ifdef DEBUG
							printf("\nProbab class: %d = %f", j, probab[i][j]);
							fflush(stdout);
#endif
						}
					}

				}
				next_tree = 1;
			}

		}
	}
	/// once the prob array is built, it's required to compute the soft majority voting
	// for each classes the probability between all the trees are added togheter and the highest probability is the "winning" class 




	for (int i = 0; i < FOREST_DIM; i++)
	{
		for (int j = 0; j < N_CLASS; j++)
		{
			if(i==0)
				result[j] = 0; //init the array
			result[j] += probab[i][j];
#ifdef DEBUG
			printf("\n\n\nResult probab class: %d = %f", j, result[j]);
			fflush(stdout);
#endif
		}
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
	float result = 0;

	for (int i = 0; i < FOREST_DIM; i++)
	{
		next_tree = 0;

		while (next_tree == 0)
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
				result += (*forest_values[i])[currentNode][0];
			}
			next_tree = 1;
		}
		return result / (float)FOREST_DIM;
	}
#endif

#endif