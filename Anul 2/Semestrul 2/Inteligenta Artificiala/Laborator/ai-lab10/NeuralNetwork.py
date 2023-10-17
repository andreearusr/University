import numpy as np


class NeuralNetwork:
    def __init__(self, x, y, h):
        self.input = x
        self.weights1 = np.random.randn(self.input.shape[1], h)
        self.weights2 = np.random.randn(h, 3)
        self.y = y
        self.output = np.zeros(y.shape)

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    def FeedForward(self):
        first_cross = np.dot(self.input, self.weights1)
        self.layer1 = self.sigmoid(first_cross)

        second_Cross = np.dot(self.layer1, self.weights2)
        self.output = self.sigmoid(second_Cross)

    def BackPropogation(self, lr):
        m = len(self.input)

        d_err = self.y - self.output
        d_weights2 = -(1 / m) * np.dot(self.layer1.T, d_err * self.sigmoid_derivative(self.output))

        d_weights1 = -(1 / m) * np.dot(self.input.T, (
                np.dot(d_err * self.sigmoid_derivative(self.output), self.weights2.T) * self.sigmoid_derivative(
            self.layer1)))

        self.weights2 = self.weights2 - lr * d_weights2
        self.weights1 = self.weights1 - lr * d_weights1

    def predict(self, X):
        self.layer_1 = self.sigmoid(np.dot(X, self.weights1))
        return self.sigmoid(np.dot(self.layer_1, self.weights2))

#https://towardsdatascience.com/the-ultimate-beginners-guide-to-implement-a-neural-network-from-scratch-cf7d52d91e00