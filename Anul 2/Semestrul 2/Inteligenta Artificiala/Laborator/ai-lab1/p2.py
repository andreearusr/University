import math


def pr2(x, y):
    """

    :param x: un punct
    :param y: al doilea punct
    :return: distanta Euclidiana dintre cele doua locatii
    """
    return math.sqrt(pow(x[0] - y[0], 2) + pow(x[1] - y[1], 2))
