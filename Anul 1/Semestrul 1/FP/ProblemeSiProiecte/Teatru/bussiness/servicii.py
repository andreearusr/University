
from domeniu.entitati import Piesa


class ServicePiese(object):
    '''
    Tip de date abstract
    Domeniu: operatiile ce se pot realiza asupra unei piese de teatru
    '''
    
    
    def __init__(self, repo_piese, validator_piese):
        '''
        Initializeaza obiectele cu care lucreaza service-ul de piese
        :param repo_piese - un repository de piese
        :param validator_piese - un validator de piese
        '''
        self.__repo_piese = repo_piese
        self.__validator_piese = validator_piese
    
    
    def adauga_piesa(self, titlu, regizor, gen, durata):
        '''
        Functie care intervine in adaugarea unei piese de teatru in fisier
        :param titlu - string,un titlu
        :param regizor- string,un regizor
        :param gen- string,un gen
        :param durata- int, o durata
        '''
        piesa = Piesa( titlu, regizor, gen, durata)
        self.__validator_piese.valideaza(piesa)
        self.__repo_piese.adauga(piesa)

    def cauta_piesa(self, titlu, regizor):
        '''
        Functie cu ajutorul careia verificam daca exista o piesa de teatru dorita
        :param titlu- string, un titlu
        :param regizor - string, un regizor
        returneaza piesa de teatru cautata, daca se afla in fisier
        '''
        piesa = self.__repo_piese.cauta(titlu, regizor)
        return piesa
        
        
    def modifica_piesa(self, piesa):
        '''
        Functie cu ajutorul careia modificam o piesa din fisier 
        :param piesa - o piesa de teatru
        '''
        
        self.__validator_piese.valideaza(piesa)
        self.__repo_piese.modifica(piesa)
    