import numpy as np
from matplotlib import pyplot as plt


class LogisticRegressionOVR(object):
    def __init__(self, eta=0.1, n_iter=2000):
        self.eta = eta
        self.n_iter = n_iter

    def _cost_function(self, h, theta, y):
        m = len(y)
        cost = (1 / m) * (np.sum(-y.T.dot(np.log(h)) - (1 - y).T.dot(np.log(1 - h))))
        return cost

    def fit(self, X, y):
        X = np.insert(X, 0, 1, axis=1)  # se insereaza pe prima poz 0
        self.w = []
        self.cost = []
        m = X.shape[0]

        for i in np.unique(y):  # creeaza un array de class labels
            y_copy = np.where(y == i, 1, 0)  # pt fiecare label se face o copie, 1 si 0
            w = np.zeros(X.shape[1])
            cost = []

            for _ in range(self.n_iter):
                output = X.dot(w)
                errors = self._sigmoid(output) - y_copy
                w -= self.eta / m * errors.dot(X)
                cost.append(self._cost_function(self._sigmoid(output), w, y_copy))
            self.w.append((w, i))
            self.cost.append((cost, i))
        return self

    def _sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def eval(self, xi, coef):
        yi = coef[0]
        for j in range(len(xi)):
            yi += coef[j + 1] * xi[j]
        return yi

    def _predict_one(self, x):
        return max((x.dot(w), c) for w, c in self.w)[1]

    def predict(self, X):
        return [self._predict_one(i) for i in np.insert(X, 0, 1, axis=1)]

    def _plot_cost(self, costh):  # This function plot the Cost function value
        for cost, c in costh:
            plt.plot(range(len(cost)), cost, 'r')
            plt.title("type-" + str(c))
            plt.xlabel("Iterations")
            plt.ylabel("Cost")
            plt.show()

# https://kenzotakahashi.github.io/logistic-regression-from-scratch-in-python.html
# https://medium.com/analytics-vidhya/logistic-regression-from-scratch-multi-classification-with-onevsall-d5c2acf0c37c