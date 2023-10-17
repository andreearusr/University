def pr6(lista):
    """

    :param lista: sir cu n numere intregi, contine duplicate
    :return: elementul majoritar (care apare de mai mult de n/2 ori)
             -100000000 daca nu avem element majoritar
    """
    d = dict()
    maxA = -100000000
    max = -100000000

    for number in lista:
        if number not in d.keys():
            d[number] = 1
        else:
            d[number] += 1
            if maxA < d[number]:
                maxA = d[number]
                max = number

    if maxA > len(lista) / 2:
        return max
    return -100000000
