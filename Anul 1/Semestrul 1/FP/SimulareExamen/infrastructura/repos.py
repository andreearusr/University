
from domeniu.entitati import Opera

from erori.exceptii import RepoError

class RepositoryPiesa(object):
    '''
    Tip de data abstract
    Domeniu: Repository-ul de piese/opere
    '''
    
    def __init__(self):
        '''
        Initializeaza lista de opere
        '''
        self._elems = []
        
    def cauta_dupa_id(self,id_opera):
        '''
        Functie care cauta o opera dupa un id-opera - int, si returneaza aceasta opera
        :param id_opera-int,un id
        Daca opera nu e gasita => arunca o exceptie de tipul  RepoError("Opera inexistenta!")
        '''
        for el in self._elems:
            if el.get_id_opera()==id_opera:
                return el
        raise RepoError("Opera inexistenta!")
        
        
    def get_all(self):
        '''
        functie care returneaza toate operele din lista
        '''
        return self._elems[:]

class FileRepoPiesa(RepositoryPiesa):
    '''
    Tip de date abstract
    Domeniu: Repository-ul de fisier al operelor
    '''
    
    
    def __init__(self, txt):
        '''
        Initializeaza repository-ul de fisiere unde sunt stocate operele
        :param txt:
        '''
        self.__txt = txt
        RepositoryPiesa.__init__(self)
        
    
    def __citeste_tot_din_fisier(self):
        '''
        Functie care incarca toate operele din fisier
        '''
        with open(self.__txt,"r") as f:
            self._elems = []
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(",")
                    opera = Opera(int(parts[0]),parts[1],parts[2],parts[3])
                    self._elems.append(opera)

    def get_all(self):
        '''
        Functie care returneaza toate operele din repository-ul de fisiere
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryPiesa.get_all(self)
    
    def cauta_dupa_id(self, id_opera):
        '''
        Functie care cauta o opera dupa un id_opera- int
        Returneaza opera gasita sau arunca o exceptie de tipul RepoError("Opera inexistenta!")
        :param id_opera - int,un id
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryPiesa.cauta_dupa_id(self, id_opera)
