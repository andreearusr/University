
import random
import string
from domeniu.entitati import Persoana, Eveniment, Adresa
from erori.exceptii import ValidError, RepoError
class UI(object):
    '''
    Tip de data abstract
    Domeniu: Interfata utilizator
    '''
    
    def __get_random_string(self,length):
        '''
        functie care genereaza un string random de o anumita lungime
        date de intrare: length - int, lungime string
        date de iesire: result - un string random
        :param length - lungime 
        '''
        letters = string.ascii_lowercase
        result = ''.join(random.choice(letters) for i in range(length))
        return result
    
    def __ui_genereaza_persoane(self):
        '''
        functie care genereaza persoane random si transmite informatiile generate pentru a adauga o persoana la lista de persoane:
            id_persoana,nume,adresa(strada,numar,oras)
        '''
        n= int(input("Cate persoane doriti sa generati? "))
        for i in range(0,n):
            id_persoana = random.randrange(0,500)
            nume = self.__get_random_string(6)
            strada = self.__get_random_string(10)
            numar = random.randrange(0,200)
            oras = self.__get_random_string(5)
            adresa = Adresa(strada, numar, oras)
            self.__srv_persoana.adauga_persoana(id_persoana,nume,adresa)
    
    def __ui_genereaza_evenimente(self):
        '''
        functie care genereaza evenimente random si transmite informatiile generate pentru a adauga un eveniment la lista de evenimente:
            id_eveniment,data_eveniment,timp_eveniment,descriere_even
        '''
        n = int(input("Cate evenimente doriti sa generati? "))
        for i in range(0,n):
            id_eveniment = random.randrange(0,200)
            data_eveniment = random.randrange(0,32)
            timp_eveniment = round(random.uniform(0,72),1)
            descriere_even = self.__get_random_string(10)
            self.__srv_eveniment.adauga_eveniment(id_eveniment,data_eveniment,timp_eveniment,descriere_even)
    
    def __ui_adauga_persoana(self):
        '''
        functie care transmite informatiile primite de la utilizator necesare pentru a adauga o persoana:
            id_persoana,nume,adresa(strada,numar,oras)
        '''
        id_persoana =  int(input("Introduceti id-ul: "))
        nume = input("Introduceti numele: ")
        strada = input('''Introduceti adresa:
        Introduceti strada: ''')
        numar = int(input("        Introduceti numarul:"))
        oras = input("        Introduceti orasul: ")
        adresa = Adresa(strada, numar, oras)
        self.__srv_persoana.adauga_persoana(id_persoana,nume,adresa)
        
    def __ui_afiseaza_persoane(self):
        '''
        functie care afiseaza persoanele din lista de persoane
        date de intrare: -
        date de iesire: persoanele din lista
        daca nu exista persoane : Nu exista persoane in lista!
        '''
        persoane = self.__srv_persoana.get_persoane()
        if len(persoane)==0:
            print("Nu exista persoane in lista! ")
            return
        for persoana in persoane:
            print(persoana)
            
    def __ui_sterge_persoana(self):
        '''
        functie care transmite informatiile primite de la utilizator necesare pentru a sterge o persoana:
            id_persoana
        '''
        id_persoana = int(input("Introduceti id persoana: "))
        self.__srv_inscriere.sterge_persoana_inscriere(id_persoana)
        
    def __ui_modifica_persoana(self):
        '''
        functie care transmite informatiile primite de la utilizator necesare pentru a modifica o persoana:
            id_persoana,nume_nou,adresa_noua(strada,numar,oras)
        '''
        id_persoana = int(input("Introduceti id persoana: "))
        self.__srv_persoana.cauta_persoana(id_persoana)
        nume_nou = input("Introduceti numele nou: ")
        strada = input('''Introduceti adresa noua:
        Introduceti strada: ''')
        numar = int(input("        Introduceti numarul: "))
        oras = input("        Introduceti orasul: ")
        adresa_noua = Adresa(strada, numar, oras)
        persoana = Persoana(id_persoana,nume_nou,adresa_noua) 
        self.__srv_persoana.modifica_persoana(persoana) 
        
    def __ui_cauta_persoana(self):
        '''
        functie care transmite informatiile primite de la utilizator necesare pentru a cauta o persoana:
            id_persoana
        '''
        id_persoana = int(input("Introduceti id persoana: "))
        print(self.__srv_persoana.cauta_persoana(id_persoana))   
    
    
    def __ui_adauga_eveniment(self):
        '''
        functie care transmite informatiile primite de la utilizator necesare pentru a adauga un eveniment:
            id_eveniment,data_eveniment,timp_eveniment,descriere_even
        '''
        id_eveniment = int(input("Introduceti id eveniment: "))
        data_eveniment = int(input("Introduceti data eveniment: "))
        timp_eveniment= float(input("Introduceti durata eveniment: "))
        descriere_even = input("Introduceti descriere eveniment: ")
        self.__srv_eveniment.adauga_eveniment(id_eveniment, data_eveniment, timp_eveniment, descriere_even)
    
    
    def __ui_afiseaza_evenimente(self):
        '''
        functie care afiseaza evenimentele din lista de evenimente
        date de intrare: -
        date de iesire: evenimentele din lista
        daca nu exista evenimente:  Nu exista evenimente in lista!
        '''
        evenimente = self.__srv_eveniment.get_evenimente()
        if len(evenimente)==0:
            print("Nu exista evenimente in lista! ")
            return 
        for eveniment in evenimente:
            print(eveniment)
            
    def __ui_sterge_eveniment(self):
        '''
        functie care transmite informatiile primite de la utilizator necesare pentru a sterge un eveniment:
            id_eveniment
        '''
        id_eveniment = int(input("Introduceti id eveniment: "))
        self.__srv_inscriere.sterge_eveniment(id_eveniment)
            
    def __ui_modifica_eveniment(self):
        '''
        functie care transmite informatiile primite de la utilizator necesare pentru a sterge un eveniment:
            id_eveniment,data_noua,timp_nou,descriere_noua
        '''
        id_eveniment = int(input("Introduceti id eveniment: "))
        self.__srv_eveniment.cauta_eveniment(id_eveniment)
        data_noua = int(input("Introduceti o noua data: "))
        timp_nou = float(input("Introduceti un timp nou: "))
        descriere_noua = input("Introduceti o descriere noua: ")
        eveniment = Eveniment(id_eveniment,data_noua,timp_nou,descriere_noua)
        self.__srv_eveniment.modifica_eveniment(eveniment)
        
    def __ui_cauta_eveniment(self):
        '''
        functie care transmite informatiile primite de la utilizator necesare pentru a cauta un eveniment:
            id_eveniment
        '''
        id_eveniment = int(input("Introduceti id eveniment: "))
        eveniment = self.__srv_eveniment.cauta_eveniment(id_eveniment)
        print(eveniment)
    
    
    def __ui_inscriere(self):
        '''
        functie care transmite informatiile primite de la utilizator necesare pentru a adauga o inscriere:
            id_inscriere,id_persoana,id_eveniment,pret_inscriere
        '''
        id_inscriere = int(input("Introduceti id inscriere: "))
        id_persoana = int(input("Introduceti id persoana: "))
        id_eveniment = int(input("Introduceti id eveniment: "))
        pret = float(input("Introduceti pretul biletului: "))
        self.__srv_inscriere.adauga_inscriere(id_inscriere,id_persoana,id_eveniment,pret)
    

    def __ui_afiseaza_inscrieri(self):
        '''
        functie care afiseaza inscrierile din lista de inscrieri
        date de intrare: -
        date de iesire: inscrierile din lista
        daca nu avem nicio inscriere:  Nu exista inscrieri in lista!
        '''
        inscrieri = self.__srv_inscriere.get_inscrieri()
        if len(inscrieri)==0:
            print("Nu exista inscrieri in lista! ")
            return 
        for inscriere in inscrieri:
            print(inscriere)
    
    
    def __ui_lista_evenimente_persoana(self):
        '''
        functie care afiseaza lista de evenimente la care participa o persoana,
            ordonat dupa descriere(alfabetic), dupa data
        date de intrare: - 
        date de iesire: evenimente la care participa o persoana(ordonate)
        daca nu exista persoane participante la evenimente:  Persoana nu participa la niciun eveniment!
        '''
        id_persoana = int(input("Introduceti id persoana: "))
        lista = self.__srv_inscriere.ordonare_lista_evenimente_persoana(id_persoana)
        if len(lista)==0:
            print("Persoana nu participa la niciun eveniment! ")
        else:
            for el in lista:
                print(el)
        
    
    def __ui_persoane_multe_evenimente(self):
        '''
        functie care afiseaza persoanele participante la cele mai multe evenimente:
                Id persoana:  Nume:  Numar evenimente:
        date de intrare: - 
        date de iesire: persoane participante la cele mai multe evenimente
        daca nu exista persoane participante la evenimente cu datele cerute:  Nu exista inscrieri in lista!
        '''
        lista_pers = self.__srv_inscriere.persoane_multe_evenimente()
        if len(lista_pers)==0:
            print("Nu exista inscrieri in lista! ")
        else:
            for pers in lista_pers:
                print(pers)
    
    
    def __ui_evenimente_multi_participanti(self):
        '''
        functie care afiseaza primele 20% evenimente cu cei mai multi participanti
        date de intrare: - 
        date de iesire: primele 20% evenimente cu cei mai multi participanti 
        '''
        rezultat = self.__srv_inscriere.evenimente_multi_participanti()
        if len(rezultat)==0:
            print("Nu putem da primele 20% evenimente")
        else: 
            for rez in rezultat:
                print(rez)

    
    def __ui_evenimente_nr_participanti(self):
        '''
        functie care afiseaza evenimentele ce au un numar de participanti cuprins intre 2 valori introduse
        date de intrare: -
        date de iesire: evenimentele cerute
        daca nu exista niciun eveniment ce se incadreaza in datele cerute:   
                Nu exista evenimente cu un numar de participanti intre cele doua valori introduse! 
        '''
        a = int(input("Dati primul numar: "))
        b = int(input("Dati al doilea numar: "))
        lista = self.__srv_inscriere.evenimente_nr_participanti(a,b)
        if len(lista)==0:
            print("Nu exista evenimente cu un numar de participanti intre cele doua valori introduse! ")
        else:
            for el in lista:
                print(el)
            
            
    def __init__(self, srv_persoana, srv_eveniment, srv_inscriere):
        '''
        functie care detine un dictionar de comenzi, fiecare comanda fiind in legatura cu o functie ui
                            un service persoana
                            un service eveniment
                            un service inscriere
        :param srv_persoana - service persoana (clasa)
        :param srv_eveniment - service eveniment (clasa)
        :param srv_inscriere - service inscriere (clasa)
        '''
        self.__srv_persoana = srv_persoana
        self.__srv_eveniment = srv_eveniment
        self.__srv_inscriere = srv_inscriere
        self.__comenzi = {"1":self.__ui_genereaza_persoane,
                          "2": self.__ui_genereaza_evenimente,
                          "3": self.__ui_adauga_persoana,
                          "4": self.__ui_afiseaza_persoane,
                          "5": self.__ui_sterge_persoana,
                          "6": self.__ui_modifica_persoana,
                          "7": self.__ui_cauta_persoana,
                          "8": self.__ui_adauga_eveniment,
                          "9": self.__ui_afiseaza_evenimente,
                          "10": self.__ui_sterge_eveniment,
                          "11": self.__ui_modifica_eveniment,
                          "12": self.__ui_cauta_eveniment,
                          "13": self.__ui_inscriere,
                          "14": self.__ui_afiseaza_inscrieri,
                          "15": self.__ui_lista_evenimente_persoana,
                          "16": self.__ui_persoane_multe_evenimente,
                          "17": self.__ui_evenimente_multi_participanti,
                          "18": self.__ui_evenimente_nr_participanti}

    
    def optiuni(self):
        '''
        functie ce contine meniul aplicatiei
        '''
        print(
            '''
            1. Genereaza persoane
            2. Genereaza evenimente
            3. Adauga persoana
            4. Afisare persoane
            5. Sterge persoana dupa id
            6. Modifica persoana
            7. Cauta persoana dupa id
            8. Adauga eveniment
            9. Afisare evenimente
            10. Sterge eveniment dupa id
            11. Modifica eveniment
            12. Cauta eveniment dupa id
            13. Inscriere persoana la un eveniment
            14. Afiseaza inscrierile
            15. Lista de evenimente la care participa o persoana
                        (ordonat alfabetic dupa descriere,dupa data)
            16. Persoane participante la cele mai multe evenimente
            17. Primele 20% evenimente cu cei mai multi participanti
            18. Evenimente cu un numar de participanti intre 2 valori introduse
            
            ''')

    def run(self):
        '''
        functia principala run, de unde se apeleaza celelalte comenzi
        exceptii: 
          de tipul ValueError - daca valoarea introdusa nu este specifica tipului de date caracteristic => Valoare numerica invalida!
          de tipul ValidError
          de tipul RepoError
        daca comanda introdusa nu este disponibila in meniu => Comanda invalida!
        '''
        while True:
            self.optiuni()
            cmd = input("Alegeti optiunea: ")
            if cmd == "exit":
                print("Goodbye! ")
                return
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
            
            
        

    
    
    
    



