import csv
import os

import matplotlib.pyplot as plt
import numpy as np
from sklearn import linear_model


def makeAprox(newData, var_name, feature):
    l_1 = []
    l_2 = []
    for i in range(len(newData)):
        rez1 = float(newData[i][var_name])
        rez2 = float(newData[i][feature])
        l_1.append(rez1)
        l_2.append(rez2)

    list_a = []
    for i in range(len(l_1)):
        if l_2[i] == 0:
            a = 0
        else:
            a = l_1[i] / l_2[i]
        list_a.append(a)

    mean_a = sum(list_a) / len(list_a)
    return mean_a


# load data and consider a single feature (Economy..GDP.per.capita) and the output to be estimated (happiness)
def loadData(fileName, inputVariabName, outputVariabName):
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
    selectedVariable = dataNames.index(inputVariabName)
    selectedOutput = dataNames.index(outputVariabName)

    oldData = data

    for i in range(len(data) - 1, -1, -1):
        if data[i][selectedVariable] == '':
            data.remove(data[i])

    a_1 = makeAprox(data, selectedOutput, selectedVariable)

    for i in range(len(oldData)):
        if oldData[i][selectedVariable] == '':
            oldData[i][selectedVariable] = str(float(oldData[i][outputVariabName]) / a_1)

    inputs = [float(oldData[i][selectedVariable]) for i in range(len(oldData))]
    outputs = [float(oldData[i][selectedOutput]) for i in range(len(oldData))]

    return inputs, outputs


# put all steps togheter
# using sklearn

def plotData(x1, y1, x2=None, y2=None, x3=None, y3=None, title=None):
    plt.plot(x1, y1, 'ro', label='train data')
    if (x2):
        plt.plot(x2, y2, 'b-', label='learnt model')
    if (x3):
        plt.plot(x3, y3, 'g^', label='test data')
    plt.title(title)
    plt.legend()
    plt.show()


crtDir = os.getcwd()
# filePath = os.path.join(crtDir, 'v1_world-happiness-report-2017.csv')
# filePath = os.path.join(crtDir, 'v2_world-happiness-report-2017.csv')
filePath = os.path.join(crtDir, 'v3_world-happiness-report-2017.csv')

inputs, outputs = loadData(filePath, 'Economy..GDP.per.Capita.', 'Happiness.Score')


# see how the data looks (plot the histograms associated to input data - GDP feature - and output data - happiness)
def plotDataHistogram(x, variableName):
    n, bins, patches = plt.hist(x, 10)
    plt.title('Histogram of ' + variableName)
    plt.show()


plotDataHistogram(inputs, 'capita GDP')
plotDataHistogram(outputs, 'Happiness score')

# check the liniarity (to check that a linear relationship exists between the dependent variable (y = happiness) and the independent variable (x = capita).)
plotData(inputs, outputs, [], [], [], [], 'capita vs. hapiness')

# split data into training data (80%) and testing data (20%)
np.random.seed(5)
indexes = [i for i in range(len(inputs))]
trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
validationSample = [i for i in indexes if not i in trainSample]

trainInputs = [inputs[i] for i in trainSample]
trainOutputs = [outputs[i] for i in trainSample]

validationInputs = [inputs[i] for i in validationSample]
validationOutputs = [outputs[i] for i in validationSample]

plotData(trainInputs, trainOutputs, [], [], validationInputs, validationOutputs, "train and test data")

# training step
xx = [[el] for el in trainInputs]
regressor = linear_model.LinearRegression()
# regressor = linear_model.SGDRegressor(max_iter =  10000)
regressor.fit(xx, trainOutputs)
w0, w1 = regressor.intercept_, regressor.coef_

# # using developed code
# from myRegression import MyLinearUnivariateRegression

# # model initialisation
# regressor = MyLinearUnivariateRegression()
# # training the model by using the training inputs and known training outputs
# regressor.fit(trainInputs, trainOutputs)
# # save the model parameters
# w0, w1 = regressor.intercept_, regressor.coef_
# print('the learnt model: f(x) = ', w0, ' + ', w1, ' * x')

# plot the model
noOfPoints = 1000
xref = []
val = min(trainInputs)
step = (max(trainInputs) - min(trainInputs)) / noOfPoints
for i in range(1, noOfPoints):
    xref.append(val)
    val += step
yref = [w0 + w1 * el for el in xref]
plotData(trainInputs, trainOutputs, xref, yref, [], [], title="train data and model")

# makes predictions for test data
# computedTestOutputs = [w0 + w1 * el for el in testInputs]
# makes predictions for test data (by tool)
computedValidationOutputs = regressor.predict([[x] for x in validationInputs])
plotData([], [], validationInputs, computedValidationOutputs, validationInputs, validationOutputs,
         "predictions vs real test data")

# compute the differences between the predictions and real outputs
error = 0.0
for t1, t2 in zip(computedValidationOutputs, validationOutputs):
    error += (t1 - t2) ** 2
error = error / len(validationOutputs)
print("prediction error (manual): ", error)

# by using sklearn
from sklearn.metrics import mean_squared_error

error = mean_squared_error(validationOutputs, computedValidationOutputs)
print("prediction error (tool): ", error)
