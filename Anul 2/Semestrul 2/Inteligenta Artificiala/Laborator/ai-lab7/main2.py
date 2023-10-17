import csv
import os

from matplotlib import pyplot as plt

from myRegression import MyLinearRegression


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
    selectedOutput = dataNames.index(outputVariabName)
    oldData = data

    for i in range(len(data) - 1, -1, -1):
        if data[i][selectedVariable1] == '':
            data.remove(data[i])
        elif data[i][selectedVariable2] == '':
            data.remove(data[i])

    a_1 = makeAprox(data, selectedOutput, selectedVariable1)
    a_2 = makeAprox(data, selectedOutput, selectedVariable2)

    for i in range(len(oldData)):
        if oldData[i][selectedVariable1] == '' and oldData[i][selectedVariable2] == '':
            oldData[i][selectedVariable1] = str(float(oldData[i][outputVariabName]) / a_1)
            oldData[i][selectedVariable2] = str(float(oldData[i][outputVariabName]) / a_2)
        elif oldData[i][selectedVariable1] == '':
            oldData[i][selectedVariable1] = str(float(oldData[i][outputVariabName]) / a_1)
        elif oldData[i][selectedVariable1] == '':
            oldData[i][selectedVariable2] = str(float(oldData[i][outputVariabName]) / a_2)

    inputs = [[float(oldData[i][selectedVariable1]), float(oldData[i][selectedVariable2])] for i in range(len(oldData))]
    outputs = [float(oldData[i][selectedOutput]) for i in range(len(oldData))]

    return inputs, outputs


def plot3Ddata(x1Train, x2Train, yTrain, x1Model=None, x2Model=None, yModel=None, x1Test=None, x2Test=None, yTest=None,
               title=None):
    ax = plt.axes(projection='3d')
    if (x1Train):
        plt.scatter(x1Train, x2Train, yTrain, c='r', marker='o', label='train data')
    if (x1Model):
        plt.scatter(x1Model, x2Model, yModel, c='b', marker='*', label='learnt model')
    if (x1Test):
        plt.scatter(x1Test, x2Test, yTest, c='g', marker='^', label='test data')
    plt.title(title)
    ax.set_xlabel("capita")
    ax.set_ylabel("freedom")
    ax.set_zlabel("happiness")
    plt.legend()
    plt.show()


# problem hapiness = w0 + w1 * GDPcapita + w2 * freedom
# load data
crtDir = os.getcwd()
filePath = os.path.join(crtDir, 'v1_world-happiness-report-2017.csv')

inputs, outputs = loadDataMoreInputs(filePath, ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score')

feature1 = [ex[0] for ex in inputs]
feature2 = [ex[1] for ex in inputs]


# see how the data looks (plot the histograms associated to input data - GDP feature  + Freedom - and output data - happiness)
def plotDataHistogram(x, variableName):
    n, bins, patches = plt.hist(x, 10)
    plt.title('Histogram of ' + variableName)
    plt.show()


# plot the data histograms
#plotDataHistogram(feature1, 'capita GDP')
#plotDataHistogram(feature2, 'Freedom')
#plotDataHistogram(outputs, 'Happiness score')

# check the liniarity (to check that a linear relationship exists between the dependent variable (y = happiness) and the independent variables (x1 = capita, x2 = freedom).)
#plot3Ddata(feature1, feature2, outputs, [], [], [], [], [], [], 'capita vs freedom vs happiness')

import numpy as np
from sklearn import linear_model

np.random.seed(5)
indexes = [i for i in range(len(inputs))]
trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
testSample = [i for i in indexes if not i in trainSample]

trainInputs = [inputs[i] for i in trainSample]
trainOutputs = [outputs[i] for i in trainSample]
testInputs = [inputs[i] for i in testSample]
testOutputs = [outputs[i] for i in testSample]

feature1train = [ex[0] for ex in trainInputs]
feature2train = [ex[1] for ex in trainInputs]

feature1test = [ex[0] for ex in testInputs]
feature2test = [ex[1] for ex in testInputs]

#plot3Ddata(feature1train, feature2train, trainOutputs, [], [], [], feature1test, feature2test, testOutputs,
#          "train and test data")


#  http://faculty.cas.usf.edu/mbrannick/regression/Part3/Reg2.html
#regressor = MyLinearRegression()

regressor = linear_model.LinearRegression()
regressor.fit(trainInputs, trainOutputs)

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
