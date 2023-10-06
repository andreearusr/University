
from erori.exceptii import ValidError
class ValidatorContact(object):
    
    
    def __init__(self):
        pass
    
    
    def valideaza_contact(self,contact):
        erori =""
        if contact.get_id_contact()<1:
            erori+= "Id invalid!\n"
        if contact.get_nume()=="":
            erori+= "Nume invalid!\n"
        if str(contact.get_nr_telefon())=="":
            erori+= "Nr telefon invalid!\n"
        if contact.get_grup()!="Prieteni":
            if contact.get_grup()!="Familie":
                if contact.get_grup()!="Job":
                    if contact.get_grup()!="Altele":
                        erori+= "Grup invalid!\n"
            
        if len(erori)>0:
            raise ValidError(erori)
        



