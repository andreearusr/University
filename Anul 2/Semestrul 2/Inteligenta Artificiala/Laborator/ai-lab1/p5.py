def pr5(lista):
    """

    :param lista: sir cu n elemente din {1,..,n-1}, o singura valoare se repeta de doua ori
    :return: valoarea care se repeta de 2 ori
    """
    d = dict()

    for number in lista:
        if number not in d.keys():
            d[number] = 1
        else:
            d[number] += 1
            return number
