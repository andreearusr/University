import math

from matplotlib import pyplot as plt

from utils import readfileErrorPrediction, readfileEvalMultiClass


def evalMultiTarget(realOutputs, computedOutputs):
    diff1 = []
    for realOut, computedOut in zip(realOutputs, computedOutputs):
        diff1.append([abs(r - c) for r, c in zip(realOut, computedOut)])
    for i in range(len(diff1)):
        diff1[i] = sum(diff1[i])
    errorL1 = sum(diff1) / len(realOutputs)

    diff = []
    for realOut, computedOut in zip(realOutputs, computedOutputs):
        diff.append([(r - c) ** 2 for r, c in zip(realOut, computedOut)])
    for i in range(len(diff)):
        diff[i] = sum(diff[i])
    errorL2 = math.sqrt(sum(diff)/len(realOutputs))

    #print(math.sqrt(sum([sum([(r - c) ** 2 for r, c in zip(realOut, computedOut)]) for realOut, computedOut in zip(realOutputs, computedOutputs)])/len(realOutputs)))
    return errorL1, errorL2


def evalMultiClassV1(realLabels, computedLabels, labelNames):
    acc = sum([1 if realLabels[i] == computedLabels[i] else 0 for i in range(0, len(realLabels))]) / len(realLabels)
    TP = {}
    FP = {}
    TN = {}
    FN = {}
    for label in labelNames:
        TP[label] = sum(
            [1 if (realLabels[i] == label and computedLabels[i] == label) else 0 for i in range(len(realLabels))])
        FP[label] = sum(
            [1 if (realLabels[i] != label and computedLabels[i] == label) else 0 for i in range(len(realLabels))])
        TN[label] = sum(
            [1 if (realLabels[i] != label and computedLabels[i] != label) else 0 for i in range(len(realLabels))])
        FN[label] = sum(
            [1 if (realLabels[i] == label and computedLabels[i] != label) else 0 for i in range(len(realLabels))])

    precision = {}
    recall = {}
    for label in labelNames:
        precision[label] = TP[label] / (TP[label] + FP[label])
        recall[label] = TP[label] / (TP[label] + FN[label])

    return acc, precision, recall


def evalMultiClassV2(realLabels, computedLabels, labelNames):
    confMatrix = [[0 for _ in labelNames] for _ in labelNames]
    for k in range(len(realLabels)):
        for i in range(len(labelNames)):
            for j in range(len(labelNames)):
                if (realLabels[k] == labelNames[i]) and (computedLabels[k] == labelNames[j]):
                    confMatrix[i][j] += 1
    acc = sum([confMatrix[i][i] for i in range(len(labelNames))]) / len(realLabels)
    precision = {}
    recall = {}
    for i in range(len(labelNames)):
        precision[labelNames[i]] = confMatrix[i][i] / sum([confMatrix[j][i] for j in range(len(labelNames))])
        recall[labelNames[i]] = confMatrix[i][i] / sum([confMatrix[i][j] for j in range(len(labelNames))])
    return acc, precision, recall


def main():
    realOutputs, computedOutputs = readfileErrorPrediction("sport.csv")
    print(realOutputs)
    print(computedOutputs)
    for i in range(len(realOutputs)):
        plt.plot(i, realOutputs[i][0], 'ro', label='real')
        plt.plot(i, realOutputs[i][1], 'yo', label='real')
        plt.plot(i, realOutputs[i][2], 'go', label='real')


    for i in range(len(computedOutputs)):
        plt.plot(i, computedOutputs[i][0], 'bo', label='computed')
        plt.plot(i, computedOutputs[i][1], 'co', label='computed')
        plt.plot(i, computedOutputs[i][2], 'mo', label='computed')

    plt.show()


    error1, error2 = evalMultiTarget(realOutputs, computedOutputs)
    print('Error (L1): ' + str(error1) + '\nError (L2): ' + str(error2))

    realLabels, computedLabels = readfileEvalMultiClass("flowers.csv")
    print(realLabels)
    print(computedLabels)

    indexes = [i for i in range(len(realLabels))]
    real, = plt.plot(indexes, realLabels, 'ro', label='real')
    computed, = plt.plot(indexes, computedLabels, 'bo', label='computed')
    plt.legend([real, (real, computed)], ["Real", "Computed"])
    plt.show()

    acc, prec, recall = evalMultiClassV1(realLabels, computedLabels, list(set(realLabels)))
    print('acc: ', acc, ' precision: ', prec, ' recall: ', recall)


main()
