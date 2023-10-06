
from domeniu.entitati import Contact,contactDTO

class ServiceAgenda(object):
    
    
    def __init__(self, repo_contact_dto, repo_contact, validator_contact):
        self.__repo_contact_dto = repo_contact_dto
        self.__repo_contact = repo_contact
        self.__validator_contact = validator_contact
    
    def adauga_contact(self,id_contact,nume,nr_telefon,grup):
        
        contact = Contact(id_contact,nume,nr_telefon,grup)
        self.__validator_contact.valideaza_contact(contact)
        self.__repo_contact.adauga(contact)
        
    def cautare_contact(self,nume):
        if nume != "":
            contact = self.__repo_contact.cauta(nume)
        else:
            print("Nume invalid!\n")
        
        return contact 
    
    def contacte_grup(self,grup):
        contacte = self.__repo_contact.get_all()
        rez=[]
        
        for contact in contacte:
            if contact.get_grup()==grup:
                rez.append(contact)
        
        rez.sort(key=lambda cont:cont.get_nume())
        return rez 
    
    def exportare(self,grup):
        contacte = self.__repo_contact.get_all()
    
        for contact in contacte:
            if contact.get_grup()==grup:
                nume = contact.get_nume()
                nr_telefon = contact.get_nr_telefon()
                cont = contactDTO(nume,nr_telefon) 
                self.__repo_contact_dto.adauga(cont)
                
                