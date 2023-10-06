from erori.exceptii import ValidError
class ValidatorPersoana(object):
    '''
    Tip de data abstract
    Domeniu: Validare persoana introdusa: un id_persoana - intreg, pozitiv,>1
                                          un nume - string, care sa nu fie gol
                                          o adresa: Strada - string, care sa nu fie gol
                                                    Numar - intreg, pozitiv,>1
                                                    Oras - string, care sa nu fie gol
    '''
    
    
    def __init__(self):
        pass
    
    def valideaza_pers(self, persoana):
        '''
        functie care valideaza datele introduse de catre utilizator
        date de intrare: persoana( id_persoana - int, nume - string, adresa - string)
        date de iesire: - 
        exceptii de tipul ValidError: daca id_persoana<1:   Id invalid!\n
                                           nume="":         Nume invalid!\n
                                           adresa: Strada="":       Strada invalida!\n
                                                   Numar<1:         Numar invalid!\n
                                                   Oras="":         Oras invalid!\n
        :param persoana- o persoana
        '''
        erori=""
        if persoana.get_id_persoana()<1:
            erori+="Id invalid!\n"
        if persoana.get_nume()=="":
            erori+="Nume invalid!\n"
        if persoana.get_adresa().get_strada()=="":
            erori+="Strada invalida!\n"
        if persoana.get_adresa().get_numar()<1:
            erori+="Numar strada invalid!\n"
        if persoana.get_adresa().get_oras()=="":
            erori+="Oras invalid!\n"
            
        if len(erori)>0:
            raise ValidError(erori)


class ValidatorEveniment(object):
    '''
    Tip de data abstract
    Domeniu: Validare eveniment introdus: un id_eveniment - intreg, pozitiv>1
                                          o data_eveniment - intreg, cuprins intre [1,31]
                                          un timp_eveniment - rational, pozitiv
                                          o descriere - string, care sa nu fie goala
    '''
    
    
    def __init__(self):
        pass
    
    def valideaza_even(self,eveniment):
        '''
        functie care valideaza datele introduse de catre utilizator
        date de intrare: un eveniment (id_eveniment - int, data_eveniment - int, timp_eveniment - float, descriere_even - string)
        date de iesire: - 
        exceptii de tipul ValidError: daca id_eveniment<1:                             Id invalid!\n
                                           data_eveniment<1 sau data_eveniment>31:     Data invalida!\n
                                           timp_eveniment<0:                           Timp invalid!\n
                                           descriere_even="":                          Descriere invalida!\n
        :param eveniment - un eveniment
        '''
        erori=""
        if eveniment.get_id_eveniment()<1:
            erori+="Id invalid!\n"
        if eveniment.get_data_eveniment()<1 or eveniment.get_data_eveniment()>31:
            erori+="Data invalida!\n"
        if eveniment.get_timp_eveniment()<0:
            erori+="Timp invalid!\n"
        if eveniment.get_descriere_even()=="":
            erori+="Descriere invalida!\n"
            
        if len(erori)>0:
            raise ValidError(erori)
    


class ValidatorInscriere(object):
    '''
    Tip de data abstract
    Domeniu: Validare inscriere introdusa: un id_inscriere - intreg, pozitiv,>1
                                          un pret - float, pozitiv
    '''
    
    
    def __init__(self):
        pass
    
    def valideaza_inscriere(self,inscriere):
        
        '''
        functie care valideaza datele introduse de catre utilizator
        date de intrare: o inscriere (id_inscriere - int, pret_inscriere - float)
        date de iesire: - 
        exceptii de tipul ValidError: daca id_inscriere<1:               Id invalid!\n
                                           pret_inscriere<0:             Pret invalid!\n

        :param eveniment - un eveniment
        '''
        erori=""
        if inscriere.get_id_inscriere()<1:
            erori+="Id invalid!\n"
        if inscriere.get_pret()<0:
            erori+="Pret invalid!\n"
            
        if len(erori)>0:
            raise ValidError(erori)
        
        
        
        




