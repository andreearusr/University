from erori.exceptii import RepoError
from domeniu.entitati import Student,Lab
class RepositoryStudenti(object):
    
    
    def __init__(self):
        self._elems = []
        
    
    def get_all(self):
        return self._elems[:]
    
    def cauta_dupa_id(self,id_student):
        for el in self._elems:
            if el.get_id_student()==id_student:
                return el
        raise RepoError("Student inexistent!\n")
    
    
    
class FileRepositoryStudenti(RepositoryStudenti):
    
    def __init__(self,txt):
        self.__txt = txt 
        RepositoryStudenti.__init__(self)
        
    def __citeste_tot_din_fisier(self):
        with open(self.__txt,"r") as f:
            self._elems=[]
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != " ":
                    parts = line.split(";")
                    student = Student(int(parts[0]),parts[1])
                    self._elems.append(student)
                    
    
    def cauta_dupa_id(self, id_student):
        self.__citeste_tot_din_fisier()
        return RepositoryStudenti.cauta_dupa_id(self, id_student)
    
    def get_all(self):
        self.__citeste_tot_din_fisier()
        return RepositoryStudenti.get_all(self)
                    
                    

class RepositoryLaboratoare(object):
    
    
    def __init__(self):
        self._elems = []
        
    
    def cauta(self,id_student):
        rez=[]
        for el in self._elems:
            if el.get_id_student()==id_student:
                rez.append(el)
        return rez
    
    def adauga(self,asignare):
        if asignare in self._elems:
            raise RepoError("Asignare existenta!\n")
        self._elems.append(asignare)
        
    
    def get_all(self):
        return self._elems[:]
    
class FileRepositoryLaboratoare(RepositoryLaboratoare):
    
    def __init__(self,txt):
        self.__txt = txt
        RepositoryLaboratoare.__init__(self)
        
    def __citeste_tot_din_fisier(self):
        with open(self.__txt,"r") as f:
            self._elems =[]
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != " ":
                    parts = line.split(";")
                    asignare = Lab(int(parts[0]),int(parts[1]),parts[2])
                    self._elems.append(asignare)
                    
        
    def __append_lab_in_fisier(self,asignare):
        with open(self.__txt,"a") as f:
            f.write(str(asignare.get_id_student())+";"+str(asignare.get_nr_lab())+";"+asignare.get_nr_problema()+"\n")
            
    
    def cauta(self, id_student):
        self.__citeste_tot_din_fisier()
        return RepositoryLaboratoare.cauta(self, id_student)
    
    def adauga(self, asignare):
        self.__citeste_tot_din_fisier()
        RepositoryLaboratoare.adauga(self, asignare)
        self.__append_lab_in_fisier(asignare)
        
    
    def get_all(self):
        self.__citeste_tot_din_fisier()
        return RepositoryLaboratoare.get_all(self)
    



