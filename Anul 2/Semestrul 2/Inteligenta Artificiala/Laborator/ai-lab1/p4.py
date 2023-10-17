def pr4(text):
    """

    :param text: un text ce contine cuvinte separate prin spatiu
    :return: cuvintele care apar o singura data in text
    """
    d = dict()
    l = []

    for word in text.split(' '):
        if word not in d.keys():
            d[word] = 1
        else:
            d[word] += 1

    for key, val in d.items():
        if val == 1:
            l.append(key)

    return l
