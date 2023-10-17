def binary(number, l):
    """

    :param number: un numar natural
    :param l: lista cifrelor binare
    :return: lista cifrelor ale numarului in reprezentarea binara
    """
    while number >= 1:
        rest = number % 2
        l.append(rest)
        number = number // 2

    return l[::-1]  # start:stop:step
    # return list(reversed(l))


def pr8(n):
    """

    :param n: numar natural
    :return: lista cu cifrele din care sunt formate numerele cuprinse intre 1 si n
    """
    l = []

    for i in range(1, n + 1):
        number = binary(i, [])
        l.append(number)

    return l
