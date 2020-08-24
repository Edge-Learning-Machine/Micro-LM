#ifdef HW_TripleExpoSmoothing_H
#define HW_TripleExpoSmoothing_H

#include "ELM.h"
#include <stdbool.h>

#include "TripleES_params.h"

int* HW_TripleExpoSmoothing(int arrayD[], int vlen, double alpha, double beta, double gamma,
	int slen, int n_preds, double scaling_factor);

#endif



