class Persoana(object):
    '''
    Tip de data abstract
    Domeniu: O persoana ce detine un id_persoana - int ,un nume si o adresa - string
    '''
    
    
    def __init__(self, id_persoana, nume, adresa):
        '''
        Initializeaza o persoana
        :param id_persoana - int
        :param nume - string
        :param adresa - string
        '''
        self.__id_persoana = id_persoana
        self.__nume = nume
        self.__adresa = adresa

    def get_id_persoana(self):
        '''
        functie care returneaza id-ul unei persoane
        '''
        return self.__id_persoana


    def get_nume(self):
        '''
        functie care returneaza numele unei persoane
        '''
        return self.__nume


    def get_adresa(self):
        '''
        functie care returneaza adresa unei persoane
        '''
        return self.__adresa


    def set_nume(self, value):
        '''
        functie care seteaza numele unei persoane la un alt nume
        :param value - string, un alt nume
        '''
        self.__nume = value


    def set_adresa(self, value):
        '''
        functie care seteaza adresa unei persoane la o alta adresa
        :param value - string, o alta adresa
        '''
        self.__adresa = value
        
    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza o persoana din lista:
                    (Id:   Nume:   Adresa: )
        '''
        return "Id:"+str(self.__id_persoana)+"  Nume:"+ self.__nume+"  Adresa:"+str(self.__adresa)

    def __eq__(self,other):
        '''
        functie care verifica daca 2 persoane au acelasi id, caz in care returneaza True
        :param other - int, o alta persoana
        '''
        return self.__id_persoana == other.__id_persoana
    
    
class Adresa:
    '''
    Tip de data abstract
    Domeniu: Adresa a unei persoane - strada-string, numar-intreg, oras-string
    '''
    
    def __init__(self,strada, numar, oras):
        '''
        Initializeaza o adresa
        :param strada - string
        :param numar - int
        :param oras - string
        '''
        self.__strada = strada
        self.__numar = numar
        self.__oras = oras

    def get_strada(self):
        '''
        functie care returneaza strada dintr-o adresa
        '''
        return self.__strada


    def get_numar(self):
        '''
        functie care returneaza numarul casei/blocului al unei strazi
        '''
        return self.__numar


    def get_oras(self):
        '''
        functie care returneaza orasul dintr-o adresa
        '''
        return self.__oras


    def set_strada(self, value):
        '''
        functie care seteaza strada unei adrese, la o alta strada
        :param value - string, o alta strada
        '''
        self.__strada = value


    def set_numar(self, value):
        '''
        functie care seteaza numarul casei/blocului la un alt numar
        :param value - int, alt numar de casa/bloc
        '''
        self.__numar = value


    def set_oras(self, value):
        '''
        functie care seteaza orasul din adresa la un alt oras
        :param value - string, alt oras
        '''
        self.__oras = value
    
    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza o adresa:
                            Strada:  Numar:  Oras
        '''
        return "Strada:"+self.__strada+"  Numar:"+str(self.__numar)+"  Oras:"+self.__oras

    


class Eveniment(object):
    '''
    Tip de data abstract
    Domeniu: Un eveniment ce detine un id_eveniment, o data_eveniment, un timp_eveniment - float si o descriere_even - string
    '''
    
    
    def __init__(self, id_eveniment, data_eveniment, timp_eveniment, descriere_even):
        '''
        Initializeaza un eveniment 
        :param id_eveniment int
        :param data_eveniment - int
        :param timp_eveniment - float
        :param descriere_even - string 
        '''
        self.__id_eveniment = id_eveniment
        self.__data_eveniment = data_eveniment
        self.__timp_eveniment = timp_eveniment
        self.__descriere_even = descriere_even

    def get_id_eveniment(self):
        '''
        functie care returneaza id-ul unui eveniment
        '''
        return self.__id_eveniment


    def get_data_eveniment(self):
        '''
        functie care returneaza data unui eveniment
        '''
        return self.__data_eveniment


    def get_timp_eveniment(self):
        '''
        functie care returneaza timpul(durata) unui eveniment
        '''
        return self.__timp_eveniment


    def get_descriere_even(self):
        '''
        functie care returneaza descrierea facuta evenimentului
        '''
        return self.__descriere_even


    def set_data_eveniment(self, value):
        '''
        functie care seteaza data unei persoane la o alta data
        :param value - int, o alta data
        '''
        self.__data_eveniment = value


    def set_timp_eveniment(self, value):
        '''
        functie care seteaza timpul/durata unui eveniment la o alta durata
        :param value - float, o alta durata
        '''
        self.__timp_eveniment = value


    def set_descriere_even(self, value):
        '''
        functie care seteaza descrierea evenimentului la o alta descriere
        :param value - string, alta descriere
        '''
        self.__descriere_even = value

    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza un eveniment din lista:
                        (Id:   Data:   Timp: h   Descriere:  )
        '''
        return "Id:"+str(self.__id_eveniment)+"  Data:"+str(self.__data_eveniment)+"  Durata:"+str(self.__timp_eveniment)+"h"+"  Descriere:"+self.__descriere_even

    def __eq__(self,other):
        '''
        functie care verifica daca doua evenimente au acelasi id, caz in care returneaza True
        :param other- int, alt eveniment
        '''
        return self.__id_eveniment==other.__id_eveniment
    

class InscriereDTO(object):
    '''
    Tip de data abstract
    Domeniu: O inscriere ce contine un id_inscriere - int ,un nume, o descriere_even - string, un pret - float
    
    '''
    
    
    def __init__(self, id_inscriere, nume, descriere_even, pret):
        '''
        Initializeaza o inscriereDTO
        :param id_inscriere - int
        :param nume - string
        :param descriere_even - string
        :param pret - float
        '''
        self.__id_inscriere = id_inscriere
        self.__nume = nume
        self.__descriere_even = descriere_even
        self.__pret = pret

    def get_id_inscriere(self):
        '''
        functie care returneaza id-ul unei inscrieriDTO
        '''
        return self.__id_inscriere


    def get_nume(self):
        '''
        functie care returneaza numele unei inscrieriDTO
        '''
        return self.__nume


    def get_descriere_even(self):
        '''
        functie care returneaza descrierea evenimentului unei inscrieriDTO
        '''
        return self.__descriere_even


    def get_pret(self):
        '''
        functie care returneaza pretul unei inscrieriDTO
        '''
        return self.__pret

        
    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza o inscriereDTO din lista:
                    (Id inscriere:  Nume: --> Descriere:  Pret: RON)
        '''
        return "Id inscriere:"+str(self.__id_inscriere)+"  Nume:"+self.__nume+" --> Descriere:"+self.__descriere_even+"  Pret bilet:"+str(self.__pret)+" RON"


class InscrDTO(object):
    '''
    Tip de data abstract
    Domeniu: O inscriere ce contine un id_inscriere - int , un id_persoana - int, un id_eveniment - int, un pret - float
    
    '''
    
    def __init__(self,id_inscriere,id_persoana,id_eveniment,pret):
        self.__id_inscriere = id_inscriere
        self.__id_persoana = id_persoana
        self.__id_eveniment = id_eveniment
        self.__pret = pret

    def get_id_inscriere(self):
        return self.__id_inscriere


    def get_id_persoana(self):
        return self.__id_persoana


    def get_id_eveniment(self):
        return self.__id_eveniment


    def get_pret(self):
        return self.__pret

    def __eq__(self,other):
        '''
        functie care verifica daca doua inscrieri au acelasi id, caz in care returneaza True
        :param other- int, alta inscriere
        '''
        return self.__id_inscriere==other.__id_inscriere
    
    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza o inscriereDTO din lista:
                    (Id inscriere:  Nume: --> Descriere:  Pret: RON)
        '''
        return "Id inscriere:"+str(self.__id_inscriere)+"  Id persoana:"+str(self.__id_persoana)+"  Id eveniment:"+str(self.__id_eveniment)+"  Pret bilet:"+str(self.__pret)+" RON"

        

class ParticipantDTO(object):
    '''
    Tip de data abstract
    Domeniu: Un participant, ce detine un id_persoana - int, un nume - string si un nr_evenimente - int,pozitiv
    '''
    
    def __init__(self,id_persoana,nume, nr_evenimente):
        '''
        Initializeaza un participantDTO
        :param id_persoana - int
        :param nume - string
        :param nr_evenimente - int
        '''
        self.__id_persoana = id_persoana
        self.__nr_evenimente = nr_evenimente
        self.__nume = nume

    def get_id_persoana(self):
        '''
        functie care returneaza id-ul persoanei participante
        '''
        return self.__id_persoana


    def get_nr_evenimente(self):
        '''
        functie care returneaza nr_evenimente la care participa o persoana
        '''
        return self.__nr_evenimente


    def get_nume(self):
        '''
        functie care returneaza numele persoanei participante
        '''
        return self.__nume
   
    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza un participantDTO din lista:
                    (Id persoana:  Nume:  Numar evenimente: )
        '''
        return "Id persoana:"+str(self.__id_persoana)+"  Nume:"+self.__nume+"  Numar evenimente:"+str(self.__nr_evenimente)

class EvenimenteDTO(object):
    '''
    Tip de data abstract
    Domeniu: Un eveniment, ce contine un id_eveniment - int, o descriere_even - string si un nr_participanti - int,pozitiv
    '''
    
    def __init__(self,id_eveniment, descriere_even, nr_participanti):
        '''
        Initializeaza un evenimentDTO
        :param id_eveniment - int
        :param descriere_even - string
        :param nr_participanti - int
        '''
        self.__descriere_even = descriere_even
        self.__nr_participanti = nr_participanti
        self.__id_eveniment = id_eveniment

    def get_descriere_even(self):
        '''
        functie care returneaza descrierea evenimentului
        '''
        return self.__descriere_even


    def get_nr_participanti(self):
        '''
        functie care returneaza numarul de participanti la eveniment
        '''
        return self.__nr_participanti
    
    def get_id_eveniment(self):
        '''
        functie care returneaza id-ul evenimentului
        '''
        return self.__id_eveniment


    def __str__(self):
        '''
        functie care returneaza formatul in care se afiseaza un evenimentDTO din lista:
                    (Descriere eveniment:  Numar participanti: )
        '''
        return "Descriere eveniment:"+self.__descriere_even+"  Numar participanti:"+str(self.__nr_participanti)

