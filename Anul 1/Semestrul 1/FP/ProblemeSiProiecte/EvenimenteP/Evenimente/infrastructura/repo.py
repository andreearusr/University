
from erori.exceptii import RepoError
from domeniu.entitati import Persoana,Eveniment,InscrDTO
class RepositoryPersoana(object):
    '''
    Tip de data abstract
    Domeniu: Lista de persoane
    '''
    
    
    def __init__(self):
        '''
        Initializeaza lista de persoane
        '''
        self._elems = []
        
    def __len__(self):
        '''
        functie care returneaza cate elemente are lista de persoane
        '''
        return len(self._elems)
    
    def adauga(self, persoana):
        '''
        functie ce adauga la lista de persoane, o alta persoana
        date de intrare: persoana - o persoana
        date de iesire: - 
        exceptii de tipul RepoError: daca persoana e in lista de persoane:    Persoana existenta!\n
        :param persoana - o persoana
        '''
        if persoana in self._elems:
            raise RepoError("Persoana existenta!\n")
        self._elems.append(persoana)
        
    def cauta_dupa_id(self, id_persoana):
        '''
        functie care cauta o persoana din lista de persoane dupa id_persoana
        date de intrare: id_persoana - int
        date de iesire: -
        exceptii de tipul RepoError: daca id_persoana nu e gasit:    Persoana inexistenta!\n
        :param id_persoana - int, pozitiv
        '''
        
        for el in self._elems:
            if el.get_id_persoana()==id_persoana:
                return el
        raise RepoError("Persoana inexistenta!\n")
    
    
    def modifica(self, persoana_noua):
        '''
        functie care modifica o persoana
        date de intrare: persoana_noua - o persoana
        date de iesire: -
        exceptii de tipul RepoError: daca persoana_noua nu e gasita in lista de persoane:   Persoana inexistenta!\n
        :param persoana_noua - o persoana
        '''
        
        persoana = self.cauta_dupa_id(persoana_noua.get_id_persoana());
       
        if persoana not in self._elems:
                raise RepoError("Persoana inexistenta!\n")
   

        '''
        for el in self._elems:
            if el.get_id_persoana()==persoana.get_id_persoana():
                el.set_nume(persoana_noua.get_nume());
                el.set_adresa(persoana_noua.get_adresa());
        '''       
    
        persoana.set_nume(persoana_noua.get_nume())
        persoana.set_adresa(persoana_noua.get_adresa())
        
        
    
    def get_all(self):
        '''
        functie care returneaza toate persoanele din lista de persoane
        '''
        return self._elems[:]
    
    def sterge_dupa_id(self, id_persoana):
        '''
        functie care sterge o persoana dupa id_persoana
        date de intrare: id_persoana - int
        date de iesire: -
        exceptii de tipul RepoError: daca id_persoana nu e gasit:   Persoana inexistenta!\n
        :param id_persoana - int,pozitiv
        '''
        
        for i in range(len(self._elems)):
            if self._elems[i].get_id_persoana()== id_persoana:
                del self._elems[i]
                return
        raise RepoError("Persoana inexistenta!\n")
        

class RepositoryEveniment(object):
    '''
    Tip de data abstract
    Domeniu: Lista de evenimente
    '''
    
    
    def __init__(self):
        '''
        Initializeaza lista de evenimente
        '''
        self._elems = []
        
    def __len__(self):
        '''
        functie care returneaza cate elemente are lista de evenimente
        '''
        return len(self._elems)
    
    def adauga(self, eveniment):
        '''
        functie ce adauga la lista de evenimente, un alt eveniment
        date de intrare: eveniment - un eveniment
        date de iesire: - 
        exceptii de tipul RepoError: daca evenimentul e in lista de evenimente:    Eveniment existent!\n
        :param eveniment - un eveniment
        '''
        if eveniment in self._elems:
            raise RepoError("Eveniment existent!\n")
        self._elems.append(eveniment)
    
    def cauta_dupa_id(self, id_eveniment):
        '''
        functie care cauta un eveniment  din lista de evenimente dupa id_eveniment
        date de intrare: id_eveniment - int
        date de iesire: -
        exceptii de tipul RepoError: daca id_eveniment nu e gasit:    Eveniment inexistent!\n
        :param id_eveniment - int, pozitiv
        '''
        for el in self._elems:
            if el.get_id_eveniment()==id_eveniment:
                return el
        raise RepoError( "Eveniment inexistent!\n")
    
    
    def modifica(self, eveniment):
        '''
        functie care modifica un eveniment
        date de intrare: eveniment_nou - un eveniment
        date de iesire: -
        exceptii de tipul RepoError: daca eveniment_nou nu e gasit in lista de evenimente:   Eveniment inexistent!\n
        :param eveniment_nou - un eveniment
        '''
#        if eveniment_nou not in self._elems:
#                raise RepoError("Eveniment inexistent!\n")
#        for i in range(len(self._elems)):
#            if self._elems[i]== eveniment_nou:
#                self._elems[i]= eveniment_nou
#                return

        eveniment_nou =self.cauta_dupa_id(eveniment.get_id_eveniment())
        eveniment_nou.set_data_eveniment(eveniment.get_data_eveniment())
        eveniment_nou.set_timp_eveniment(eveniment.get_timp_eveniment())
        eveniment_nou.set_descriere_even(eveniment.get_descriere_even())
            
    def get_all(self):
        '''
        functie care returneaza toate evenimentele din lista de evenimente
        '''
        return self._elems[:]
            
    def sterge_dupa_id(self, id_eveniment):
        '''
        functie care sterge un eveniment dupa id_eveniment
        date de intrare: id_eveniment - int
        date de iesire: -
        exceptii de tipul RepoError: daca id_eveniment nu e gasit:   Eveniment inexistent!\n
        :param id_eveniment - int,pozitiv
        '''
        for i in range(len(self._elems)):
            if self._elems[i].get_id_eveniment()== id_eveniment:
                del self._elems[i]
                return
        raise RepoError("Eveniment inexistent!\n")
        
    
    

class RepositoryInscriere(object):
    '''
    Tip de data abstract
    Domeniu: Lista de inscrieri
    '''
    
    
    def __init__(self):
        '''
        Initializeaza lista de inscrieri
        '''
        self._elems = []
        
    def __len__(self):
        '''
        functie care returneaza cate elemente are lista de inscrieri
        '''
        return len(self._elems)

    def adauga(self,inscriere):
        '''
        functie ce adauga la lista de inscrieri, o alta inscriere
        date de intrare: inscriere - o inscriere
        date de iesire: - 
        exceptii de tipul RepoError: daca inscrierea e in lista de inscrieri:    Inscriere existenta!\n
        :param inscriere - o inscriere
        '''
        if inscriere in self._elems:
            raise RepoError("Inscriere existenta!\n")
        self._elems.append(inscriere)

    def get_all(self):
        '''
        functie care returneaza toate inscrierile din lista de inscrieri
        '''
        return self._elems[:]  
    
    def cauta_dupa_id(self, id_inscriere):
        '''
        functie care cauta o inscriere  din lista de inscrieri dupa id_inscriere
        date de intrare: id_inscriere - int
        date de iesire: -
        exceptii de tipul RepoError: daca id_inscriere nu e gasit:    Inscriere inexistenta!\n
        :param id_eveniment - int, pozitiv
        '''
        
        for i in range(len(self._elems)):
            if self._elems[i].get_id_inscriere()==id_inscriere:
                return self._elems[i]
        raise RepoError("Inscriere inexistenta!\n")
#        for el in self._elems:
#            if el.get_id_inscriere()==id_inscriere:
#                return el
#        raise RepoError( "Inscriere inexistenta!\n")
        
    
    def sterge_inscriere_dupa_id(self,id_inscriere):
        '''
        functie care sterge o inscriere  dupa id_inscriere
        date de intrare: id_inscriere - int
        date de iesire: -
        exceptii de tipul RepoError: daca id_inscriere nu e gasit:   Inscriere inexistenta!\n
        :param id_eveniment - int,pozitiv
        '''
        for i in range(len(self._elems)):
            if self._elems[i].get_id_inscriere()==id_inscriere:
                del self._elems[i]
                return
        raise RepoError("Inscriere inexistenta!\n")
            


class FileRepoPersoana(RepositoryPersoana):
    '''
    Stocheaza/sterge/modifica/cauta persoane din fisier
    '''

    
    def __init__(self, txt):
        '''
        initializeaza repository-ul de persoane
        :param txt - string, fisierul unde sunt stocate persoanele
        '''
        self.__txt = txt
        RepositoryPersoana.__init__(self)
    

    def __citeste_tot_din_fisier(self):
        '''
        Incarca persoanele din fisier
        '''
        with open(self.__txt,"r") as f:
            self._elems = []
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(";")
                    persoana = Persoana(int(parts[0]),parts[1],parts[2])
                    self._elems.append(persoana)
    
    def __append_persoana_fisier(self,persoana):
        '''
        Stocheaza o persoana la sfarsitul fisierului.
        :param persoana - o persoana
        '''
        with open(self.__txt,"a") as f:
            f.write(str(persoana.get_id_persoana())+";"+persoana.get_nume()+";"+str(persoana.get_adresa())+"\n")
    
    def __scrie_tot_in_fisier(self):
        '''
        Stocheaza toate persoanele in fisier

        '''
        with open(self.__txt,"w") as f:
            for persoana in self._elems:
                f.write(str(persoana.get_id_persoana())+";"+persoana.get_nume()+";"+str(persoana.get_adresa())+"\n")
    
    
    def adauga(self, persoana):
        '''
        Adauga o persoana in fisier
        :param persoana - o persoana
        '''
        self.__citeste_tot_din_fisier()
        RepositoryPersoana.adauga(self, persoana)
        self.__append_persoana_fisier(persoana)
        
    def sterge_dupa_id(self, id_persoana):
        '''
        sterge o persoana din fisier dupa id-ul acesteia
        :param id_persoana - int
        '''
        self.__citeste_tot_din_fisier()
        RepositoryPersoana.sterge_dupa_id(self, id_persoana)
        self.__scrie_tot_in_fisier()
        
    def modifica(self, persoana):
        '''
        actualizeaza o persoana din fisier
        :param persoana - o persoana (id_persoana,nume,adresa)
        '''
        self.__citeste_tot_din_fisier()
        RepositoryPersoana.modifica(self, persoana)
        self.__scrie_tot_in_fisier()
         
    def cauta_dupa_id(self, id_persoana):
        '''
        Cauta o persoana dupa un id_persoana
        :param id_persoana - int, un id
        returneaza persoana cu id-ul dat
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryPersoana.cauta_dupa_id(self, id_persoana)
    
    def __len__(self):
        '''
        returneaza lungimea listei de persoane din fisier
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryPersoana.__len__(self)
    
    def get_all(self):
        '''
        returneaza toate persoanele din fisier
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryPersoana.get_all(self)

class FileRepoEveniment(RepositoryEveniment):
    '''
    Stocheaza/sterge/modifica/cauta evenimentele din fisier
    '''
    
    def __init__(self,txt):
        '''
        initializeaza repository-ul de evenimente
        :param txt - string, fisierul unde sunt stocate evenimentele
        '''
        self.__txt = txt
        RepositoryEveniment.__init__(self)
    
    def __citeste_tot_din_fisier(self):
        '''
        Incarca evenimentele din fisier
        '''
        with open(self.__txt,"r") as f:
            self._elems = []
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(";")
                    eveniment = Eveniment(int(parts[0]),int(parts[1]),float(parts[2]),parts[3])
                    self._elems.append(eveniment)
    
    def __append_eveniment_fisier(self,eveniment):
        '''
        Stocheaza un eveniment la sfarsitul fisierului.
        :param eveniment - un eveniment
        '''
        with open(self.__txt,"a") as f:
            f.write(str(eveniment.get_id_eveniment())+";"+str(eveniment.get_data_eveniment())+";"+str(eveniment.get_timp_eveniment())+";"+eveniment.get_descriere_even()+"\n")
    
    def __scrie_tot_in_fisier(self):
        '''
        Stocheaza toate evenimentele in fisier
        '''
        with open(self.__txt,"w") as f:
            for eveniment in self._elems:
                f.write(str(eveniment.get_id_eveniment())+";"+str(eveniment.get_data_eveniment())+";"+str(eveniment.get_timp_eveniment())+";"+eveniment.get_descriere_even()+"\n")
    
    def adauga(self, eveniment):
        '''
        Adauga un eveniment  in fisier
        :param eveniment - un eveniment
        '''
        self.__citeste_tot_din_fisier()
        RepositoryEveniment.adauga(self, eveniment)
        self.__append_eveniment_fisier(eveniment)
    
    def modifica(self, eveniment):
        '''
        actualizeaza un evenimnent din fisier
        :param eveniment - un eveniment (id_eveniment, data, timp, descriere)
        '''
        self.__citeste_tot_din_fisier()
        RepositoryEveniment.modifica(self, eveniment)
        self.__scrie_tot_in_fisier()
        
    def sterge_dupa_id(self, id_eveniment):
        '''
        sterge un eveniment din fisier dupa id-ul acestuia
        :param id_eveniment - int
        '''
        self.__citeste_tot_din_fisier()
        RepositoryEveniment.sterge_dupa_id(self, id_eveniment)
        self.__scrie_tot_in_fisier()
        
    def cauta_dupa_id(self, id_eveniment):
        '''
        Cauta un eveniment dupa un id_eveniment
        returneaza evenimentul cu id-ul dat
        :param id_eveniment - int, un id
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryEveniment.cauta_dupa_id(self, id_eveniment)
    
    def get_all(self):
        '''
        returneaza toate evenimentele din fisier
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryEveniment.get_all(self)
    
    def __len__(self):
        '''
        returneaza lungimea listei de evenimente din fisier
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryEveniment.__len__(self)
    
    
class FileRepoInscriere(RepositoryInscriere):
    '''
    Stocheaza/sterge/modifica/cauta inscrierile din fisier
    '''
    
    def __init__(self,txt):
        '''
        initializeaza repository-ul de inscrieri
        :param txt - string, fisierul unde sunt stocate inscrierile
        '''
        self.__txt = txt
        RepositoryInscriere.__init__(self)


    def __citeste_tot_din_fisier(self):
        '''
        Incarca inscrierile din fisier
        '''
        with open(self.__txt,"r") as f:
            self._elems = []
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(";")
                    inscriere = InscrDTO(int(parts[0]),int(parts[1]),int(parts[2]),float(parts[3]))
                    self._elems.append(inscriere)
    
    def __append_inscriere_fisier(self,inscriere):
        '''
        Stocheaza o inscriere la sfarsitul fisierului.
        :param inscriere - o inscriere
        '''
        with open(self.__txt,"a") as f:
            f.write(str(inscriere.get_id_inscriere())+";"+str(inscriere.get_id_persoana())+";"+str(inscriere.get_id_eveniment())+";"+str(inscriere.get_pret())+"\n")
                    
    
    def __scrie_tot_in_fisier(self):
        '''
        Stocheaza toate inscrierile in fisier
        '''
        with open(self.__txt,"w") as f:
            for inscriere in self._elems:
                f.write(str(inscriere.get_id_inscriere())+";"+str(inscriere.get_id_persoana())+";"+str(inscriere.get_id_eveniment())+";"+str(inscriere.get_pret())+"\n")
                
                
    def adauga(self, inscriere):
        '''
        Adauga o inscriere in fisier
        :param inscriere - o inscriere
        '''
        self.__citeste_tot_din_fisier()
        RepositoryInscriere.adauga(self, inscriere)
        self.__append_inscriere_fisier(inscriere)
        
    def sterge_inscriere_dupa_id(self, id_inscriere):
        '''
        sterge o inscriere din fisier dupa id-ul acesteia
        :param id_inscriere - int
        '''
        self.__citeste_tot_din_fisier()
        RepositoryInscriere.sterge_inscriere_dupa_id(self, id_inscriere)
        self.__scrie_tot_in_fisier()
        
    def cauta_dupa_id(self, id_inscriere):
        '''
        Cauta o inscriere dupa un id_inscriere
        returneaza inscrierea cu id-ul dat
        :param id_inscriere - int, un id
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryInscriere.cauta_dupa_id(self, id_inscriere)

    def get_all(self):
        '''
        returneaza toate inscrierile din fisier
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryInscriere.get_all(self)
    
    def __len__(self):
        '''
        returneaza lungimea listei de inscrieri din fisier
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryInscriere.__len__(self)

