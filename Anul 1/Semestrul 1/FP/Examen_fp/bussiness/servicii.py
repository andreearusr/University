
from domeniu.entitati import Melodie,MelodieDTO

class ServiceMelodie(object):
    '''
    Tip de date abstract
    Domeniu: serviciile ce pot fi realizate asupra melodiilor
    '''
    
    
    def __init__(self, repo_melodie,repo_melodie_dto, validator_melodie):
        '''
        Initializeaza obiectele de lucru ale service-ului
        :param repo_melodie - repository-ul de melodii
        :param validator_melodie - un validator de melodii
        '''
        
        self.__repo_melodie = repo_melodie
        self.__repo_melodie_dto = repo_melodie_dto
        self.__validator_melodie = validator_melodie
        
        
    def adauga(self, titlu, artist, gen, durata):
        '''
        Functie cu ajutorul careia putem adauga o melodie in repository
        :param titlu - string, un titlu
        :param artist - string, un artist
        :param gen - string, un gen
        :param durata - int, o durata
        '''
        melodie = Melodie(titlu,artist,gen,durata)
        self.__validator_melodie.valideaza(melodie)
        self.__repo_melodie.adauga(melodie)
    
    def cauta_melodie(self, titlu, artist):
        '''
        Functie cu ajutorul careia cautam o melodie din repository
        Returneaza melodia daca e gasita
        :param titlu - string,un titlu
        :param artist - string, un artist
        '''
        return self.__repo_melodie.cauta(titlu,artist)
    
    def modificare_melodie(self,melodie):
        '''
        Functie cu ajutorul careia modificam o melodie din repository cu valorile noi ale melodiei "melodie"
        :param melodie - o melodie - cu parametri noi: gen,durata
        '''
        self.__validator_melodie.valideaza(melodie)
        self.__repo_melodie.modifica(melodie)
        
        
    def exporta_melodii(self,nume_fisier):
        '''
        Functie care exporta melodiile din fisier, ordonate dupa artist si titlu
        :param nume_fisier - un nume de fisier
        '''
        melodii = self.__repo_melodie.get_all()
        melodii.sort(key = lambda el:(el.get_artist(),el.get_titlu()))
        
        for melodie in melodii:
            artist = melodie.get_artist()
            titlu = melodie.get_titlu()
            durata = melodie.get_durata()
            gen = melodie.get_gen()
            
            melodie_dto = MelodieDTO(artist,titlu,durata,gen)
            self.__repo_melodie_dto.adauga(melodie_dto)
            


