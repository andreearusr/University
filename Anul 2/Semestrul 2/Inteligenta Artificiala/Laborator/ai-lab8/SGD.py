from matplotlib import pyplot as plt


class MySGDRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = []

    # grad function
    def grad(self, x, y, w):
        grad_w = 2 * x * ((w * x) - y)  # derevative with respect to x
        return grad_w

    # simple stochastic GD
    def fit(self, x, y, learningRate=0.001, noEpochs=3000):
        self.coef_ = [0.0 for _ in range(len(x[0]) + 1)]  # beta or w coefficients y = w0 + w1 * x1 + w2 * x2 + ...
        # self.coef_ = [random.random() for _ in range(len(x[0]) + 1)]    #beta or w coefficients
        list_x = []
        list_y = []

        for epoch in range(noEpochs):
            sum_err = 0
            crt = []
            S = 0
            # TBA: shuffle the trainind examples in order to prevent cycles
            for i in range(len(x)):  # for each sample from the training data
                ycomputed = self.eval(x[i])  # estimate the output
                crtError = ycomputed - y[i]  # compute the error for the current sample
                sum_err += crtError ** 2

            for i in range(len(x)):
                y_hat = self.eval(x[i])
                expr = y_hat - y[i]

                for j in range(0, len(x[0])):  # update the coefficients
                    self.coef_[j] -= learningRate * expr/len(x) * x[i][j]
                self.coef_[len(x[0])] -= learningRate * expr/len(x) * 1

            list_x.append(epoch)
            list_y.append(sum_err)

        plt.plot(list_x, list_y)
        plt.show()

        self.intercept_ = self.coef_[-1]
        self.coef_ = self.coef_[:-1]

    def eval(self, xi):
        yi = self.coef_[-1]
        for j in range(len(xi)):
            yi += self.coef_[j] * xi[j]
        return yi

    def predict(self, x):
        yComputed = [self.eval(xi) for xi in x]
        return yComputed
