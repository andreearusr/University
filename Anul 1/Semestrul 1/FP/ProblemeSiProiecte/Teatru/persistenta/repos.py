from erori.exceptii import RepoError
from domeniu.entitati import Piesa
class RepositoryPiese(object):
    '''
    Tip de date abstract
    Domeniu: Repository de piese de teatru
    '''
    
    def __init__(self):
        '''
        Initializeaza lista de piese de teatru din repository
        '''
        self._elems=[]
        
        
    def adauga(self,piesa):
        if piesa in self._elems:
            raise RepoError("Piesa deja existenta!\n")
        self._elems.append(piesa)
        
    def cauta(self, titlu, regizor):
        for el in self._elems:
            if el.get_titlu()==titlu:
                if el.get_regizor()==regizor:
                    return el  
        raise RepoError("Nu exista piesa cautata!\n")
    
    def modifica(self, piesa):
        
        titlu = piesa.get_titlu()
        regizor = piesa.get_regizor()
        piesa_noua = self.cauta(titlu, regizor)
        piesa_noua.set_gen(piesa.get_gen())
        piesa_noua.set_durata(piesa.get_durata())
        
class FileRepositoryPiese(RepositoryPiese):
    
    
    def __init__(self,txt):
        self.__txt = txt
        RepositoryPiese.__init__(self)
    
    def __citeste_tot_din_fisier(self):
        with open(self.__txt,"r") as f:
            self._elems=[]
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(";")
                    piesa = Piesa(parts[0],parts[1],parts[2],int(parts[3]))
                    self._elems.append(piesa)
    
    def __apend_piesa_in_fisier(self,piesa):
        with open(self.__txt,"a") as f:
            f.write(piesa.get_titlu()+";"+piesa.get_regizor()+";"+piesa.get_gen()+";"+str(piesa.get_durata())+"\n")
            
    def __scrie_tot_in_fisier(self):
        with open(self.__txt,"w") as f:
            for piesa in self._elems:
                f.write(piesa.get_titlu()+";"+piesa.get_regizor()+";"+piesa.get_gen()+";"+str(piesa.get_durata())+"\n")
            
    def adauga(self, piesa):
        self.__citeste_tot_din_fisier()
        RepositoryPiese.adauga(self, piesa)
        self.__apend_piesa_in_fisier(piesa)
        
    def cauta(self, titlu, regizor):
        self.__citeste_tot_din_fisier()
        return RepositoryPiese.cauta(self, titlu, regizor)
    
    def modifica(self, piesa):
        self.__citeste_tot_din_fisier()
        RepositoryPiese.modifica(self, piesa)
        self.__scrie_tot_in_fisier()
            



