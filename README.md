# Micro-LM
A plain C library for machine learning on edge devices.

Micro-LM currently implements the following ML algorithms:

- `Linear SVM`
- `Decision Tree`
- `K-NN`
- `TripleES`, Holt-Winters Triple Exponential Smoothing for time series

Each algorithm provides both classification and regression, for binary and multiclass problems. `SVM` supports only ordinal multiclass classification. `Holt-Winters Triple Exponential Smoothing` supports only regression.

We are extending the library to other algorithms, also unsupervised. Your voluntary contribution is welcome.

The library is optimized for memory footprint. [`Desk-LM`](https://github.com/Edge-Learning-Machine/Desk-LM) performs model training and cross-validation, and creates .c and .h files that store the best model's parameters. These files must be compiled together with the [`Micro-LM`](https://github.com/Edge-Learning-Machine/Micro-LM) files available in this repository.

As an alternative, we are working for a dynamic configuration of Micro-LM through .json files produced by [`Desk-LM`](https://github.com/Edge-Learning-Machine/Desk-LM).

## Usage

You can compile the code as an executable or as a static library, using gcc/g++ for a Microcontroller or a desktop (e.g., thorugh Eclipse CDT or Visual Studio Code).

The Micro-LM files need to be compiled together with the .c and .h files produced by [`Desk-LM`](https://github.com/Edge-Learning-Machine/Desk-LM).

The program must be configured in `ELM.h`, where the user has to specify some `#define`, such as:
- The algorithm: `SVM`, `DT`, `KNN` or `TripleES`
- `DS_TEST`, if you want to test performance in a dataset, instead of doing one shot estimations. Used only by: knn, decisionTree, svm.
- `REGRESSION`, if you want to perform a regression. Default is classification (no regression). Used only by: knn, decisionTree, svm. TES performs only regression

`ELM.h` exposes the following functions:
- *`preprocess(X)`*, where X is the sample vector
- *`algo_classification(X)`*, where X is the sample vector. Algo is: knn, decisionTree, svm.
- *`algo_regression(X)`*, where X is the sample vector. Algo is: knn, decisionTree, svm.
- *`algo_test_dataset(isRegression)`*, for (whole or minimal) dataset testing. Algo is: knn, decisionTree, svm.
- *`HW_TripleExpoSmoothing(int arrayD[], int vlen, double alpha, double beta, double gamma,int slen, int n_preds, double scaling_factor)`*, for Holt-Winters time series

## Data type
float 32 data are used

## License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/Edge-Learning-Machine/Micro-LM/blob/master/LICENSE.md) file for details

## Contributing
Please see [CONTRIBUTING.md](https://github.com/Edge-Learning-Machine/Desk-LM/blob/master/docs/CONTRIBUTING.md)

## Reference article for more infomation
F., Sakr, F., Bellotti, R., Berta, A., De Gloria, "Machine Learning on Mainstream Microcontrollers," Sensors 2020, 20, 2638.
https://www.mdpi.com/1424-8220/20/9/2638

## References
https://medium.com/open-machine-learning-course/open-machine-learning-course-topic-9-time-series-analysis-in-python-a270cb05e0b3
