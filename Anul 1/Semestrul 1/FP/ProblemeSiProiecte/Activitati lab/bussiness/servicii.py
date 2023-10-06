
from domeniu.entitati import Student, Lab, LabDTO, Lab1DTO
from erori.exceptii import ValidError

class ServiceStudenti(object):
    
    
    def __init__(self, validator_studenti, repo_studenti):
        self.__validator_studenti = validator_studenti
        self.__repo_studenti = repo_studenti
    
    def get_studenti(self):
        return self.__repo_studenti.get_all()
    
    def cauta_student(self,id_student):
        if id_student<0:
            raise ValidError("Id invalid!\n")
        return self.__repo_studenti.cauta_dupa_id(id_student)



class ServiceLaboratoare(object):
    
    
    def __init__(self, validator_laboratoare, repo_laboratoare, repo_studenti):
        self.__validator_laboratoare = validator_laboratoare
        self.__repo_laboratoare = repo_laboratoare
        self.__repo_studenti = repo_studenti
    
    
    def asignare_laborator(self,id_student, nr_lab, nr_problema):
        
        asignare = Lab(id_student, nr_lab, nr_problema)
        self.__repo_laboratoare.adauga(asignare)
        
    
    def cauta_laborator(self,id_student):
        if id_student<0:
            raise ValidError("Id invalid!\n")
        return self.__repo_laboratoare.cauta(id_student)
    
    def vizualizare_laboratoare(self,id_student):
        laboratoare = self.__repo_laboratoare.get_all()
        rez =[]
        
        for lab in laboratoare:
            id_st = lab.get_id_student()
            if id_st == id_student:
                lb = lab.get_nr_lab()
                nr = lab.get_nr_problema()
                rez.append(LabDTO(lb,nr))
                
        return rez
    
    def vizualizare_stud_lab(self,nr_lab):
        laboratoare = self.__repo_laboratoare.get_all()
        rez =[]
        
        for lab in laboratoare:
            nr = lab.get_nr_lab()
            if nr == nr_lab:
                id_st = lab.get_id_student()
                student = self.__repo_studenti.cauta_dupa_id(id_st)
                nr_pb = lab.get_nr_problema()
                rez.append(Lab1DTO(student,nr_lab,nr_pb))
                
        return rez
    
    
    
    
        
        

