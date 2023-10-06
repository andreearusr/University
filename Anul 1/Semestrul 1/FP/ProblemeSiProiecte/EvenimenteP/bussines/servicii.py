from erori.exceptii import ValidError
from domeniu.entitati import Persoana, Eveniment,InscrDTO,InscriereDTO,ParticipantDTO,EvenimenteDTO
class ServicePersoana(object):
    '''
    Tip de data abstract
    Domeniu: actiunile ce pot fi facute asupra unei persoane
    '''

    
    def __init__(self, validator_persoana, repo_persoana):
        '''
        Initializeaza Service Persoana: validator_persoana - ValidatorPersoana repo_persoana -RepositoryPersoana
        :param validator_persoana - un validator
        :param repo_persoana - un repository
        '''
        self.__validator_persoana = validator_persoana
        self.__repo_persoana = repo_persoana
    
    def adauga_persoana(self,id_persoana,nume,adresa):
        '''
        functie care adauga o persoana in lista
        date de intrare: id_persoana - int
                         nume - string
                         adresa: strada-string  numar-int   oras-string
        date de iesire: - 
        :param id_persoana - un id
        :param nume - un nume
        :param adresa - o adresa
        '''
        persoana = Persoana(id_persoana,nume,adresa)
        self.__validator_persoana.valideaza_pers(persoana)
        self.__repo_persoana.adauga(persoana)
        
    def get_persoane(self):
        '''
        functie care returneaza toate persoanele ce sunt in lista
        '''
        return self.__repo_persoana.get_all()
    
    def cauta_persoana(self,id_persoana):
        '''
        functie care cauta o persoana din lista dupa un id_persoana
        date de intrare: id_persoana - int
        date de iesire: persoana - persoana cautata
        exceptii de tipul ValidError: daca id_persoana<1    Id invalid!\n
        :param id_persoana - un id
        '''
        if id_persoana<0:
            raise ValidError("Id invalid!\n")
        return self.__repo_persoana.cauta_dupa_id(id_persoana)
        
    def modifica_persoana(self,persoana_noua):
        '''
        functie care modifica elementele componente ale unei persoane in altele noi
        date de intrare: persoana - id_persoana - int
                                    nume_nou - string
                                    adresa_noua: strada - string
                                                 numar - int
                                                 oras - string
        date de iesire: - 
        exceptii de tipul ValidError: daca nume_nou=""      Nume invalid!\n
                                           strada=""        Strada invalida!\n
                                           numar<1          Numar invalid!\n
                                           oras=""          Oras invalid!\n
        :param persoana - o persoana
        '''
        
        self.__validator_persoana.valideaza_pers(persoana_noua)
        self.__repo_persoana.modifica(persoana_noua)
    

class ServiceEveniment(object):
    '''
    Tip de data abstract
    Domeniu: actiunile ce pot fi facute asupra unui eveniment
    '''
    
    
    def __init__(self, validator_eveniment, repo_eveniment):
        '''
        Initializeaza Service Eveniment: validator_eveniment - ValidatorEveniment  repo_eveniment - RepositoryEveniment
        :param validator_eveniment - un validator
        :param repo_eveniment - un repository
        '''
        self.__validator_eveniment = validator_eveniment
        self.__repo_eveniment = repo_eveniment
    
    def adauga_eveniment(self, id_eveniment, data_eveniment, timp_eveniment, descriere_even):
        '''
        functie care adauga un eveniment in lista
        date de intrare: id_eveniment - int
                         data_eveniment - int
                         timp_eveniment - float
                         descriere_even - string
        date de iesire: - 
        :param id_eveniment - un id
        :param data_eveniment - o data
        :param timp_eveniment - un timp/durata
        :param descriere_even - o descriere
        '''
        eveniment = Eveniment(id_eveniment,data_eveniment,timp_eveniment,descriere_even)
        self.__validator_eveniment.valideaza_even(eveniment)
        self.__repo_eveniment.adauga(eveniment)
        
    def get_evenimente(self):
        '''
        functie care returneaza toate evenimentele care sunt in lista
        '''
        return self.__repo_eveniment.get_all()
    
    def modifica_eveniment(self,eveniment):
        '''
        functie care modifica elementele componente ale unui eveniment in altele noi
        date de intrare: eveniment: id_eveniment - int
                                    data_eveniment - int
                                    timp_eveniment - float
                                    descriere_even - string
        date de iesire: -
        exceptii de tipul ValidError: daca data_eveniment<1 sau >31      Data invalida!\n
                                           timp_eveniment<0              Timp invalid!\n
                                           descriere_even=""             Descriere invalida!\n
        :param eveniment - un eveniment
        '''
        self.__validator_eveniment.valideaza_even(eveniment)
        self.__repo_eveniment.modifica(eveniment)
            
    def cauta_eveniment(self,id_eveniment):
        '''
        functie care cauta un eveniment din lista dupa un id_eveniment
        date de intrare: id_eveniment - int
        date de iesire: eveniment - evenimentul cautat
        exceptii de tipul ValidError: daca id_eveniment<1    Id invalid!\n
        :param id_eveniment - un id
        '''
        if id_eveniment<1:
            raise ValidError("Id invalid!\n")
        return self.__repo_eveniment.cauta_dupa_id(id_eveniment)
        
    

class ServiceInscriere(object):
    '''
    Tip de data abstract
    Domeniu: actiunile ce pot fi facute in scopul inscrierii/ stergerii persoanei la un eveniment
    '''
    
    
    def __init__(self, validator_inscriere, repo_inscriere, repo_persoana, repo_eveniment):
        '''
        Initializeaza Service Inscriere
        :param validator_inscriere - un validator
        :param repo_inscriere - un repository inscriere
        :param repo_persoana - un repository persoana
        :param repo_eveniment - un repository eveniment
        '''
        self.__validator_inscriere = validator_inscriere
        self.__repo_inscriere = repo_inscriere
        self.__repo_persoana = repo_persoana
        self.__repo_eveniment = repo_eveniment
    
    def adauga_inscriere(self,id_inscriere,id_persoana,id_eveniment,pret):
        '''
        functie care adauga o inscriere
        date de intrare: id_inscriere - int
                         id_persoana - int
                         id_eveniment - int
                         pret_inscriere - float
        date de iesire - 
        :param id_inscriere - un id inscriere
        :param id_persoana - un id persoana
        :param id_eveniment - un id eveniment
        :param pret_inscriere - un pret eveniment
        '''
        inscriere = InscrDTO(id_inscriere,id_persoana,id_eveniment,pret)
        self.__validator_inscriere.valideaza_inscriere(inscriere)
        self.__repo_inscriere.adauga(inscriere)
        
    def get_inscrieri(self):
        '''
        functie care returneaza toate inscrierile care sunt in lista
        '''
        inscrieri = self.__repo_inscriere.get_all()
        inscrieri_dtos = []
        for inscriere in inscrieri:
            id_inscriere = inscriere.get_id_inscriere()
            
            id_persoana = inscriere.get_id_persoana()
            persoana = self.__repo_persoana.cauta_dupa_id(id_persoana)
            nume = persoana.get_nume()
            
            id_eveniment = inscriere.get_id_eveniment()
            ev = self.__repo_eveniment.cauta_dupa_id(id_eveniment)
            descriere_even = ev.get_descriere_even()
            pret = inscriere.get_pret()
            
            inscriere_dto = InscriereDTO(id_inscriere,nume,descriere_even,pret)
            inscrieri_dtos.append(inscriere_dto)
        return inscrieri_dtos
        
    def ordonare_lista_evenimente_persoana(self,id_persoana):
        '''
        functie care ordoneaza evenimentele la care participa o persoana dupa descriere(alfabetic), dupa data
        date de intrare: id_persoana - int
        date de iesire: lista - lista de evenimente ordonata
        :param id_persoana - int, un id persoana
        '''
        lista=[]
        self.__repo_persoana.cauta_dupa_id(id_persoana)
        inscrieri = self.__repo_inscriere.get_all()
        for inscriere in inscrieri:
            if inscriere.get_id_persoana()==id_persoana:
                id_eveniment = inscriere.get_id_eveniment()
                ev = self.__repo_eveniment.cauta_dupa_id(id_eveniment)
                lista.append(ev)
                
        lista.sort(key=lambda ev:(ev.get_descriere_even(),ev.get_data_eveniment()))
        return lista
               
#    def persoane_evenimente(self,id_persoana):
#        nr_evenimente=0
#        self.__repo_persoana.cauta_dupa_id(id_persoana)
#        inscrieri = self.__repo_inscriere.get_all()
#        for inscriere in inscrieri:
#            if inscriere.get_persoana().get_id_persoana()==id_persoana:
#                id_eveniment = inscriere.get_eveniment().get_id_eveniment()
#                self.__repo_eveniment.cauta_dupa_id(id_eveniment)
#                nr_evenimente +=1
#        return nr_evenimente
            
    def persoane_multe_evenimente(self):
        '''
        functie care intocmeste o lista de persoane(id,nume), impreuna cu un numar de evenimente la care participa,
            returnand in final doar acele persoane ce participa la cele mai multe evenimente
        date de intrare: - 
        date de iesire: rezultat - lista de persoane participante la cele mai multe evenimente
        '''
        persoane = []
        lista_nr=[]
        id_uri=[]
        inscrieri = self.__repo_inscriere.get_all()
        for inscriere in inscrieri:  
            id_persoana = inscriere.get_id_persoana()
            if id_uri.count(id_persoana)==0:
                id_uri.append(id_persoana)
                persoana = self.__repo_persoana.cauta_dupa_id((id_persoana))
                nume = persoana.get_nume()
                
                nr_evenimente  = len(self.ordonare_lista_evenimente_persoana(id_persoana))
                lista_nr.append(nr_evenimente)
                persoane.append(ParticipantDTO(id_persoana,nume,nr_evenimente))
        
        rezultat=[]
        for i in range(0,len(persoane)):
            if persoane[i].get_nr_evenimente()==max(lista_nr):
                rezultat.append(persoane[i])
      
        return rezultat
    
    def evenimente_nr_participanti(self,a,b):
        '''
        functie care realizeaza o lista cu evenimentele ce au un numar de participanti cuprinse 
                            intre a si b (cele 2 valori introduse de catre utilizator)
        date de intrare: a- int, prima valoare introdusa
                         b - int, a doua valoare introdusa
        date de iesire: rezultat - lista de evenimente cu numarul de participanti intre a si b
        
        :param a - int, prima valoare
        :param b - int, a doua valoare
        '''
        rezultat=[]
        id_uri = []
        inscrieri = self.__repo_inscriere.get_all()
        for inscriere in inscrieri:
            id_eveniment = inscriere.get_id_eveniment()
            if id_uri.count(id_eveniment)==0:
                id_uri.append(id_eveniment)
                nr_persoane = self.evenimente_participanti(id_eveniment)
                if nr_persoane in range(a,b):
                    rezultat.append(self.__repo_eveniment.cauta_dupa_id(id_eveniment))  
        return rezultat
    
    def evenimente_participanti(self,id_eveniment):
        '''
        functie ce calculeaza numarul de participanti pe care il are un eveniment
        date de intrare: id_eveniment - int
        date de iesire: nr_persoane - numarul de participanti la acel eveniment
        :param id_eveniment-int pozitiv, un id
        '''
        lista=[] 
        self.__repo_eveniment.cauta_dupa_id(id_eveniment) 
        inscrieri = self.__repo_inscriere.get_all()
        for inscriere in inscrieri:
            if inscriere.get_id_eveniment()==id_eveniment:
                id_persoana = inscriere.get_id_persoana()
                persoana = self.__repo_persoana.cauta_dupa_id(id_persoana)
                lista.append(persoana)
            else:
                continue 
            
        nr_persoane=len(lista)
        return nr_persoane 
    
    def evenimente_multi_participanti(self):
        '''
        functie ce intocmeste o lista de evenimente(id_eveniment,descriere_even,nr_participanti), o ordoneaza in ordine
            descrescatoare dupa numarul de participanti si apoi afla primele 20% evenimente cu cei mai multi participanti
        date de intrare: - 
        date de iesire: lista cu primele 20% evenimente cu cei mai multi participanti
        '''
        evenimente=[]
        id_ev = []
        inscrieri = self.__repo_inscriere.get_all()
        for inscriere in inscrieri:
            id_eveniment = inscriere.get_id_eveniment()
            if id_ev.count(id_eveniment)==0:
                id_ev.append(id_eveniment)
                nr_participanti = self.evenimente_participanti(id_eveniment)
                
                ev = self.__repo_eveniment.cauta_dupa_id(id_eveniment)
                descriere_even = ev.get_descriere_even()
                
                even = EvenimenteDTO(id_eveniment,descriere_even,nr_participanti)
                evenimente.append(even)

        evenimente.sort(key=lambda ev:ev.get_nr_participanti(), reverse = True)
        rezultat = []
        a = int(0.2*len(evenimente))
        for i in range(0,a):
            rezultat.append(evenimente[i])
        return rezultat     
        
            
    def sterge_persoana_inscriere(self,id_persoana):
        '''
        functie care sterge o persoana din lista dupa un id_persoana si sterge si inscrierile acesteia la evenimente
        date de intrare: id_persoana - int
        date de iesire:-
        :param id_persoana - un id
        '''
        inscrieri = self.__repo_inscriere.get_all()
        for inscriere in inscrieri:
            if inscriere.get_id_persoana()==id_persoana:
                self.__repo_inscriere.sterge_inscriere_dupa_id(inscriere.get_id_inscriere())
        self.__repo_persoana.sterge_dupa_id(id_persoana)
        
    def sterge_eveniment(self,id_eveniment):
        '''
        functie care sterge un eveniment din lista dupa un id_eveniment si sterge si inscrierile la acel eveniment
        date de intrare: id_eveniment - int
        date de iesire:-
        :param id_eveniment - un id
        '''
        inscrieri = self.__repo_inscriere.get_all()
        for inscriere in inscrieri:
            if inscriere.get_id_eveniment()==id_eveniment:
                self.__repo_inscriere.sterge_inscriere_dupa_id(inscriere.get_id_inscriere())
        self.__repo_eveniment.sterge_dupa_id(id_eveniment)

        
    

