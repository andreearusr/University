from domeniu.entitati import Contact,contactDTO
from infrastructura.repos import FileContactRepository, FileContactDTORepository,ContactRepository
from erori.exceptii import RepoError,ValidError
from validare.validatori import ValidatorContact
from bussiness.servicii import ServiceAgenda

import unittest

'''
class Teste(object):
    
    
    def __init__(self):
        pass

    def ruleaza_teste_domeniu(self):
        id_contact = 5
        nume = "Andrei"
        nr_telefon = 45563442312
        grup = "Prieteni"
        contact = Contact(id_contact,nume,nr_telefon,grup)
        assert(contact.get_id_contact()==5)
        assert(contact.get_nume()=="Andrei")
        assert(contact.get_nr_telefon()==45563442312)
        assert(contact.get_grup()=="Prieteni")
        assert(str(contact)=="Id:5  Nume:Andrei  Nr telefon:45563442312  Grup:Prieteni")
        
        nume1 = "Raul"
        nr_telefon1 = 8976543214
        contact2 = contactDTO(nume1,nr_telefon1)
        assert(contact2.get_nume()=="Raul")
        assert(contact2.get_nr_telefon()==8976543214)
        
        
    def ruleaza_teste_repo(self):
        with open ("test_contact.txt","w") as f:
            f.write("")
        repo_contact = FileContactRepository("test_contact.txt")
        with open ("test_contact_dto.txt","w") as fi:
            fi.write("")
        repo_contact2 = FileContactDTORepository("test_contact_dto.txt")
        
        id_contact = 5
        nume = "Andrei"
        nr_telefon = 45563442312
        grup = "Prieteni"
        contact = Contact(id_contact,nume,nr_telefon,grup)
        repo_contact.adauga(contact)
        alls = repo_contact.get_all()
        assert(len(alls)==1)
        
        contact2 = repo_contact.cauta("Andrei")
        assert(str(contact2)=="Id:5  Nume:Andrei  Nr telefon:45563442312  Grup:Prieteni")
        try:
            repo_contact.cauta("Raluca")
            assert (False)
        except RepoError as re:
            assert(str(re)=="Nu exista contactul cautat!\n")
        
        
        nume_dto = "Andreea"
        nr_telefon_dto = 1286543241
        
        contact_dto = contactDTO(nume_dto,nr_telefon_dto)
        repo_contact2.adauga(contact_dto)
        
        
        
    def ruleaza_teste_validatori(self):
        validator_contact = ValidatorContact()
        id_contact = 5
        nume = "Andrei"
        nr_telefon = 45563442312
        grup = "Prieteni"
        contact = Contact(id_contact,nume,nr_telefon,grup)
        validator_contact.valideaza_contact(contact)
        
        try:
            validator_contact.valideaza_contact(Contact(4,"",7654321675,"ADJgj"))
            assert (False)
        except ValidError as ve:
            assert(str(ve)=="Nume invalid!\nGrup invalid!\n")
            
        try:
            validator_contact.valideaza_contact(Contact(-5,"Rus","" ,"Familie"))
            assert (False)
        except ValidError as ve:
            assert(str(ve)=="Id invalid!\nNr telefon invalid!\n")
    
    
    def ruleaza_teste_service(self):
        validator_contact = ValidatorContact()
        with open ("test_contact.txt","w") as f:
            f.write("")
        repo_contact = FileContactRepository("test_contact.txt")
        with open ("test_contact_dto.txt","w") as fi:
            fi.write("")
        repo_contact2 = FileContactDTORepository("test_contact_dto.txt")
        service_contact = ServiceAgenda(repo_contact2,repo_contact,validator_contact)
        
        service_contact.adauga_contact(8, "Maria", 9324567891, "Job")
        alls = repo_contact.get_all()
        assert(len(alls)==1)
        
        contact = service_contact.cautare_contact("Maria")
        assert(str(contact)=="Id:8  Nume:Maria  Nr telefon:9324567891  Grup:Job")
        
        service_contact.adauga_contact(9, "Ariana", 3548567891, "Job")
        service_contact.adauga_contact(12, "Mihai", 9324568121, "Familie")
        rez = service_contact.contacte_grup("Job")
        
        assert(str(rez[1])=="Id:8  Nume:Maria  Nr telefon:9324567891  Grup:Job")
        assert(str(rez[0])=="Id:9  Nume:Ariana  Nr telefon:3548567891  Grup:Job")
        
        service_contact.exportare("Familie")
        
    def ruleaza_toate_testele(self):
        self.ruleaza_teste_domeniu()
        self.ruleaza_teste_repo()
        self.ruleaza_teste_validatori()
        self.ruleaza_teste_service()
    
'''  

class TestCaseContactDomeniu(unittest.TestCase):
    
    def setUp(self):
        id_contact = 5
        nume = "Andrei"
        nr_telefon = 45563442312
        grup = "Prieteni"
        self.contact = Contact(id_contact,nume,nr_telefon,grup)
        
    def test_getteri(self):
        self.assertEqual(self.contact.get_id_contact(),5)
        self.assertEqual(self.contact.get_nume(),"Andrei")
        self.assertEqual(self.contact.get_nr_telefon(),45563442312)
        self.assertEqual(self.contact.get_grup(),"Prieteni")
        self.assertEqual(str(self.contact),"Id:5  Nume:Andrei  Nr telefon:45563442312  Grup:Prieteni")
        
        
        contact1 = Contact(3,"Andrei",9872345678,"Job")
        self.assertEqual(self.contact,contact1)
        
    
class TestCaseContactDTODomeniu(unittest.TestCase):
    
    def setUp(self):
        nume = "Raul"
        nr_telefon = 8976543214
        self.contact1 = contactDTO(nume,nr_telefon)
        
    def test_getteri(self):
        self.assertEqual(self.contact1.get_nume(),"Raul")
        self.assertEqual(self.contact1.get_nr_telefon(),8976543214)
        
        

class TestCaseValidatorContact(unittest.TestCase):
    
    def setUp(self):
        self.validator_contact = ValidatorContact()
        
    def test_valideaza(self):
        contact = Contact(5,"Marius",3421567894,"Prieteni")
        self.validator_contact.valideaza_contact(contact)
        
        contact1 = Contact(-3,"",3421567894,"DAggsh")
        self.assertRaises(ValidError, self.validator_contact.valideaza_contact, contact1)
        
        contact2 = Contact(2,"","","Job")
        self.assertRaises(ValidError, self.validator_contact.valideaza_contact, contact2)
        
    
class TestCaseRepoContact(unittest.TestCase):
    
    def setUp(self):
        self.repo_contact = ContactRepository()
        self.id_contact = 5
        self.nume = "Andrei"
        self.nr_telefon = 45563442312
        self.grup = "Prieteni"
        self.contact = Contact(self.id_contact,self.nume,self.nr_telefon,self.grup)
        self.repo_contact.adauga(self.contact)
        
    def test_adauga(self):
        self.assertEqual(len(self.repo_contact.get_all()),1)
        contact = Contact(6,"Andreea",7654321987,"Job")
        self.repo_contact.adauga(contact)
        self.assertEqual(len(self.repo_contact.get_all()),2)
        
        self.assertRaises(RepoError, self.repo_contact.adauga, contact)
        
    def test_cauta(self):
        self.assertEqual(self.repo_contact.cauta("Andrei"),self.contact)
        self.assertRaises(RepoError, self.repo_contact.cauta, "Raul")
        
    def test_get_all(self):
        self.assertEqual(len(self.repo_contact.get_all()),1)
        
        contact = Contact(6,"Andreea",7654321987,"Job")
        self.repo_contact.adauga(contact)
        self.assertEqual(len(self.repo_contact.get_all()),2)
        alls = self.repo_contact.get_all()
        self.assertEqual(alls[0],self.contact)
        self.assertEqual(alls[1],contact)
        
class TestCaseFileRepoContact(unittest.TestCase):
    
    def setUp(self):
        with open("test_contact.txt","w") as f:
            f.write("")
        self.repo = FileContactRepository("test_contact.txt")
        
    
    def test_adauga(self):
        id_contact = 5
        nume = "Andrei"
        nr_telefon = 45563442312
        grup = "Prieteni"
        contact = Contact(id_contact,nume,nr_telefon,grup)
        self.repo.adauga(contact)
        
        self.assertEqual(len(self.repo.get_all()),1)
        self.assertRaises(RepoError, self.repo.adauga, contact) 
        
    
    def test_cauta(self):
        self.repo.adauga(Contact(4,"Mihai",6534218765,"Familie"))
        self.assertEqual(str(self.repo.cauta("Mihai")),"Id:4  Nume:Mihai  Nr telefon:6534218765  Grup:Familie")
        self.assertRaises(RepoError, self.repo.cauta, "Marian")
        
    
    def test_get_all(self):
        contact = Contact(4,"Mihai",6534218765,"Familie")
        contact1 = Contact(7,"Ariana",3412113211,"Prieteni")
        self.repo.adauga(contact)
        self.repo.adauga(contact1)
        alls = self.repo.get_all()
        self.assertEqual(alls[0],contact)
        self.assertEqual(alls[1],contact1)
        
    
class TestCaseFileRepoContactDTO(unittest.TestCase):
    
    def setUp(self):
        with open("test_contact_dto.txt","w") as f:
            f.write("")
        self.repo = FileContactDTORepository("test_contact_dto.txt")
        
    
    def test_adauga(self):
        nume = "Raul"
        nr_telefon = 8976543214
        contact1 = contactDTO(nume,nr_telefon)    
        self.repo.adauga(contact1)
        
        #self.assertRaises(RepoError, self.repo.adauga, contact1)
        
class TestCaseServiceAgenda(unittest.TestCase):
    
    def setUp(self):
        with open("test_contact.txt","w") as f:
            f.write("")
        self.repo = FileContactRepository("test_contact.txt")
        
        with open("test_contact_dto.txt","w") as f:
            f.write("")
        self.repo = FileContactDTORepository("test_contact_dto.txt")
        
        self.valid = ValidatorContact()
        self.repo = FileContactRepository("test_contact.txt")
        self.repo1 = FileContactDTORepository("test_contact_dto.txt")
        self.srv = ServiceAgenda(self.repo1,self.repo,self.valid)
        
        self.contact = Contact(4,"Mihai",6534218765,"Familie")
        self.srv.adauga_contact(4,"Mihai",6534218765,"Familie")
        
    
    def test_adauga(self):
        self.srv.adauga_contact(7,"Ariana",3412113211,"Prieteni") 
        self.assertEqual(len(self.repo.get_all()),2)
        
        with self.assertRaises(RepoError):
            self.srv.adauga_contact(67,"Mihai",7654321564, "Job")
            
        with self.assertRaises(ValidError):
            self.srv.adauga_contact(-5,"","", "dsgs")
            
        with self.assertRaises(ValidError):
            self.srv.adauga_contact(5,"aaa","", "")
    
    
    def test_cauta(self):
        self.assertEqual(self.srv.cautare_contact("Mihai"),self.contact)
        
        with self.assertRaises(RepoError):
            self.srv.cautare_contact("Andrei")
    
    def test_contacte_grup(self):
        contact = Contact(5,"Amalia",1234567894,"Familie")
        self.srv.adauga_contact(5,"Amalia",1234567894,"Familie")
        rez = self.srv.contacte_grup("Familie")
        
        self.assertEqual(rez[0],contact)
        self.assertEqual(rez[1],self.contact)
    
    def test_exportare(self):
        pass 
    
        
