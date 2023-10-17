def pr3(v1, v2):
    """

    :param v1: vectorul 1
    :param v2: vectorul 2
    :return: produsul scalar a celor 2 vectori rari
    """
    P = 0

    n = len(v1)
    m = len(v1[0])

    for i in range(n):
        for j in range(m):
            P = P + v1[i][j] * v2[i][j]

    return P
