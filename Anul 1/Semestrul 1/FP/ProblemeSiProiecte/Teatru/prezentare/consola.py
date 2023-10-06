
from erori.exceptii import ValidError, RepoError
from domeniu.entitati import Piesa
import random
import string
from random import randrange
from string import ascii_lowercase
class UI(object):
    
    
    def __ui_adauga_piesa(self):
        titlu = input("Dati titlul piesei:")
        regizor = input("Dati numele regizorului:")
        gen = input("Dati genul piesei:")
        durata = int(input("Dati durata piesei:"))
        
        self.__srv_piese.adauga_piesa(titlu,regizor,gen,durata)
        
    
    
    def __ui_modificare_piesa(self):
        titlu = input("Dati titlul piesei:")
        regizor = input("Dati numele regizorului:")
        self.__srv_piese.cauta_piesa(titlu, regizor)
        
        gen = input("Dati genul piesei:")
        durata = int(input("Dati durata piesei:"))
        piesa = Piesa(titlu, regizor, gen, durata)
        
        self.__srv_piese.modifica_piesa(piesa)
    

        
    def __creeaza_piese_aleator(self):
        nr = int(input("Cate piese doriti sa generati? "))
        for i in range(0,nr):
#             titlu = 
#             regizor = 
            gen = self.__get_random_string(10)
            durata = randint(1,10)
            self.__srv_piese.adauga_piesa(titlu,regizor,gen,durata)
    
    
    def __ui_export(self):
        nume = input("Dati un nume de fisier")
    
    
    def __init__(self,srv_piese):
        self.__srv_piese = srv_piese
        self.__comenzi ={"1": self.__ui_adauga_piesa,
                         "2": self.__ui_modificare_piesa,
                         "3": self.__creeaza_piese_aleator,
                         "4": self.__ui_export}

    
    def optiuni(self):
        print(
            '''
            1.Adauga piesa
            2.Modificare piesa
            3.Creeaza piese aleator
            4.Exporteaza piese
        
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
                
    
    
            


