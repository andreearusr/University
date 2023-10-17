import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from pandas import DataFrame
from sklearn.preprocessing import StandardScaler

# step1: load the data
from NeuralNetwork import NeuralNetwork


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


# step2: split data into train and test

def splitData(inputs, outputs):
    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
    testSample = [i for i in indexes if not i in trainSample]

    trainInputs = [inputs[i] for i in trainSample]
    trainOutputs = [outputs[i] for i in trainSample]
    testInputs = [inputs[i] for i in testSample]
    testOutputs = [outputs[i] for i in testSample]

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

# sns.pairplot(iris, hue='Species', height=2, diag_kind="hist")
# plt.show()

# normalise the data
trainInputs, testInputs = normalisation(trainInputs, testInputs)

# liniar classifier and one-vs-all approach for multi-class
# classifier = linear_model.LogisticRegression()

# non-liniar classifier and softmax approach for multi-class
# classifier = neural_network.MLPClassifier(hidden_layer_sizes=(5,), activation='relu', max_iter=100, solver='sgd',
#                                          verbose=10, random_state=1, learning_rate_init=.1)


epochs = 1000
lr = 0.01


m = len(trainInputs)

trainOutputs = np.array(trainOutputs)
trainOutputs = [[d] for d in trainOutputs]

print(np.array(trainInputs))
print(np.array(trainOutputs))

nn1 = NeuralNetwork(np.array(trainInputs), np.array(trainOutputs), 64)
loss = []
iterations = []
for i in range(epochs):
    nn1.FeedForward()
    nn1.BackPropogation(lr)
    cost = (1 / m) * np.sum(np.square(nn1.y - nn1.output))
    print("Cost: {} ".format(cost))

    loss.append(cost)
    iterations.append(i)

plt.plot(iterations, loss)
plt.show()
