def calculateSum(pair, lista):
    """

    :param pair: perechea cu coordonate din matrice
    :param lista: o matrice
    :return: suma sub-matricei identificata prin perechea pair
    """
    S = 0

    p = pair[0][0]
    q = pair[0][1]
    r = pair[1][0]
    s = pair[1][1]

    if p <= r:
        if q <= s:
            for i in range(p, r + 1):
                for j in range(q, s + 1):
                    S = S + lista[i][j]
        if q > s:
            for i in range(p, r + 1):
                for j in range(s, q + 1):
                    S = S + lista[i][j]
    else:
        if q < s:
            for i in range(r, p + 1):
                for j in range(q, s + 1):
                    S = S + lista[i][j]
        if q > s:
            for i in range(r, p + 1):
                for j in range(s, q + 1):
                    S = S + lista[i][j]

    return S


def pr9(lista, pairsList):
    """

    :param lista: o matrice
    :param pairsList: lista de perechi de coordonate din matrice
    :return: lista cu suma elementelor din sub-matricile identificate de fiecare pereche din pairsList
    """
    l = []

    for pair in pairsList:
        suma = calculateSum(pair, lista)
        l.append(suma)
    return l
