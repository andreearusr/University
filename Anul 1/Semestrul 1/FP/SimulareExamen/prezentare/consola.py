
from erori.exceptii import RepoError
class UI(object):
    
    def ui_cautare_genuri(self):
#         lista =[]
#         nr = int(input("Cate genuri doriti sa introduceti? "))
#         for i in range(nr):
#             genuri = input("Introduceti gen:")
#             lista.append(genuri)
#         rezultat = self.__srv_piesa.cautare_genuri(lista)
#         for el in rezultat:
#             print(el)  

        genuri = input("Introduceti o lista de genuri separate prin  ,  :")
        rezultat = self.__srv_piesa.cautare_genuri(genuri)
        for el in rezultat:
            print(el)

    def ui_cumpara_bilete(self):
        id_bilet = int(input("Introduceti id opera:"))
        nr_bilete = int(input("Introduceti numarul de bilete:"))
        piesa = self.__srv_piesa.cumpara_bilete(id_bilet,nr_bilete)
        print(piesa)
        
        
    def __init__(self, srv_piesa):
        self.__srv_piesa = srv_piesa
        self.__comenzi = { "1": self.ui_cautare_genuri,
                        "2": self.ui_cumpara_bilete
                         }
    
    def optiuni(self):
        print('''
                1. Cautare piesa
                2. Cumparare bilete
        
             ''')
    
    
    def run(self):
        while True:
            self.optiuni()
            cmd = input("Alegeti optiunea: ")
            if cmd in self.__comenzi:
                try:
                    self.__comenzi[cmd]()
                except ValueError:
                    print("Valoare numerica invalida!")
                except RepoError as re:
                    print(re)
                    
            else:
                print("Comanda invalida!")
    



