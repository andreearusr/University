class Piesa(object):
    '''
    Tip de date abstract
    Domeniu: piese de teatru
    '''
    
    
    def __init__(self, titlu, regizor, gen, durata):
        '''
        Initializeaza o piesa de teatru
        :param titlu - string
        :param regizor - string
        :param gen - string
        :param durata - int
        '''
        self.__titlu = titlu
        self.__regizor = regizor
        self.__gen = gen
        self.__durata = durata

    def get_titlu(self):
        return self.__titlu


    def get_regizor(self):
        return self.__regizor


    def get_gen(self):
        return self.__gen


    def get_durata(self):
        return self.__durata


    def set_titlu(self, value):
        self.__titlu = value


    def set_regizor(self, value):
        self.__regizor = value


    def set_gen(self, value):
        self.__gen = value


    def set_durata(self, value):
        self.__durata = value

    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza o piesa
            Titlu:    Regizor:    Gen:    Durata:
        '''
        return "Titlu:"+self.__titlu+"  Regizor:"+self.__regizor+"  Gen:"+self.__gen+"  Durata:"+str(self.__durata)
    




