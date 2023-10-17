import csv
import os
from statistics import mean, stdev

import numpy as np
from matplotlib import pyplot as plt
from sklearn.preprocessing import StandardScaler

from SGD import MySGDRegression


# load all the data from a csv file
def loadDataMoreInputs(fileName):
    data = []
    dataNames = []
    with open(fileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                dataNames = row
            else:
                data.append(row)
            line_count += 1
    return dataNames, data


def loadDataMoreInputs(fileName, inputVariabNames, outputVariabName):
    data = []
    dataNames = []
    with open(fileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                dataNames = row
            else:
                data.append(row)
            line_count += 1
    selectedVariable1 = dataNames.index(inputVariabNames[0])
    selectedVariable2 = dataNames.index(inputVariabNames[1])
    inputs = [[float(data[i][selectedVariable1]), float(data[i][selectedVariable2])] for i in range(len(data))]
    selectedOutput = dataNames.index(outputVariabName)
    outputs = [float(data[i][selectedOutput]) for i in range(len(data))]

    return inputs, outputs


def plot3Ddata(x1Train, x2Train, yTrain, x1Model=None, x2Model=None, yModel=None, x1Test=None, x2Test=None, yTest=None,
               title=None):
    ax = plt.axes(projection='3d')

    if (x1Train):
        ax.scatter3D(x1Train, x2Train, yTrain, c='r', marker='o', label='train data')
    if (x1Model):
        ax.scatter3D(x1Model, x2Model, yModel, c='b', marker='*', label='learnt model')
    if (x1Test):
        ax.scatter3D(x1Test, x2Test, yTest, c='g', marker='^', label='test data')

    plt.title(title)
    ax.set_xlabel("capita")
    ax.set_ylabel("freedom")
    ax.set_zlabel("happiness")
    plt.legend()
    plt.show()


def plotDataHistogram(x, variableName):
    n, bins, patches = plt.hist(x, 10)
    plt.title('Histogram of ' + variableName)
    plt.show()


# load data
crtDir = os.getcwd()
filePath = os.path.join(crtDir, 'world-happiness-report-2017.csv')

inputs, outputs = loadDataMoreInputs(filePath, ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score')

feature1 = [ex[0] for ex in inputs]
feature2 = [ex[1] for ex in inputs]

# plot the data histograms
plotDataHistogram(feature1, 'capita GDP')
plotDataHistogram(feature2, 'freedom')
plotDataHistogram(outputs, 'Happiness score')

# check the liniarity (to check that a linear relationship exists between the dependent variable (y = happiness) and the independent variables (x1 = capita, x2 = freedom).)
plot3Ddata(feature1, feature2, outputs, [], [], [], [], [], [], 'capita vs freedom vs happiness')


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


def normalizationZ(feature, m, s):
    featureNormalized = [(f - m) / s for f in feature]
    return featureNormalized


# statistical normalisation (centered around meand and standardisation)
def statisticalNormalisation(features):
    # meanValue = sum(features) / len(features)
    meanValue = mean(features)
    # stdDevValue = (1 / len(features) * sum([ (feat - meanValue) ** 2 for feat in features])) ** 0.5
    stdDevValue = stdev(features)
    normalisedFeatures = [(feat - meanValue) / stdDevValue for feat in features]
    return normalisedFeatures


np.random.seed(5)
indexes = [i for i in range(len(inputs))]
trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
testSample = [i for i in indexes if not i in trainSample]

trainInputs = [inputs[i] for i in trainSample]
trainOutputs = [outputs[i] for i in trainSample]
testInputs = [inputs[i] for i in testSample]
testOutputs = [outputs[i] for i in testSample]

trainInputs, testInputs = normalisation(trainInputs, testInputs)
trainOutputs, testOutputs = normalisation(trainOutputs, testOutputs)

feature1train = [ex[0] for ex in trainInputs]
feature2train = [ex[1] for ex in trainInputs]

feature1test = [ex[0] for ex in testInputs]
feature2test = [ex[1] for ex in testInputs]

'''
m1 = sum(feature1train) / len(feature1train)
s1 = (1 / len(feature1train) * sum([(f - m1) ** 2 for f in feature1train])) ** 0.5

m2 = sum(feature2train) / len(feature2train)
s2 = (1 / len(feature2train) * sum([(f - m2) ** 2 for f in feature2train])) ** 0.5

feature1train = statisticalNormalisation(feature1train)
feature2train = statisticalNormalisation(feature2train)
feature1test = statisticalNormalisation(feature1test)
feature2test = statisticalNormalisation(feature2test)

m1O = sum(trainOutputs) / len(trainOutputs)
s1O = (1 / len(trainOutputs) * sum([(f - m1O) ** 2 for f in trainOutputs])) ** 0.5

trainOutputs = statisticalNormalisation(trainOutputs)
testOutputs = statisticalNormalisation(testOutputs)


f1train = statisticalNormalisation(feature1train)
f2train = statisticalNormalisation(feature2train)
f1test = statisticalNormalisation(feature1test)
f2test = statisticalNormalisation(feature2test)
'''

plot3Ddata(feature1train, feature2train, trainOutputs, [], [], [], feature1test, feature2test, testOutputs,
           "train and test data (after normalisation)")


# from sklearn import linear_model
# regressor = linear_model.SGDRegressor()
# regressor = linear_model.SGDRegressor(learning_rate='constant', alpha=0, eta0=0.01, shuffle=True, max_iter=10000)

regressor = MySGDRegression()

regressor.fit(trainInputs, trainOutputs)

# parameters of the liniar regressor
w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]
print('the learnt model: f(x) = ', w0, ' + ', w1, ' * x1 + ', w2, ' * x2')

# numerical representation of the regressor model
noOfPoints = 50
xref1 = []
val = min(feature1)
step1 = (max(feature1) - min(feature1)) / noOfPoints
for _ in range(1, noOfPoints):
    for _ in range(1, noOfPoints):
        xref1.append(val)
    val += step1

xref2 = []
val = min(feature2)
step2 = (max(feature2) - min(feature2)) / noOfPoints
for _ in range(1, noOfPoints):
    aux = val
    for _ in range(1, noOfPoints):
        xref2.append(aux)
        aux += step2
yref = [w0 + w1 * el1 + w2 * el2 for el1, el2 in zip(xref1, xref2)]

plot3Ddata(feature1train, feature2train, trainOutputs, xref1, xref2, yref, [], [], [],
           'train data and the learnt model')

# use the trained model to predict new inputs

# makes predictions for test data
# computedTestOutputs = [w0 + w1 * el[0] + w2 * el[1] for el in testInputs]
# makes predictions for test data (by tool)
computedTestOutputs = regressor.predict(testInputs)

plot3Ddata([], [], [], feature1test, feature2test, computedTestOutputs, feature1test, feature2test, testOutputs,
           'predictions vs real test data')

# compute the differences between the predictions and real outputs
error = 0.0
for t1, t2 in zip(computedTestOutputs, testOutputs):
    error += (t1 - t2) ** 2
error = error / len(testOutputs)
print('prediction error (manual): ', error)

from sklearn.metrics import mean_squared_error

error = mean_squared_error(testOutputs, computedTestOutputs)
print('prediction error (tool):   ', error)
