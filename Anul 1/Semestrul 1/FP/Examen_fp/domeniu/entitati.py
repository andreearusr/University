class Melodie(object):
    '''
    Tip de date abstract
    Domeniu: melodii
    '''
    
    
    def __init__(self, titlu, artist, gen, durata):
        '''
        Initializeaza specificatiile unei melodii
        :param titlu - string
        :param artist - string
        :param gen - string 
        :param durata - intreg
        '''
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__durata = durata

    def get_titlu(self):
        return self.__titlu


    def get_artist(self):
        return self.__artist


    def get_gen(self):
        return self.__gen


    def get_durata(self):
        return self.__durata


    def set_titlu(self, value):
        self.__titlu = value


    def set_artist(self, value):
        self.__artist = value


    def set_gen(self, value):
        self.__gen = value


    def set_durata(self, value):
        self.__durata = value


    def __str__(self):
        '''
        Returneaza formatul in care se afiseaza o melodie:
                Titlu:     Artist:    Gen:    Durata:
        '''
        return "Titlu:"+self.__titlu+"  Artist:"+self.__artist+"  Gen:"+self.__gen+"  Durata:"+str(self.__durata)

class MelodieDTO(object):
    '''
    Tip de date abstract
    Domeniu: melodii_dto
    '''
    
    def __init__(self,artist,titlu,durata,gen):
        '''
        Initializeaza specificatiile unei melodii_dto
        :param artist - string
        :param titlu - string
        :param gen - string
        :param durata - intreg
        '''
        self.__artist = artist
        self.__titlu = titlu
        self.__durata = durata
        self.__gen = gen

    def get_artist(self):
        return self.__artist


    def get_titlu(self):
        return self.__titlu

    def get_durata(self):
        return self.__durata

    def get_gen(self):
        return self.__gen


