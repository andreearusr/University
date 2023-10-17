def pr10(lista):
    """

    :param lista: o matrice
    :return: indexul liniei ce contine cele mai multe elemente de 1
             0 daca nu exista linie cu componente 1
    """
    linie = -1
    Smax = 0
    n = len(lista)
    m = len(lista[0])

    for i in range(n):
        S = 0
        for j in range(m - 1, -1, -1):
            if lista[i][j] != 0:
                S += lista[i][j]
        if S > Smax:
            Smax = S
            linie = i

    return linie + 1
