#include "ELM.h"

#ifdef KNN

#include "KNN.h"
#include <stdio.h>

#include "math.h"
#include <stdlib.h> // To check if works on STM32
#include <string.h> // To check if works on STM32

#ifdef DS_TEST
#ifdef REGRESSION
float (*pRegress)(float X[]) = knn_regression;
#else
int (*pClassf)(float X[]) = knn_classification;
#endif
#endif


struct neighbour{
        int id;
        float score;
        #ifdef REGRESSION
        float label;
        #endif
    };
int struct_cmp_by_score_dec(const void *, const void *);

//int regressionLabels[N_CLASS]; //Attention!!!!!!!!



#ifndef REGRESSION
int knn_classification(float X[]) {
    // KNN
    // https://www.geeksforgeeks.org/weighted-k-nn/
    struct neighbour neighbours[N_TRAIN];

    int j;
    for(j=0; j < N_TRAIN; j++){
        neighbours[j].id = j;

        float acc=0;
        bool skip=false;
        int k;
        for(k=0; k < N_FEATURE; k++) {
            acc+=(X[k] - X_train[j][k])*(X[k] - X_train[j][k]);
            if (acc > 10000000) {
                neighbours[j].score = 0;
                skip=true;
                break;
            }
        }
        if (!skip){
            acc = sqrt(acc);
            if (acc < 0.00000001) {
                neighbours[j].score = 100000000;
            } else {
                neighbours[j].score = 1 / acc;
            }
        }
    }
    qsort(neighbours, N_TRAIN, sizeof(struct neighbour), struct_cmp_by_score_dec);
    
    {
        int n;
        float scores[N_CLASS];
        memset(scores, 0, N_CLASS*sizeof(float)); 
        for(n=0; n<K; n++) {
            scores[y_train[neighbours[n].id]] += neighbours[n].score;
        }
        float bestScore=0;
        int bestClass;
        for(n=0; n<N_CLASS; n++) {
            if (scores[n] > bestScore) {
                bestScore = scores[n];
                bestClass = n;
            }
        }
        return(bestClass);
    }
}
#endif

#ifdef REGRESSION
float knn_regression(float X[]) {
    // KNN
    // https://www.geeksforgeeks.org/weighted-k-nn/
    struct neighbour neighbours[N_TRAIN];
    
        int j;
        for(j=0; j < N_TRAIN; j++){
            neighbours[j].id = j;

            // if needed, could be used also for classification
            neighbours[j].label = y_train[j];

            float acc=0;
            bool skip=false;
            int k;
            for(k=0; k < N_FEATURE; k++) {
                acc+=(X[k] - X_train[j][k])*(X[k] - X_train[j][k]);
                if (acc > 10000000) {
                    neighbours[j].score = 0;
                    skip=true;
                    break;
                }
            }
            if (!skip){
                acc = sqrt(acc);
                if (acc < 0.00000001) {
                    neighbours[j].score = 100000000;
                } else {
                    neighbours[j].score = 1 / acc;
                }
            }
        }
        qsort(neighbours, N_TRAIN, sizeof(struct neighbour), struct_cmp_by_score_dec);
        
        {
            float totalScore = 0;
            float pred = 0;
            int n = 0;
            for(n=0; n<K; n++) {
                pred += (neighbours[n].label * neighbours[n].score);
                totalScore += neighbours[n].score;
            }
            pred /= totalScore;
            
            #ifdef MINMAX_NORMALIZATION
                pred = pred / S_Y;
            #elif defined(STANDARD_SCALING)
                pred = pred * S_Y + U_Y;
            #endif
            printf("Prediction: %f", pred);
            return pred;
        }
}
#endif

/* qsort struct comparision function (price float field) */ 
int struct_cmp_by_score_dec(const void *a, const void *b) 
{ 
    struct neighbour *ia = (struct neighbour *)a;
    struct neighbour *ib = (struct neighbour *)b;
    return -(int)(100000.f*ia->score - 100000.f*ib->score);
	/* float comparison: returns negative if b > a 
	and positive if a > b. We multiplied result by 100.0
	to preserve decimal fraction */ 
    //Decreasing
} 
#endif




