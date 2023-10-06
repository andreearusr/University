class Contact(object):
    
    
    def __init__(self, id_contact, nume, nr_telefon, grup):
        self.__id_contact = id_contact
        self.__nume = nume
        self.__nr_telefon = nr_telefon
        self.__grup = grup

    def get_id_contact(self):
        return self.__id_contact


    def get_nume(self):
        return self.__nume


    def get_nr_telefon(self):
        return self.__nr_telefon


    def get_grup(self):
        return self.__grup

    def __eq__(self,other):
        return self.__nume == other.__nume
    
    def __str__(self):
        return "Id:"+str(self.__id_contact)+"  Nume:"+self.__nume+"  Nr telefon:"+str(self.__nr_telefon)+"  Grup:"+self.__grup
    
class contactDTO(object):
    
    def __init__(self,nume ,nr_telefon):
        self.__nume = nume
        self.__nr_telefon = nr_telefon

    def get_nume(self):
        return self.__nume


    def get_nr_telefon(self):
        return self.__nr_telefon


