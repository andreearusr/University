class MyLinearRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = []

    def fit(self, x, y):
        sx2 = 0
        for i in range(len(x)):
            sx2 += x[i][1] * x[i][1]

        sx1y = 0
        for i in range(len(x)):
            sx1y += x[i][0] * y[i]

        sx1x2 = 0
        for i in range(len(x)):
            sx1x2 += x[i][0] * x[i][1]

        sx2y = 0
        for i in range(len(x)):
            sx2y += x[i][1] * y[i]

        sx1 = 0
        for i in range(len(x)):
            sx1 += x[i][0] * x[i][0]

        w1 = (sx2 * sx1y - sx1x2 * sx2y) / (sx1 * sx2 - sx1x2 * sx1x2)
        w2 = (sx1 * sx2y - sx1x2 * sx1y) / (sx1 * sx2 - sx1x2 * sx1x2)

        sx1_1 = 0
        for i in range(len(x)):
            sx1_1 += x[i][0]

        sx2_1 = 0
        for i in range(len(x)):
            sx2_1 += x[i][1]

        sy = 0
        for i in range(len(y)):
            sy += y[i]

        w0 = sy / len(y) - w1 * (sx1_1 / len(x)) - w2 * (sx2_1 / len(x))
        self.intercept_ = w0
        self.coef_.append(w1)
        self.coef_.append(w2)

    # predict the outputs for some new inputs (by using the learnt model)
    def predict(self, x):
        return [self.intercept_ + self.coef_[0] * val[0] + self.coef_[1] * val[1] for val in x]


class MyLinearUnivariateRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = 0.0
    # learn a linear univariate regression model by using training inputs (x) and outputs (y)
    def fit(self, x, y):
        sx = sum(x)
        sy = sum(y)
        sx2 = sum(i * i for i in x)
        sxy = sum(i * j for (i,j) in zip(x, y))
        w1 = (len(x) * sxy - sx * sy) / (len(x) * sx2 - sx * sx)
        w0 = (sy - w1 * sx) / len(x)
        self.intercept_, self.coef_ =  w0, w1
    # predict the outputs for some new inputs (by using the learnt model)
    def predict(self, x):
        if (isinstance(x[0], list)):
            return [self.intercept_ + self.coef_ * val[0] for val in x]
        else:
            return [self.intercept_ + self.coef_ * val for val in x]