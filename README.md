# Desk-LM
A plain C library for machine learning on edge devices


Micro-ML is a plain C library for machine learning on edge devices (it can be used also on desktops). It currently implements the following ML algorithms:

- Linear SVM
- Decision Tree
- K-NN

Each algorithm provides both classification and regression, for binary and multiclass problems. SVM supports only ordinal multiclass classification.

We are extending the library to other algorithms, also unsupervised. Your voluntary contribution is welcome.

At present, the library is optimized for memory footprint. [Desk-LM](https://github.com/Edge-Learning-Machine/Desk-LM) performs model training and cross-validation, and creates .c and .h files that store the best model's parameters. These files must be compiled together with the Micro-LM files available in this repository.

We are currently working to provide dynamic configurability to all the algorithms.

## Reference article for more infomation
F., Sakr, F., Bellotti, R., Berta, A., De Gloria, "Machine Learning on Mainstream Microcontrollers," Sensors 2020, 20, 2638.
https://www.mdpi.com/1424-8220/20/9/2638

## Usage

You can compile the code as an executable or as a static library, using gcc/g++ for a Microcontroller or a desktop (e.g., thorugh Eclipse CDT or Visual Studio Code).

The Micro-LM files need to be compiled together with the .c and .h files produced by [Desk-LM](https://github.com/Edge-Learning-Machine/Desk-LM).

The program must be configured in ELM.h, where the user has to specify some '<#define>', such as:
- The algorithm: SVM or DT or KNN
- DS_TEST, if you want to test performance in a dataset, instead of doing one shot estimations
- REGRESSION, if you want to perform a regression. Default is classification (no regression)

ELM.h exposes the following functions:
- *preprocess(X)*, where X is the sample vector
- *algo_classification(X)*, where X is the sample vector. algo is knn, decisionTree, svm
- *algo_classification(X)*, where X is the sample vector. algo is knn, decisionTree, svm
- *algo_test_dataset(isRegression)*, for (whole or minimal) dataset testing. algo is knn, decisionTree, svm
