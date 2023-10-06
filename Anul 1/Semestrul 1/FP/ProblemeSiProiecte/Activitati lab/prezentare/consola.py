
from erori.exceptii import ValidError, RepoError
class UI(object):

    
    def __ui_vizualizare_studenti(self):
        studenti = self.__srv_studenti.get_studenti()
        if len(studenti)==0:
            print("Nu avem studenti in lista!\n")
            return 
        for student in studenti:
            print(student)
        
    
    
    def __ui_cauta_student(self):
        id_student = int(input("Introduceti id-ul studentului: "))
        print(self.__srv_studenti.cauta_student(id_student))
        
    
    def __ui_asignare_laborator(self):
        
        id_student = int(input("Introduceti id-ul studentului: "))
        self.__srv_studenti.cauta_student(id_student)
        
        nr_lab = int(input("Introduceti nr-ul laboratorului: "))
        labs = self.__srv_laboratoare.cauta_laborator(id_student)
        for lab in labs:
            nr = lab.get_nr_lab()
            if nr_lab == nr:
                raise ValidError("Nu puteti adauga 2 probleme la acelasi laborator!\n")
            
        nr_problema = input("Introduceti nr-ul problemei: ")
        self.__srv_laboratoare.asignare_laborator(id_student, nr_lab, nr_problema)
        
    def __ui_vizualizare_laboratoare(self):
        
        id_student = int(input("Introduceti id-ul studentului: "))
        self.__srv_studenti.cauta_student(id_student)
        
        labs = self.__srv_laboratoare.vizualizare_laboratoare(id_student)
        for lab in labs:
            print(lab)
    
    
    def __ui_vizualizare_stud_lab(self):
        nr_lab = int(input("Introduceti nr-ul laboratorului: "))
        
        labs = self.__srv_laboratoare.vizualizare_stud_lab(nr_lab)
        for lab in labs:
            print(lab)
    
    
    def __init__(self, srv_studenti, srv_laboratoare):
        self.__srv_studenti = srv_studenti
        self.__srv_laboratoare = srv_laboratoare
        self.__comenzi = {"1": self.__ui_vizualizare_studenti,
                          "2": self.__ui_cauta_student,
                          "3": self.__ui_asignare_laborator,
                          "4": self.__ui_vizualizare_laboratoare,
                          "5": self.__ui_vizualizare_stud_lab
            }
        
    
    
    def optiuni(self):
        "functie ce contine meniul"
        
        print(
            '''
            1.Vizualizare lista studenti
            2.Cauta student dupa id
            3.Asignare laborator la un student
            4.Vizualizare toate laboratoarele unui student
            5.Vizualizare studenti si laboratoare asignate pt un laborator dat
            
            ''')
    def run(self):
        while True:
            self.optiuni()
            cmd = input("Alegeti optiunea: ")
            if cmd in self.__comenzi:
                try:
                    self.__comenzi[cmd]()
                except ValueError:
                    print("Valoare numerica invalida! ")
                except ValidError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
                    
            else:
                print("Comanda invalida! ")

