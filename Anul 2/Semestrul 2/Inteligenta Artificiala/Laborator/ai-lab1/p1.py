def pr1(text):
    """

    :param text: text ce contine cuvinte separate prin spatiu
    :return: returneaza ultimul cuvant dpdv alfabetic
    """
    stringMax = ' '
    for word in text.split(' '):
        if word > stringMax:
            stringMax = word

    return stringMax
