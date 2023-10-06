
from erori.exceptii import RepoError
from domeniu.entitati import Contact,contactDTO

class ContactRepository(object):
    
    def __init__(self):
        self._elems = []
        
    
    
    def adauga(self,contact):
        if contact in self._elems:
            raise RepoError("Nu se pot adauga 2 nr de telefon pt acelasi nume!\n")
        self._elems.append(contact)
         
    def cauta(self,nume):
        for el in self._elems:
            if el.get_nume()==nume:
                return el 
        raise RepoError("Nu exista contactul cautat!\n")
    
    def get_all(self):
        return self._elems[:]
    
    
class FileContactRepository(ContactRepository):
    
    
    def __init__(self, txt):
        self.__txt = txt
        ContactRepository.__init__(self)
        
    
    def __citeste_tot_din_fisier(self):
        with open(self.__txt,"r") as f:
            self._elems=[]
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != " ":
                    parts = line.split(";")
                    contact = Contact(int(parts[0]),parts[1],int(parts[2]),parts[3])
                    
                    self._elems.append(contact)
    
    
    def  __append_contact_in_fisier(self,contact):
        with open (self.__txt,"a") as f:
            f.write(str(contact.get_id_contact())+";"+contact.get_nume()+";"+str(contact.get_nr_telefon())+";"+contact.get_grup()+"\n")
            
            
    def adauga(self, contact):
        self.__citeste_tot_din_fisier()
        ContactRepository.adauga(self, contact)
        self.__append_contact_in_fisier(contact)
        
    def cauta(self, nume):
        self.__citeste_tot_din_fisier()
        return ContactRepository.cauta(self, nume)

    def get_all(self):
        self.__citeste_tot_din_fisier()
        return ContactRepository.get_all(self)


class FileContactDTORepository(ContactRepository):
    
    def __init__(self,txt):
        self.__txt = txt
        ContactRepository.__init__(self)
        
    def __citeste_tot_din_fisier(self):
        with open(self.__txt,"r") as f:
            self._elems=[]
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != " ":
                    parts = line.split(",")
                    contact_dto = contactDTO(parts[0], int(parts[1]))
                    
                    self._elems.append(contact_dto)
                    
    def  __append_contact_in_fisier(self,contact_dto):
        with open (self.__txt,"a") as f:
            f.write(contact_dto.get_nume()+","+str(contact_dto.get_nr_telefon())+"\n")
                    
    def adauga(self, contact_dto):
        self.__citeste_tot_din_fisier()
        ContactRepository.adauga(self, contact_dto)
        self.__append_contact_in_fisier(contact_dto)
                    