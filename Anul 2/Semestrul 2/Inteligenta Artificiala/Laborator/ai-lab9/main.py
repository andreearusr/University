import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from pandas import DataFrame
from sklearn.preprocessing import StandardScaler

from LogisticRegressionOVR import LogisticRegressionOVR


def loadIrisData():
    from sklearn.datasets import load_iris

    data = load_iris()
    inputs = data.data
    outputs = data.target
    outputNames = data.target_names
    featureNames = list(data.feature_names)
    feature1 = [feat[featureNames.index('sepal length (cm)')] for feat in inputs]
    feature2 = [feat[featureNames.index('petal length (cm)')] for feat in inputs]
    feature3 = [feat[featureNames.index('petal width (cm)')] for feat in inputs]
    feature4 = [feat[featureNames.index('petal width (cm)')] for feat in inputs]
    inputs = [[feat[featureNames.index('sepal length (cm)')], feat[featureNames.index('sepal width (cm)')],
               feat[featureNames.index('petal length (cm)')], feat[featureNames.index('petal width (cm)')]]
              for feat in inputs]

    iris_data = DataFrame(inputs, columns=['Sepal Length', 'Sepal Width', 'Petal Length', 'Petal Width'])
    iris_target = DataFrame(outputs, columns=['Species'])
    iris = pd.concat([iris_data, iris_target], axis=1)

    return iris, inputs, outputs, outputNames


iris, inputs, outputs, outputNames = loadIrisData()


# print(outputNames)
# print(inputs[0], inputs[50], inputs[-5])
# print(outputs[0], outputs[50], outputs[-5])


# step2: split data into train and test

def splitData(Inputs, Outputs):
    np.random.seed(5)
    indexes = [i for i in range(len(Inputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(Inputs)), replace=False)
    testSample = [i for i in indexes if not i in trainSample]

    trainInputs = [Inputs[i] for i in trainSample]
    trainOutputs = [Outputs[i] for i in trainSample]
    testInputs = [Inputs[i] for i in testSample]
    testOutputs = [Outputs[i] for i in testSample]

    return trainInputs, trainOutputs, testInputs, testOutputs


def normalisation(trainData, testData):
    scaler = StandardScaler()
    if not isinstance(trainData[0], list):
        # encode each sample into a list
        trainData = [[d] for d in trainData]
        testData = [[d] for d in testData]

        scaler.fit(trainData)  # fit only on training data
        normalisedTrainData = scaler.transform(trainData)  # apply same transformation to train data
        normalisedTestData = scaler.transform(testData)  # apply same transformation to test data

        # decode from list to raw values
        normalisedTrainData = [el[0] for el in normalisedTrainData]
        normalisedTestData = [el[0] for el in normalisedTestData]
    else:
        scaler.fit(trainData)  # fit only on training data
        normalisedTrainData = scaler.transform(trainData)  # apply same transformation to train data
        normalisedTestData = scaler.transform(testData)  # apply same transformation to test data
    return normalisedTrainData, normalisedTestData


trainInputs, trainOutputs, testInputs, testOutputs = splitData(inputs, outputs)
import seaborn as sns

sns.pairplot(iris, hue='Species', height=2, diag_kind="hist")
plt.show()

# normalise the data
trainInputs, testInputs = normalisation(trainInputs, testInputs)

# sns.pairplot(iris, hue='Species', height=2, diag_kind="hist")
# plt.show()


# classifier = linear_model.LogisticRegression()
# classifier = Logist()
classifier = LogisticRegressionOVR()
classifier.fit(trainInputs, trainOutputs)
classifier._plot_cost(classifier.cost)

predictedLabels = classifier.predict(testInputs)


def evalMultiClass(realLabels, computedLabels, labelNames):
    from sklearn.metrics import confusion_matrix

    confMatrix = confusion_matrix(realLabels, computedLabels)
    acc = sum([confMatrix[i][i] for i in range(len(labelNames))]) / len(realLabels)
    precision = {}
    recall = {}
    for i in range(len(labelNames)):
        precision[labelNames[i]] = confMatrix[i][i] / sum([confMatrix[j][i] for j in range(len(labelNames))])
        recall[labelNames[i]] = confMatrix[i][i] / sum([confMatrix[i][j] for j in range(len(labelNames))])
    return acc, precision, recall, confMatrix


acc, prec, recall, cm = evalMultiClass(np.array(testOutputs), predictedLabels, outputNames)
# plotConfusionMatrix(cm, outputNames, "iris classification")

print('acc: ', acc)
print('precision: ', prec)
print('recall: ', recall)
