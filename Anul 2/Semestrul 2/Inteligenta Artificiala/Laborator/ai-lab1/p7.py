def pr7(lista, k):
    """

    :param lista: sir de numere
    :param k: intreg
    :return: al k-lea cel mai mare element
    """
    n = len(lista)
    for i in range(n - 1):
        for j in range(n - 1):
            if lista[j] > lista[j + 1]:
                temp = lista[j]
                lista[j] = lista[j + 1]
                lista[j + 1] = temp

    return lista[n - k]
