from erori.exceptii import RepoError
from domeniu.entitati import Melodie,MelodieDTO

class RepositoryMelodie(object):
    '''
    Tip abstract de date
    Domeniu: repository de melodii
    '''
    
    def __init(self):
        '''
        Initializeaza lista unde se vor stoca melodiile
        '''
        self._elems =[]
        
    def cauta(self, titlu, artist):
        '''
        Functie care cauta o melodie in repository dupa titlu si artist
        Returneaza melodia daca o gaseste
        Sau arunca RepoError  =>  Melodie inexistenta!\n  daca nu este gasita in lista
        :param titlu - string, un titlu
        :param artist - string, un artist
        '''
        for el in self._elems:
            if el.get_titlu()==titlu:
                if el.get_artist()==artist:
                    return el 
        raise RepoError("Melodie inexistenta!\n")
    
    def modifica(self,melodie):
        '''
        Functie care modifica o melodie deja existenta in repository
        Se modifica genul si durata 
        
        melodie_noua - melodia din repository care dorim sa fie modificata cu noile valori ale melodiei  "melodie"
        :param melodie - o melodie cu noile valori ce se doresc a fi modificate
        '''
        
        titlu = melodie.get_titlu()
        artist = melodie.get_artist()
        melodie_noua = self.cauta(titlu, artist)
        melodie_noua.set_gen(melodie.get_gen())
        melodie_noua.set_durata(melodie.get_durata())
        
    def adauga(self,melodie):
        '''
        Functie care adauga o melodie in repository
        Daca melodia exista deja in repository => arunca RepoError =>  Melodie deja existenta!\n
        :param melodie - o melodie
        '''
        
        if melodie in self._elems:
            raise RepoError("Melodie deja existenta!\n")
        self._elems.append(melodie)
    
    def get_all(self):
        '''
        Functie care returneaza toate melodiile din repository
        '''
        return self._elems[:]
    
    
class FileRepositoryMelodie(RepositoryMelodie):
    '''
    Tip de date abstract
    Domeniu: repository-ul de fisiere, unde sunt pastrate melodiile
    Mosteneste de la clasa RepositoryMelodie toate metodele
    '''
    
    
    def __init__(self,txt):
        '''
        Initializeaza un nume de fisier
        :param txt - string, un nume de fisier
        '''
        self.__txt = txt
        RepositoryMelodie.__init__(self)
        
    
    def __citeste_tot_din_fisier(self):
        '''
        Functie cu ajutorul careia citim toate melodiile aflate deja in fisier
        '''
        with open(self.__txt,"r") as f:
            self._elems=[]
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(";")
                    melodie = Melodie(parts[0],parts[1],parts[2],int(parts[3]))
                    self._elems.append(melodie)
                    
    def __append_melodie_in_fisier(self,melodie):
        '''
        Functie cu ajutorul careia adaugam o melodie la sfarsitul fisierului
        :param melodie - o melodie
        '''
        with open(self.__txt,"a") as f:
                f.write(melodie.get_titlu()+";"+melodie.get_artist()+";"+melodie.get_gen()+";"+str(melodie.get_durata())+"\n")
                
    def __scrie_tot_in_fisier(self):
        '''
        Functie cu ajutorul careia scriem in fisier
        '''
        with open(self.__txt,"w") as f:
            for melodie in self._elems:
                f.write(melodie.get_titlu()+";"+melodie.get_artist()+";"+melodie.get_gen()+";"+str(melodie.get_durata())+"\n")
                     
    def cauta(self, titlu, artist):
        '''
        Functie care cauta o melodie in repository-ul de fisiere dupa titlul si artistul acesteia
        :param titlu - string, un titlu
        :param artist - string, un artist
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryMelodie.cauta(self, titlu, artist)
    
    def modifica(self, melodie):
        '''
        Functie care modifica o melodie din repository-ul de fisiere cu ajutorul noilor valori ale melodiei "melodie"
        :param melodie - melodie, noua melodie
        '''
        self.__citeste_tot_din_fisier()
        RepositoryMelodie.modifica(self, melodie)
        self.__scrie_tot_in_fisier()
        
    def adauga(self, melodie):
        '''
        Functie care adauga o melodie in repository-ul de fisiere
        :param melodie - o melodie
        '''
        self.__citeste_tot_din_fisier()
        RepositoryMelodie.adauga(self, melodie)
        self.__append_melodie_in_fisier(melodie)
        
    def get_all(self):
        '''
        Functie care returneaza toate melodiile din repository-ul de fisiere
        '''
        self.__citeste_tot_din_fisier()
        return RepositoryMelodie.get_all(self)
    
class FileRepositoryMelodiiDTO(RepositoryMelodie):
    '''
    Tip de date abstract
    Domeniu: repository-ul de melodii exportate intr-un fisier
    '''
    
    def __init__(self,txt):
        '''
        Initializeaza numele fisierului unde se exporta
        :param txt - string, un nume de fisier
        '''

        self.__txt = txt
        RepositoryMelodie.__init__(self)

    def __citeste_tot_din_fisier(self):
        '''
        Functie cu ajutorul careia citim toate melodiile_dto aflate deja in fisier
        '''
        with open(self.__txt,"r") as f:
            self._elems=[]
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(",")
                    melodie_dto = MelodieDTO(parts[0],parts[1],int(parts[2]),parts[3])
                    self._elems.append(melodie_dto)
                    
    def __append_melodie_dto_in_fisier(self,melodie_dto):
        '''
        Functie cu ajutorul careia adaugam o melodie_dto la sfarsitul fisierului
        :param melodie - o melodie
        '''
        with open(self.__txt,"a") as f:
                f.write('"'+ melodie_dto.get_artist()+'"'+"," +'"'+melodie_dto.get_titlu()+'"'+","+'"'+str(melodie_dto.get_durata())+'"'+","+'"'+melodie_dto.get_gen()+'"'+"\n")
                  
    def adauga(self, melodie_dto):
        '''
        Functie care adauga o melodie_dto in repository-ul de fisiere
        :param melodie - o melodie
        '''
        self.__citeste_tot_din_fisier()
        RepositoryMelodie.adauga(self, melodie_dto)
        self.__append_melodie_dto_in_fisier(melodie_dto)
