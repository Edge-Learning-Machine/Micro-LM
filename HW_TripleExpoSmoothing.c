#include "ELM.h"

#ifdef TES

#include <stdio.h>
#include <stdlib.h>
#include "HW_TripleExpoSmoothing.h"
#include "TripleES_params.h"

int* HW_TripleExpoSmoothing(int arrayD[], int vlen, double alpha, double beta, double gamma,
	int slen, int n_preds, double scaling_factor)
{
	//initial trend
	int tot = vlen + n_preds;
	double sum = 0.0;
	double initial_trend = 0.0;
	for (int i = 0; i < slen; i++)
	{
		sum += (double)(((arrayD[i + slen] - arrayD[i])) / slen);
	}
	initial_trend = sum / (double)slen;

	//initial_seasonal_components
	double *seasonals;
	seasonals = malloc(tot * sizeof(double));
	double *season_averages;
	season_averages = malloc(tot * sizeof(double));

	for (int j = 0; j < tot; j++)
	{
		seasonals[j] = 0.0;
		season_averages[j] = 0.0;
	}

	int n_seasons = (int)(vlen / slen);
	double somma = 0.0;
	//let's calculate season averages
	for (int j = 0; j < n_seasons; j++)
	{
		for (int h = slen * j; h < ((slen * j) + slen); h++)
		{
			somma += arrayD[h];
		}
		season_averages[j] = somma / (double) slen;
	}
	//let's calculate initial values
	for (int i = 0; i < slen; i++)
	{
		double sum_of_vals_over_avg = 0.0;
		for (int j = 0; j < n_seasons; j++)
		{
			sum_of_vals_over_avg += arrayD[(slen * j) + i] - season_averages[j];
		}
		seasonals[i] = sum_of_vals_over_avg / (double)n_seasons;
	}


	//triple_exponential_smoothing
	double smooth = 0.0;
	double trend = 0.0;

    int *result;
	result = malloc(tot * sizeof(int));
	double *Smooth;
	Smooth = malloc(tot * sizeof(double));
	double *Trend;
	Trend = malloc(tot * sizeof(double));
	double *Season;
	Season = malloc(tot * sizeof(double));
	double *PredictedDeviation;
	PredictedDeviation = malloc(tot * sizeof(double));

	for (int j = 0; j < tot; j++)
	{
		result[j] = 0;
		Smooth[j] = 0.0;
		Trend[j] = 0.0;
		Season[j] = 0.0;
		PredictedDeviation[j] = 0.0;
	}

	for (int i = 0; i < tot; i++)
	{
		if (i == 0) //components initialization
		{
			smooth = (double)arrayD[i];
			trend = initial_trend;
			result[i] = arrayD[i];
			Smooth[i] = smooth;
			Trend[i] = trend;
			Season[i] = seasonals[i % slen];

			PredictedDeviation[i] = 0;
			continue;
		}
		if (i >= vlen) //predicting
		{
			int m = i - vlen + 1;
			result[i] = (int)(((smooth + m * trend) + seasonals[i % slen]));

			// when predicting we increase uncertainty on each step
			PredictedDeviation[i] = PredictedDeviation[i-1] * 1.01;
		}
		else
		{
			double val = (double)arrayD[i];
			double last_smooth = smooth;
			smooth = (alpha * (val - seasonals[i % slen])) + ((1 - alpha) * (smooth + trend));
			trend = (beta * (smooth - last_smooth)) + ((1 - beta) * trend);
			seasonals[i % slen] = (gamma * (val - smooth)) + ((1 - gamma) * seasonals[i % slen]);
			result[i] = (int)(smooth + trend + seasonals[i % slen]);

			Smooth[i] = smooth;
			Trend[i] = trend;
			Season[i] = seasonals[i % slen];
		}
	}
	int *res;
	res = malloc(n_preds*sizeof(int));
	for (int i=0; i<n_preds; i++)
	{
		res[i] = result[vlen+i];
	}

	free (seasonals);
	free (season_averages);
	free (result);
	free (Smooth);
	free (Trend);
	free (Season);
	free (PredictedDeviation);

	return res;

}
#endif
