
from erori.exceptii import ValidError, RepoError
class UI(object):

    
    
    
    
    def __ui_adauga_contact(self):
        id_contact = int(input("Dati un id:"))
        nume = input("Dati numele contactului:")
        nr_telefon = input("Dati un numar de telefon:")
        
        grup = input("Dati numele grupului:")
        
        self.__srv_agenda.adauga_contact(id_contact, nume, int(nr_telefon), grup)
    
    
    def __ui_cautare_nr_telefon(self):
        nume = input("Introduceti numele contactului:")
        contact = self.__srv_agenda.cautare_contact(nume)
        print(contact)
    
    
    def __ui_contacte_grup_ord(self):
        grup = input("Dati numele grupului:")
        contacte = self.__srv_agenda.contacte_grup(grup)
        if contacte == []:
            print("Nu exista contacte in grupul dat!")
        else:
            for contact in contacte:
                print(contact)
    
    
    def __ui_exportare(self):
        grup = input("Dati numele grupului:")
        self.__srv_agenda.exportare(grup)
    
    
    def __init__(self, srv_agenda):
        self.__srv_agenda = srv_agenda
        self.__comenzi ={"1": self.__ui_adauga_contact,
                         "2": self.__ui_cautare_nr_telefon,
                         "3": self.__ui_contacte_grup_ord,
                         "4": self.__ui_exportare
            }
    
    
    def optiuni(self):
        print(
            '''
            1.Adauga contact
            2.Cauta contact
            3.Contactele anumitui grup
            4.Exportare contacte grup
            
            ''')
    
    def run(self):
        while True:
            self.optiuni()
            cmd = input("Introduceti optiunea:")
            if cmd in self.__comenzi:
                try:
                    self.__comenzi[cmd]()
                except ValueError:
                    print("Valoare numerica invalida!")
                except ValidError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
            else:
                print("Comanda invalida!")
                    
                
    
    



