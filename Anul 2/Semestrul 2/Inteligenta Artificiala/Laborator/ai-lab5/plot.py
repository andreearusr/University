import operator

import matplotlib.pyplot as plt


def plot(points, path):
    x = []
    y = []
    for p in points:
        x.append(p[0])
        y.append(p[1])

    y = list(map(operator.sub, [max(y) for i in range(len(points))], y))
    plt.plot(x, y, 'co')

    for k in range(1, len(path)):
        i = path[k - 1]
        j = path[k]

        plt.arrow(x[i], y[i], x[j] - x[i], y[j] - y[i], color='r', length_includes_head=True)

    plt.xlim(0, max(x) * 1.1)
    plt.ylim(0, max(y) * 1.1)
    plt.show()
