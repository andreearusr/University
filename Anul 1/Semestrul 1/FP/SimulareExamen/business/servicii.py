
from domeniu.entitati import PiesaDTO

class ServicePiesa(object):
    '''
    Tip de date abstract
    Domeniu: service-ul de opere
    '''
    
    
    def __init__(self, repo_piesa):
        '''
        Initializeaza service-ul de opere
        :param repo_piesa - repository-ul de opere
        '''
        self.__repo_piesa = repo_piesa
    
    def cautare_genuri(self,genuri):
        '''
        Functie care cauta operele cu un gen dintre cele introduse la tastatura
        :param lista - lista de genuri
        returneaza o lista cu toate operele care au genul unul dintre cele mentionate
        '''
#         rezultat =[]
#         opere = self.__repo_piesa.get_all()
#         for opera in opere:
#             gen = opera.get_gen()
#             if gen in lista:
#                 rezultat.append(opera)
#         return rezultat

        rez=[]
        opere = self.__repo_piesa.get_all()
        
        genuri = genuri.strip()
        parts = genuri.split(",")
        for part in parts:
            for opera in opere:
                gen = opera.get_gen()
                if gen == part:
                    rez.append(opera)
        
        return rez 

    
    def cumpara_bilete(self,id_opera,nr_bilete):
        '''
        Functie care calculeaza suma totala a biletelor dorite sa fie cumparate de catre un utilizator
        returneaza piesa compusa din Opera la care doreste sa cumpere bilete si suma totala a biletelor
        :param id_bilet - int,un id
        :param nr_bilete - int
        '''
        opera = self.__repo_piesa.cauta_dupa_id(id_opera)
        pret = opera.get_pret()
        suma = 0
        for i in range (nr_bilete):
            suma = suma + int(pret)
            
        piesa = PiesaDTO(opera,suma)
        return piesa

            
        



