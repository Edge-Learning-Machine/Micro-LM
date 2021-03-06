#include "ELM.h"

#ifdef DT

#include "dt.h"
#include <stdio.h>
#include <stdbool.h>


#ifdef REGRESSION
float (*pRegress)(float X[]) = decisionTree_regression;
#else
int (*pClassf)(float X[]) = decisionTree_classification;
#endif


#ifndef REGRESSION
int decisionTree_classification(float X[])
{
	int currentNode = 0;
	while (1)
	{
		if (feature[currentNode] >= 0)
		{
			if (X[feature[currentNode]] <= threshold[currentNode])
			{
#ifdef DEBUG
				printf("\ncurrent node: %d, X:%f <= %f\n", currentNode, X[feature[currentNode]], threshold[currentNode]);
				fflush(stdout);
#endif
				currentNode = children_left[currentNode];
			}
			else
			{
#ifdef DEBUG
				printf("\ncurrent node: %d, X:%f > %f\n", currentNode, X[feature[currentNode]], threshold[currentNode]);
				fflush(stdout);
#endif
				currentNode = children_right[currentNode];
			}
		}
		else
		{ // Leaf node
			/*{
				int j;
				int maxClass;
				int maxValue = 0;
				for (j = 0; j < N_CLASS; j++)
				{
					if (values[currentNode][j] >= maxValue)
					{
						maxValue = values[currentNode][j];
						maxClass = target_classes[j];
					}
				}
				return maxClass;
			}
			break;*/
			int j;
			for (j = 0; j < N_LEAVES; j++) {
				if (leaf_nodes[j][0] == currentNode) {
					int maxIdx = leaf_nodes[j][1];
					int maxClass = target_classes[maxIdx];
					printf("\ncurrent node: %d, decision: %d\n", currentNode, maxClass);
					fflush(stdout);
					return maxClass;
				}
			}
		}
	}
}
#else
float decisionTree_regression(float X[])
{
	int currentNode = 0;
	while (1)
	{
		if (feature[currentNode] >= 0)
		{
			if (X[feature[currentNode]] <= threshold[currentNode])
			{
				currentNode = children_left[currentNode];
			}
			else
			{
				currentNode = children_right[currentNode];
			}
		}
		else
		{ // Leaf node
			return values[currentNode][0];
		}
	}
}
#endif

#endif
