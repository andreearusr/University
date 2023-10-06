from domeniu.entitati import Melodie
from erori.exceptii import ValidError,RepoError
import random 
class UI(object):

    
    def __ui_modificare_melodie(self):
        titlu = input("Dati titlul melodiei:") 
        artist = input("Dati artistul melodiei")
        
        self.__srv_melodie.cauta_melodie(titlu,artist)
        gen = input("Dati genul melodiei:")
        durata = int(input("Dati durata melodiei:"))
        
        melodie = Melodie(titlu,artist,gen,durata)
        self.__srv_melodie.modificare_melodie(melodie)
        

    def __ui_creeaza_aleator_melodii(self):
        nr = int(input("Cate melodii doriti sa generati? "))
        l_titluri = input("Introduceti o lista de titluri separate prin virgula: ")
        l_artisti = input("Introduceti o lista de artisti separati prin virgula: ")
        
        lista_t =[]
        l_titluri.strip()
        titluri = l_titluri.split(",")
        for titlu in titluri:
            lista_t.append(titlu)
        
        lista_a =[]
        l_artisti.strip()
        artisti = l_artisti.split(",")
        for artist in artisti:
            lista_a.append(artist)
        
        nr_melodii=0
        genuri =['Rock','Pop','Jazz','Altele']
        for i in range(nr):
            titlu = random.choice(lista_t)
            artist = random.choice(lista_a)
            gen = random.choice(genuri)
            print(gen)
            durata = random.randrange(1,500)
            self.__srv_melodie.adauga(titlu,artist,gen,durata)
            nr_melodii+=1
        print(nr_melodii)
    
    
    def __ui_exporta_melodii(self):
        
        nume_fisier = input("Dati numele fisierului, cu extensia  .txt  :")
        self.__srv_melodie.exporta_melodii(nume_fisier)
        
    
    def __init__(self,srv_melodie):
        self.__srv_melodie = srv_melodie
        self.__comenzi = {"1": self.__ui_modificare_melodie,
                          "2": self.__ui_creeaza_aleator_melodii,
                          "3": self.__ui_exporta_melodii
            }

    
    def optiuni(self):
        print( 
            '''
            1.Modificare melodii
            2.Creeaza aleator melodii
            3.Exporta melodii
            
            ''')
    def run(self):
        while True:
            self.optiuni()
            cmd = input("Alegeti optiunea dorita:")
            if cmd in self.__comenzi:
                try:
                    self.__comenzi[cmd]()
                except ValueError:
                    print("Valoare numerica invalida!\n")
                except ValidError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
            else:
                print("Comanda invalida!\n")
    
    
    
    
    

