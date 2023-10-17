
def readfileErrorPrediction(filename):
    realOutputs = []
    computedOutputs = []

    with open(filename) as f:
        for line in f.readlines():
            outputs = line.split(",")
            realOutputs.append([float(outputs[0]), float(outputs[1]), float(outputs[2])])
            computedOutputs.append([float(outputs[3]), float(outputs[4]), float(outputs[5])])

    return realOutputs, computedOutputs


def readfileEvalMultiClass(filename):
    realLabels = []
    computedLabels = []

    with open(filename) as f:
        for line in f.readlines():
            labels = line.split(",")
            realLabels.append(labels[0])

            var = labels[1][0:len(labels[1]) - 1]
            computedLabels.append(var)

    return realLabels, computedLabels

