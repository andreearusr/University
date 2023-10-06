class Opera(object):
    '''
    Tip de date abstract
    Domeniu: opere (id_opera- int, titlu-string, gen-string, pret-float)
    '''
    
    
    def __init__(self, id_opera, titlu, gen, pret):
        '''
        Initializeaza o opera
        :param id_opera -int
        :param titlu - string
        :param gen - string
        :param pret - float
        '''
        self.__id_opera = id_opera
        self.__titlu = titlu
        self.__gen = gen
        self.__pret = pret

    def get_id_opera(self):
        return self.__id_opera


    def get_titlu(self):
        return self.__titlu


    def get_gen(self):
        return self.__gen


    def get_pret(self):
        return self.__pret

    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza o opera:
                id opera:  titlu:  gen:  pret:  
        '''
        return "id opera:"+str(self.__id_opera)+"  titlu:"+self.__titlu+"  gen:"+self.__gen+"  pret:"+str(self.__pret)


class PiesaDTO(object):
    '''
    Tip de date abstract
    Domeniu: o opera ce are si un pret total/nr bilete cumparate
    '''
    
    def __init__(self,opera,suma):
        '''
        Initializeaza o piesa
        :param opera - opera la care se doreste cumpararea de bilete
        :param suma - int
        '''
        self.__opera = opera
        self.__suma = suma

    def get_opera(self):
        return self.__opera


    def get_suma(self):
        return self.__suma

    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza o cumparare de bilete:
                opera:  pretul total bilete:
        '''
        return "opera:"+str(self.__opera)+"  pret total bilete:"+str(self.__suma)





