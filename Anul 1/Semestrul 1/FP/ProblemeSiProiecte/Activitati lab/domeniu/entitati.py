class Student(object):
    
    
    def __init__(self,id_student, nume):
        self.__id_student = id_student
        self.__nume = nume

    def get_id_student(self):
        return self.__id_student


    def get_nume(self):
        return self.__nume
    
    def __eq__(self,other):
        return self.__id_student==other.__id_student
    
    def __str__(self):
        return "Id:"+str(self.__id_student)+"  Nume:"+self.__nume


class Lab(object):
    
    def __init__(self,id_student, nr_lab, nr_problema):
        self.__id_student = id_student
        self.__nr_lab = nr_lab
        self.__nr_problema = nr_problema

    def get_id_student(self):
        return self.__id_student


    def get_nr_lab(self):
        return self.__nr_lab


    def get_nr_problema(self):
        return self.__nr_problema

    

class LabDTO(object):
    
    def __init__(self,nr_lab , nr_problema):
        self.__nr_lab = nr_lab
        self.__nr_problema = nr_problema
        
    
    def __str__(self):
        return "Nr laborator:"+str(self.__nr_lab)+"  Nr problema:"+self.__nr_problema
    
    
class Lab1DTO(object):
    
    def __init__(self,student, nr_lab, nr_problema):
        self.__student = student
        self.__nr_lab = nr_lab
        self.__nr_problema = nr_problema
        
    def __str__(self):
        return "Student:"+str(self.__student)+"  Nr laborator:"+str(self.__nr_lab)+"  Nr problema:"+self.__nr_problema
