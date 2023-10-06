
from domeniu.entitati import Persoana,Eveniment,Adresa,InscriereDTO,InscrDTO,ParticipantDTO,EvenimenteDTO
from validare.validatori import ValidatorPersoana,ValidatorEveniment,ValidatorInscriere
from infrastructura.repo import RepositoryPersoana,RepositoryEveniment,RepositoryInscriere,\
    FileRepoPersoana, FileRepoEveniment, FileRepoInscriere
from erori.exceptii import ValidError,RepoError
from bussines.servicii import ServicePersoana,ServiceEveniment, ServiceInscriere
import unittest


class TestCasePersoanaDomeniu(unittest.TestCase):

       
    def setUp(self):
        id_persoana = 5
        nume = "Raluca"
        strada = "Somesului"
        numar = 30
        oras = "Cluj-Napoca"
        self.adresa = Adresa(strada,numar,oras)
        self.persoana = Persoana(id_persoana,nume,self.adresa)
        
    def test_getteri(self):
        
        self.assertEqual(self.persoana.get_id_persoana(),5)
        self.assertEqual(self.persoana.get_nume(),"Raluca")
        self.assertEqual(self.persoana.get_adresa().get_strada(),"Somesului")
        self.assertEqual(self.persoana.get_adresa().get_numar(),30)
        self.assertEqual(self.persoana.get_adresa().get_oras(),"Cluj-Napoca")
        self.assertEqual(str(self.persoana),"Id:5  Nume:Raluca  Adresa:Strada:Somesului  Numar:30  Oras:Cluj-Napoca")
        
        persoana1 = Persoana(5,"Raul",Adresa("Somesului", 30, "Cluj-Napoca"))
        self.assertEqual(self.persoana,persoana1)
        
    def test_setteri(self):
        self.persoana.set_nume("Andreea")
        self.adresa.set_strada("Avram Iancu")
        self.adresa.set_numar(11)
        self.adresa.set_oras("Cluj")
        
        self.assertEqual(self.persoana.get_nume(),"Andreea")
        self.assertEqual(self.persoana.get_adresa().get_strada(),"Avram Iancu")
        self.assertEqual(self.persoana.get_adresa().get_numar(),11)
        self.assertEqual(self.persoana.get_adresa().get_oras(),"Cluj")
        self.persoana.set_adresa(Adresa("Avram Iancu",10,"Cluj"))
    
        self.assertEqual(str(self.persoana),"Id:5  Nume:Andreea  Adresa:Strada:Avram Iancu  Numar:10  Oras:Cluj")
        self.assertNotEqual(str(self.persoana),"Id:5  Nume:Andreea  Adresa:Strada:Somesului  Numar:30  Oras:Cluj-Napoca")
        
class TestCaseEvenimentDomeniu(unittest.TestCase):
    
    def setUp(self):
        id_eveniment = 11
        data_eveniment = 23
        timp_eveniment = 5
        descriere_even = "Latino Party"
        self.eveniment = Eveniment(id_eveniment,data_eveniment,timp_eveniment,descriere_even)
        
    def test_getteri(self):
        self.assertTrue(self.eveniment.get_id_eveniment()==11)
        self.assertTrue(self.eveniment.get_data_eveniment()==23)
        self.assertTrue(self.eveniment.get_timp_eveniment()==5)
        self.assertTrue(self.eveniment.get_descriere_even()=="Latino Party")
        self.assertTrue(str(self.eveniment)=="Id:11  Data:23  Durata:5h  Descriere:Latino Party")
        
        eveniment1 = Eveniment(11,23,5,"Kitch Party")
        self.assertEqual(self.eveniment, eveniment1)
        
    def test_setter(self):
        self.eveniment.set_data_eveniment(15)
        self.eveniment.set_timp_eveniment(5.5)
        self.eveniment.set_descriere_even("Latino party")
        
        self.assertTrue(self.eveniment.get_data_eveniment()==15)
        self.assertTrue(self.eveniment.get_timp_eveniment()==5.5)
        self.assertTrue(self.eveniment.get_descriere_even()=="Latino party")
     
        self.assertTrue(str(self.eveniment)=="Id:11  Data:15  Durata:5.5h  Descriere:Latino party")
        self.assertFalse(str(self.eveniment)=="Id:11  Data:15  Durata:5h  Descriere:Latino Party")
        
        
class TestCaseInscriereDTODomeniu(unittest.TestCase):
    
    def setUp(self):
        persoana=Persoana(5,"Ioana",Adresa("Florilor",22,"Dej"))
        nume = persoana.get_nume()
        eveniment = Eveniment(3,7,9,"Nunta")
        descriere_even = eveniment.get_descriere_even()
        id_inscriere = 25
        pret = 900
        self.inscriere = InscriereDTO(id_inscriere,nume,descriere_even,pret)
        
    def test_getteri(self):

        self.assertEqual(self.inscriere.get_id_inscriere(),25)
        self.assertEqual(self.inscriere.get_nume(),"Ioana" )
        self.assertEqual(self.inscriere.get_descriere_even(), "Nunta")
        self.assertEqual(self.inscriere.get_pret(), 900)
        self.assertTrue(str(self.inscriere)=="Id inscriere:25  Nume:Ioana --> Descriere:Nunta  Pret bilet:900 RON")
             
class TestCaseInscrDTODomeniu(unittest.TestCase):
    
    def setUp(self):
        persoana=Persoana(5,"Andrada",Adresa("Florilor",22,"Dej"))
        id_persoana = persoana.get_id_persoana()
        eveniment = Eveniment(3,7,9,"Botez")
        id_eveniment = eveniment.get_id_eveniment()
        id_inscriere = 20
        pret = 500
        self.inscriere = InscrDTO(id_inscriere,id_persoana,id_eveniment,pret)
        
    def test_getteri(self):
        self.assertEqual(self.inscriere.get_id_inscriere(),20)
        self.assertEqual(self.inscriere.get_id_persoana(),5 )
        self.assertEqual(self.inscriere.get_id_eveniment(), 3)
        self.assertEqual(self.inscriere.get_pret(), 500)
        self.assertTrue(str(self.inscriere)=="Id inscriere:20  Id persoana:5  Id eveniment:3  Pret bilet:500 RON")
        
        inscriere1 = InscrDTO(20,7,9,850)
        self.assertEqual(self.inscriere, inscriere1)
    
    
class TestCaseParticipantDTODomeniu(unittest.TestCase):
    
    def test_Create(self):
        
        participant = ParticipantDTO(10,"Bogdan",11)
        self.assertEqual(participant.get_id_persoana(), 10)
        self.assertEqual(participant.get_nume(), "Bogdan")
        self.assertEqual(participant.get_nr_evenimente(), 11)
        
        self.assertTrue(str(participant)=="Id persoana:10  Nume:Bogdan  Numar evenimente:11")
        
class TestCaseEvenimenteDTODomeniu(unittest.TestCase):
    
    def test_Create(self):
       
        eveniment = EvenimenteDTO(15,"Majorat",70)
        self.assertEqual(eveniment.get_id_eveniment(),15)
        self.assertEqual(eveniment.get_descriere_even(),"Majorat")
        self.assertEqual(eveniment.get_nr_participanti(),70)
        
        self.assertTrue(str(eveniment)=="Descriere eveniment:Majorat  Numar participanti:70")
        
    
class TestCaseValidatorPersoana(unittest.TestCase):

    def setUp(self):
        self.valid = ValidatorPersoana()
        
    def test_valideaza(self):
        persoana = Persoana(15,"Iulia",Adresa("Principala",27,"Bistrita"))
        self.valid.valideaza_pers(persoana)
        
        persoana1 = Persoana(-55,"",Adresa("Principala",27,"Bistrita"))
        self.assertRaises(ValidError, self.valid.valideaza_pers, persoana1)
        
        persoana2 = Persoana(2,"Mihai",Adresa("",27,""))
        self.assertRaises(ValidError, self.valid.valideaza_pers, persoana2)
        
        persoana3 = Persoana(12,"",Adresa("Principala",-29,"Bistrita"))
        self.assertRaises(ValidError, self.valid.valideaza_pers, persoana3)
        

class TestCaseValidatorEveniment(unittest.TestCase):
    
    def setUp(self):
        self.valid = ValidatorEveniment()
        
    def test_valideaza(self):
        eveniment = Eveniment(-32,21,1.5,"Concert")
        self.assertRaises(ValidError, self.valid.valideaza_even, eveniment)
        
        eveniment1 = Eveniment(11,89,1.5,"")
        self.assertRaises(ValidError, self.valid.valideaza_even, eveniment1)
        
        eveniment2 = Eveniment(68,-9,-15,"Concert")
        self.assertRaises(ValidError, self.valid.valideaza_even, eveniment2)
        
class TestCaseValidatorInscriere(unittest.TestCase):
      
    def setUp(self):
        self.valid = ValidatorInscriere()
        
    def test_valideaza(self):
        adresa = Adresa("Principala", 123, "Alba")
        Persoana(15,"Mihaela",adresa)
        Eveniment(2,11,1.5,"chestionar")
        
        inscriere = InscrDTO(-12,15,2,350)
        self.assertRaises(ValidError, self.valid.valideaza_inscriere, inscriere)
        
        inscriere = InscrDTO(9,15,2,-900)
        self.assertRaises(ValidError, self.valid.valideaza_inscriere, inscriere)
    
class TestCaseRepoPersoana(unittest.TestCase):
    
    def setUp(self):
        self.repo = RepositoryPersoana()
        self.id_persoana = 21
        self.adresa = Adresa("Republicii", 30, "Campia-Turzii")
        self.persoana = Persoana(self.id_persoana,"Rares",self.adresa)
        self.repo.adauga(self.persoana)
    def tearDown(self):
        pass
    
    def test_len(self):
        self.assertTrue(self.repo.__len__()==1)
        
    def test_adauga(self):
        adresa = Adresa("Pavlov", 22, "Cluj")
        persoana = Persoana(7,"Raluca",adresa)
        self.repo.adauga(persoana)
        self.assertTrue(self.repo.__len__()==2)
        self.assertRaises(RepoError,self.repo.adauga,self.persoana)
    
    def test_cauta(self):
        self.assertEqual(self.repo.cauta_dupa_id(21),self.persoana)
        self.assertRaises(RepoError,self.repo.cauta_dupa_id,26)

    def test_modifica(self):
        adresa = Adresa("Otelarilor", 31, "Campia-Turzii")
        persoana = Persoana(self.id_persoana,"Maria",adresa)
        self.repo.modifica(persoana)
        self.assertEqual(self.persoana.get_nume(),"Maria")
        self.assertEqual(self.persoana.get_adresa(),adresa)
        
        
    def test_get_all(self):
        adresa = Adresa("Pavlov", 22, "Cluj")
        persoana = Persoana(7,"Raluca",adresa)
        self.repo.adauga(persoana)
        
        self.assertEqual(self.repo.__len__(),2)
        alls = self.repo.get_all()
        self.assertEqual(alls[0],self.persoana)
        self.assertEqual(alls[1],persoana)
        
    def test_sterge(self):
        adresa = Adresa("Pavlov", 22, "Cluj")
        persoana = Persoana(7,"Raluca",adresa)
        self.repo.adauga(persoana)
        
        self.repo.sterge_dupa_id(7)
        self.assertEqual(self.repo.__len__(),1)
        self.assertRaises(RepoError,self.repo.sterge_dupa_id,12)
        
        
class TestCaseRepoEveniment(unittest.TestCase):
    
    def setUp(self):
        self.repo = RepositoryEveniment()
        self.id_eveniment = 33
        self.eveniment = Eveniment(self.id_eveniment,15,4.5,"Balul bobocilor")
        self.repo.adauga(self.eveniment)
        
    def tearDown(self):
        pass
    
    def test_len(self):
        self.assertTrue(self.repo.__len__()==1)
        
    def test_adauga(self):
        eveniment = Eveniment(678,13,4,"Discurs")
        self.repo.adauga(eveniment)
        self.assertTrue(self.repo.__len__()==2)
        self.assertRaises(RepoError,self.repo.adauga,self.eveniment)
    
    def test_cauta(self):
        self.assertEqual(self.repo.cauta_dupa_id(33),self.eveniment)
        self.assertRaises(RepoError,self.repo.cauta_dupa_id,78)

    def test_modifica(self):
        eveniment = Eveniment(self.id_eveniment,13,4,"Discurs")
        self.repo.modifica(eveniment)
        self.assertEqual(self.eveniment.get_data_eveniment(),13)
        self.assertEqual(self.eveniment.get_timp_eveniment(),4)
        self.assertEqual(self.eveniment.get_descriere_even(),"Discurs")
        
    def test_get_all(self):
        eveniment = Eveniment(123,22,3,"Test")
        self.repo.adauga(eveniment)
        self.assertEqual(self.repo.__len__(),2)
        alls = self.repo.get_all()
        self.assertEqual(alls[0],self.eveniment)
        self.assertEqual(alls[1],eveniment)
        
    def test_sterge(self):
        self.repo.sterge_dupa_id(self.id_eveniment)
        self.assertEqual(self.repo.__len__(),0)
        self.assertRaises(RepoError,self.repo.sterge_dupa_id,50)
        

class TestCaseRepoInscriere(unittest.TestCase):
    
    def setUp(self):
        self.repo = RepositoryInscriere()
        
        self.id_inscriere = 3
        persoana = Persoana(21,"Rares",Adresa("Somesului", 30, "Cluj-Napoca"))
        id_persoana = persoana.get_id_persoana()
        eveniment = Eveniment(11,23,6.5,"Balroom")
        id_eveniment = eveniment.get_id_eveniment()
        
        self.inscriere = InscrDTO(self.id_inscriere,id_persoana,id_eveniment,150)
        self.repo.adauga(self.inscriere)
        
    def tearDown(self):
        pass
    
    def test_len(self):
        self.assertTrue(self.repo.__len__()==1)
        
    def test_adauga(self):
        id_inscriere = 7
        persoana = Persoana(45,"Rares",Adresa("Frunzisului", 30, "Arad"))
        id_persoana = persoana.get_id_persoana()
        eveniment = Eveniment(90,17,5,"Balroom")
        id_eveniment = eveniment.get_id_eveniment()
        inscriere = InscrDTO(id_inscriere,id_persoana,id_eveniment,350)
        self.repo.adauga(inscriere)
        
        self.assertTrue(self.repo.__len__()==2)
        self.assertRaises(RepoError,self.repo.adauga,self.inscriere)
    
    def test_cauta(self):
        self.assertEqual(self.repo.cauta_dupa_id(3),self.inscriere)
        self.assertRaises(RepoError,self.repo.cauta_dupa_id,99)

    def test_get_all(self):
        Persoana(9,"Radu",Adresa("Bujorului", 30, "Brasov"))
        Eveniment(15,20,2,"Protest")
        inscriere = InscrDTO(89,9,15,30)
        self.repo.adauga(inscriere)
        self.assertEqual(self.repo.__len__(),2)
        alls = self.repo.get_all()
        self.assertEqual(alls[0],self.inscriere)
        self.assertEqual(alls[1],inscriere)
        
    def test_sterge(self):
        self.repo.sterge_inscriere_dupa_id(self.id_inscriere)
        self.assertEqual(self.repo.__len__(),0)
        self.assertRaises(RepoError,self.repo.sterge_inscriere_dupa_id,57)
        
class TestCaseFileRepoPersoana(unittest.TestCase):
    
    def setUp(self):
        with open("test_persoane.txt","w") as f:
            f.write("")
        self.repo = FileRepoPersoana("test_persoane.txt")

    def test_adauga(self):
        adresa = Adresa("Pavlov", 22, "Cluj")
        persoana = Persoana(7,"Raluca",adresa)
        self.repo.adauga(persoana)
        self.assertEqual(self.repo.__len__(),1)
        self.assertRaises(RepoError,self.repo.adauga,persoana)
        self.assertEqual(self.repo.__len__(),1)
    
    def test_cauta(self):
        adresa = Adresa("Pavlov", 22, "Cluj")
        persoana = Persoana(7,"Raluca",adresa)
        self.repo.adauga(persoana)
        self.assertEqual(str(self.repo.cauta_dupa_id(7)),"Id:7  Nume:Raluca  Adresa:Strada:Pavlov  Numar:22  Oras:Cluj")
        self.assertRaises(RepoError,self.repo.cauta_dupa_id,26)
      
    def test_sterge(self):
        adresa = Adresa("Pavlov", 22, "Cluj")
        persoana = Persoana(7,"Raluca",adresa)
        self.repo.adauga(persoana)
        self.repo.sterge_dupa_id(7)
        self.assertEqual(self.repo.__len__(),0)
        self.assertRaises(RepoError,self.repo.sterge_dupa_id,12)
        
    def test_modifica(self):
        adresa = Adresa("Pavlov", 22, "Cluj")
        persoana = Persoana(7,"Raluca",adresa)
        self.repo.adauga(persoana)
        
        adresa1 = Adresa("Principala", 15, "Campia")
        persoana1 = Persoana(7,"Andreea",adresa1)
        self.repo.modifica(persoana1)
        
        persoana_noua = self.repo.cauta_dupa_id(persoana.get_id_persoana())
        self.assertEqual(persoana_noua, persoana1)
       
    
        
    def test_get_all(self):
        adresa = Adresa("Pavlov", 22, "Cluj")
        persoana = Persoana(7,"Raluca",adresa)
        self.repo.adauga(persoana)
        
        adresa1 = Adresa("Principala", 15, "Campia")
        persoana1 = Persoana(9,"Andreea",adresa1)
        self.repo.adauga(persoana1)
        alls = self.repo.get_all()
        self.assertEqual(alls[0],persoana)
        self.assertEqual(alls[1],persoana1)
        
        
        
class TestCaseFileRepoEveniment(unittest.TestCase):
    
    def setUp(self):
        with open("test_evenimente.txt","w") as f:
            f.write("")
        self.repo = FileRepoEveniment("test_evenimente.txt")

    def test_adauga(self):
        eveniment = Eveniment(678,13,4,"Discurs")
        self.repo.adauga(eveniment)
        self.assertEqual(self.repo.__len__(),1)
        self.assertRaises(RepoError,self.repo.adauga,eveniment)
        self.assertEqual(self.repo.__len__(),1)
    
    def test_cauta(self):
        eveniment = Eveniment(678,13,4,"Discurs")
        self.repo.adauga(eveniment)
        self.assertEqual(str(self.repo.cauta_dupa_id(678)),"Id:678  Data:13  Durata:4.0h  Descriere:Discurs")
        self.assertRaises(RepoError,self.repo.cauta_dupa_id,26)
      
    def test_sterge(self):
        eveniment = Eveniment(678,13,4,"Discurs")
        self.repo.adauga(eveniment)
        self.repo.sterge_dupa_id(678)
        self.assertEqual(self.repo.__len__(),0)
        self.assertRaises(RepoError,self.repo.sterge_dupa_id,12)
        
    def test_modifica(self):
        eveniment = Eveniment(678,13,4,"Discurs")
        self.repo.adauga(eveniment)
        
        eveniment1 = Eveniment(678,10,3,"Aniversare")
        self.repo.modifica(eveniment1)
        
        eveniment_modificat = self.repo.cauta_dupa_id(eveniment.get_id_eveniment())
        self.assertEqual(eveniment, eveniment_modificat)
        
        
    def test_get_all(self):
        eveniment = Eveniment(678,13,4,"Discurs")
        self.repo.adauga(eveniment)
        
        eveniment1 = Eveniment(55,10,3,"Aniversare")
        self.repo.adauga(eveniment1)
        alls = self.repo.get_all()
        self.assertEqual(alls[0],eveniment)
        self.assertEqual(alls[1],eveniment1)
        
class TestCaseFileRepoInscriere(unittest.TestCase):
    
    def setUp(self):
        with open("test_inscrieri.txt","w") as f:
            f.write("")
        self.repo = FileRepoInscriere("test_inscrieri.txt")
        
    def test_adauga(self):
        id_inscriere = 7
        persoana = Persoana(45,"Rares",Adresa("Frunzisului", 30, "Arad"))
        id_persoana = persoana.get_id_persoana()
        eveniment = Eveniment(90,17,5,"Balroom")
        id_eveniment = eveniment.get_id_eveniment()
        inscriere = InscrDTO(id_inscriere,id_persoana,id_eveniment,350)
        self.repo.adauga(inscriere)
        
        self.assertTrue(self.repo.__len__()==1)
        self.assertRaises(RepoError,self.repo.adauga,inscriere)
    
    def test_cauta(self):
        id_inscriere = 7
        persoana = Persoana(45,"Rares",Adresa("Frunzisului", 30, "Arad"))
        id_persoana = persoana.get_id_persoana()
        eveniment = Eveniment(90,17,5,"Balroom")
        id_eveniment = eveniment.get_id_eveniment()
        inscriere = InscrDTO(id_inscriere,id_persoana,id_eveniment,350)
        self.repo.adauga(inscriere)
        
        self.assertEqual(str(self.repo.cauta_dupa_id(7)),"Id inscriere:7  Id persoana:45  Id eveniment:90  Pret bilet:350.0 RON")
        self.assertRaises(RepoError,self.repo.cauta_dupa_id,26)
    
    def test_sterge(self):
        id_inscriere = 7
        persoana = Persoana(45,"Rares",Adresa("Frunzisului", 30, "Arad"))
        id_persoana = persoana.get_id_persoana()
        eveniment = Eveniment(90,17,5,"Balroom")
        id_eveniment = eveniment.get_id_eveniment()
        inscriere = InscrDTO(id_inscriere,id_persoana,id_eveniment,350)
        self.repo.adauga(inscriere)
        
        self.repo.sterge_inscriere_dupa_id(7)
        self.assertEqual(self.repo.__len__(),0)
        self.assertRaises(RepoError,self.repo.sterge_inscriere_dupa_id,67)
    
    def test_get_all(self):
        id_inscriere = 7
        persoana = Persoana(45,"Rares",Adresa("Frunzisului", 30, "Arad"))
        id_persoana = persoana.get_id_persoana()
        eveniment = Eveniment(90,17,5,"Balroom")
        id_eveniment = eveniment.get_id_eveniment()
        inscriere = InscrDTO(id_inscriere,id_persoana,id_eveniment,350)
        self.repo.adauga(inscriere)
        
        id_inscriere1 = 9
        persoana1 = Persoana(6,"Catalin",Adresa("Baritiu", 30, "Arad"))
        id_persoana1 = persoana1.get_id_persoana()
        eveniment1 = Eveniment(78,13,2,"Speech")
        id_eveniment1 = eveniment1.get_id_eveniment()
        inscriere1 = InscrDTO(id_inscriere1,id_persoana1,id_eveniment1,45)
        self.repo.adauga(inscriere1)
        
        alls = self.repo.get_all()
        self.assertEqual(alls[0],inscriere)
        self.assertEqual(alls[1],inscriere1)
        
        

class TestCaseServicePersoana(unittest.TestCase):
    
    def setUp(self):
        self.valid = ValidatorPersoana()
        self.repo = RepositoryPersoana()
        self.srv = ServicePersoana(self.valid,self.repo)
        
        self.id_persoana = 67
        self.persoana= Persoana(self.id_persoana,"Andrei",Adresa("Sperantei", 11, "Timisoara"))
        self.srv.adauga_persoana(self.id_persoana,"Andrei",Adresa("Sperantei", 11, "Timisoara"))
    
    def tearDown(self):
        pass
    
    def test_adauga(self):
        self.srv.adauga_persoana(33,"Alex",Adresa("Sperantei", 45, "Brasov"))
        self.assertEqual(self.repo.__len__(),2)
        
        with self.assertRaises(RepoError):
            self.srv.adauga_persoana(67,"Adela",Adresa("Prahovei", 45, "Prahova"))
        
        with self.assertRaises(ValidError):
            self.srv.adauga_persoana(30,"",Adresa("Bucegi", -21, ""))
        with self.assertRaises(ValidError):
            self.srv.adauga_persoana(-45,"",Adresa("", 2, "Bucovina"))
            
    def test_get_persoane(self):
        persoana = Persoana(12,"Andreea",Adresa("Frunzisului", 11, "Arges"))
        self.srv.adauga_persoana(12,"Andreea",Adresa("Frunzisului", 11, "Arges"))
        alls  = self.srv.get_persoane()
        self.assertEqual(alls[0],self.persoana)
        self.assertEqual(alls[1],persoana)
     
    def test_modifica(self):
        persoana = Persoana( -22,"",Adresa("",41,"Vrancea"))
        with self.assertRaises(ValidError):
            self.srv.modifica_persoana(persoana)
            
        persoana1 = Persoana( 19,"Strada",Adresa("Observatorului",-1,""))
        with self.assertRaises(ValidError):
            self.srv.modifica_persoana(persoana1)
                 
    def test_cauta(self):
        self.assertEqual(self.srv.cauta_persoana(self.id_persoana),self.persoana)
        
        with self.assertRaises(ValidError):
            self.srv.cauta_persoana(-55)
        with self.assertRaises(RepoError):
            self.srv.cauta_persoana(345)
            
    
class TestCaseServiceEveniment(unittest.TestCase):
    
    def setUp(self):
        self.valid = ValidatorEveniment()
        self.repo = RepositoryEveniment()
        self.srv = ServiceEveniment(self.valid,self.repo)
        
        self.id_eveniment = 22
        self.eveniment= Eveniment(self.id_eveniment,22,4.5,"Revelion")
        self.srv.adauga_eveniment(self.id_eveniment, 22, 4.5, "Revelion")
        
    def tearDown(self):
        pass
    
    def test_adauga(self):
        self.srv.adauga_eveniment(26, 22, 4.5, "Revelion")
        self.assertEqual(self.repo.__len__(),2)
        
        with self.assertRaises(RepoError):
            self.srv.adauga_eveniment(22, 13, 4.5, "Revelion")
            
        with self.assertRaises(ValidError):
            self.srv.adauga_eveniment(-2,24,0,"")
        with self.assertRaises(ValidError):
            self.srv.adauga_eveniment(11,-67,-2,"Craciun")
            
    def test_get_evenimente(self):
        eveniment = Eveniment(12,6,5,"Balroom")
        self.srv.adauga_eveniment(12,6,5,"Balroom")
        alls  = self.srv.get_evenimente()
        self.assertEqual(alls[0],self.eveniment)
        self.assertEqual(alls[1],eveniment)
     
    def test_modifica(self):
        eveniment1 = Eveniment(-30,20,-2,"Magie")
        with self.assertRaises(ValidError):
            self.srv.modifica_eveniment(eveniment1)
            
        eveniment2 = Eveniment(17,32,9,"")
        with self.assertRaises(ValidError):
            self.srv.modifica_eveniment(eveniment2)
            
        eveniment3 = Eveniment(0,-5,0,"Bal")
        with self.assertRaises(ValidError):
            self.srv.modifica_eveniment(eveniment3)
              
    def test_cauta(self):
        self.assertEqual(self.srv.cauta_eveniment(self.id_eveniment),self.eveniment)
        
        with self.assertRaises(ValidError):
            self.srv.cauta_eveniment(-55)
            
        with self.assertRaises(RepoError):
            self.srv.cauta_eveniment(254)
 
 
class TestCaseServiceInscriere(unittest.TestCase):
    
    def setUp(self):
        valid = ValidatorInscriere()
        self.repo = RepositoryInscriere()
        self.repo1 = RepositoryPersoana()
        self.repo2 = RepositoryEveniment()
        self.srv = ServiceInscriere(valid,self.repo,self.repo1,self.repo2)
        
        self.id_inscriere = 5
        adresa = Adresa("Bucovinei", 45, "Bistrita")
        self.persoana = Persoana(11,"Cristian",adresa)
        self.id_persoana = self.persoana.get_id_persoana()
        self.repo1.adauga(self.persoana)
        self.eveniment = Eveniment(9,4,3,"Discurs scoala")
        self.id_eveniment = self.eveniment.get_id_eveniment()
        self.repo2.adauga(self.eveniment)
        pret = 15
        self.srv.adauga_inscriere(self.id_inscriere,self.id_persoana,self.id_eveniment, pret)
        
    def tearDown(self):
        pass
    
    def test_adauga(self):
        id_inscriere = 9
        persoana = Persoana(9,"Marius",Adresa("Bucovinei", 38, "Bistrita"))
        id_persoana = persoana.get_id_persoana()
        self.repo1.adauga(persoana)
        eveniment = Eveniment(7,2,3,"Discurs scoala")
        id_eveniment = eveniment.get_id_eveniment()
        self.repo2.adauga(eveniment)
        pret = 250
        self.srv.adauga_inscriere(id_inscriere,id_persoana,id_eveniment, pret)
        
        self.assertEqual(self.repo.__len__(),2 )
        
        with self.assertRaises(RepoError):
            self.srv.adauga_inscriere(5, 78, 67, 150)
            
        with self.assertRaises(ValidError):
            self.srv.adauga_inscriere(-45,11,9,-10)
        
        with self.assertRaises(ValidError):
            self.srv.adauga_inscriere(0,11,9,0)
            
    def test_get_inscrieri(self):
        id_inscriere = 9
        persoana = Persoana(9,"Marius",Adresa("Bucovinei", 38, "Bistrita"))
        id_persoana = persoana.get_id_persoana()
        self.repo1.adauga(persoana)
        eveniment = Eveniment(15,9,3,"Discurs scoala")
        id_eveniment = eveniment.get_id_eveniment()
        self.repo2.adauga(eveniment)
        pret = 250
        self.srv.adauga_inscriere(id_inscriere,id_persoana,id_eveniment, pret)
        
        self.assertEqual(self.repo.__len__(),2 )
        alls = self.srv.get_inscrieri()
        self.assertTrue(str(alls[0])=="Id inscriere:5  Nume:Cristian --> Descriere:Discurs scoala  Pret bilet:15 RON")
        self.assertTrue(str(alls[1])=="Id inscriere:9  Nume:Marius --> Descriere:Discurs scoala  Pret bilet:250 RON")
    
    def test_sterge_persoana_inscriere(self):
        self.srv.sterge_persoana_inscriere(self.id_persoana)
        self.assertEqual(self.repo.__len__(),0)
        self.assertEqual(self.repo1.__len__(),0)
    
    def test_sterge_eveniment_inscriere(self):
        self.srv.sterge_eveniment(self.id_eveniment)
        self.assertEqual(self.repo.__len__(),0)
        self.assertEqual(self.repo2.__len__(),0)
    
    def test_ordonare_lista_ev(self):
        eveniment = Eveniment(89,16,4,"Creativitate")
        id_eveniment = eveniment.get_id_eveniment()
        self.repo2.adauga(eveniment)
        pret = 60
        id_inscriere = 57
        self.srv.adauga_inscriere(id_inscriere,self.id_persoana,id_eveniment, pret)
        
        alls = self.srv.ordonare_lista_evenimente_persoana(self.id_persoana)
        self.assertEqual(alls[0],eveniment)
        self.assertEqual(alls[1],self.eveniment)
        
        with self.assertRaises(RepoError):
            self.srv.ordonare_lista_evenimente_persoana(67)
            
    def test_pers_multe_ev(self):
        eveniment = Eveniment(89,16,4,"Creativitate")
        id_eveniment = eveniment.get_id_eveniment()
        self.repo2.adauga(eveniment)
        pret = 60
        id_inscriere = 57
        self.srv.adauga_inscriere(id_inscriere,self.id_persoana,id_eveniment, pret)
        
        eveniment1 = Eveniment(33,4,2,"Spectacol")
        id_eveniment1 = eveniment1.get_id_eveniment()
        self.repo2.adauga(eveniment1)
        pret = 60
        id_inscriere1 = 87
        self.srv.adauga_inscriere(id_inscriere1,self.id_persoana,id_eveniment1, pret)
    
        id_inscriere2 = 9
        persoana = Persoana(9,"Marius",Adresa("Bucovinei", 38, "Bistrita"))
        id_persoana = persoana.get_id_persoana()
        self.repo1.adauga(persoana)
        eveniment2 = Eveniment(15,9,3,"Discurs scoala")
        id_eveniment2 = eveniment.get_id_eveniment()
        self.repo2.adauga(eveniment2)
        pret2 = 250
        id_inscriere3 = 1
        self.srv.adauga_inscriere(id_inscriere2,id_persoana,id_eveniment2, pret)
        self.srv.adauga_inscriere(id_inscriere3,id_persoana,id_eveniment1, pret2)
        
        rez = self.srv.persoane_multe_evenimente()
        self.assertTrue(rez[0].get_id_persoana()==self.id_persoana)
        self.assertTrue(rez[0].get_nume()=="Cristian")
        self.assertTrue(rez[0].get_nr_evenimente()==3)
        
        id_inscriere4 = 2
        self.srv.adauga_inscriere(id_inscriere4,id_persoana,id_eveniment2, pret)
        
        rez1 = self.srv.persoane_multe_evenimente()
        self.assertTrue(rez1[0].get_id_persoana()==self.id_persoana)
        self.assertTrue(rez1[0].get_nume()=="Cristian")
        self.assertTrue(rez1[0].get_nr_evenimente()==3)
        self.assertTrue(rez1[1].get_id_persoana()==id_persoana)
        self.assertTrue(rez1[1].get_nume()=="Marius")
        self.assertTrue(rez1[1].get_nr_evenimente()==3)
    
    def test_ev_nr_particip(self):
        id_inscriere = 9
        persoana = Persoana(9,"Marius",Adresa("Bucovinei", 38, "Bistrita"))
        id_persoana = persoana.get_id_persoana()
        self.repo1.adauga(persoana)
        pret = 250
        self.srv.adauga_inscriere(id_inscriere,id_persoana,self.id_eveniment, pret)
        
        id_inscriere1 = 12
        persoana1 = Persoana(17,"Mihai",Adresa("Frunzisului", 24, "Bistrita"))
        id_persoana1 = persoana1.get_id_persoana()
        self.repo1.adauga(persoana1)
        eveniment1 = Eveniment(15,9,3,"Discurs scoala")
        id_eveniment1 = eveniment1.get_id_eveniment()
        self.repo2.adauga(eveniment1)
        pret1 = 60
        self.srv.adauga_inscriere(id_inscriere1,id_persoana1,id_eveniment1, pret1)
        
        alls = self.srv.evenimente_nr_participanti(1, 7)
        self.assertEqual(alls[0],self.eveniment)
        self.assertEqual(alls[1],eveniment1)
        

    def test_ev_particip(self):
        
        id_inscriere = 9
        persoana = Persoana(9,"Marius",Adresa("Bucovinei", 38, "Bistrita"))
        id_persoana = persoana.get_id_persoana()
        self.repo1.adauga(persoana)
        pret = 250
        self.srv.adauga_inscriere(id_inscriere,id_persoana,self.id_eveniment, pret)
        
        eveniment = Eveniment(7,2,3,"Discurs scoala")
        id_eveniment = eveniment.get_id_eveniment()
        self.repo2.adauga(eveniment)
        
        self.assertEqual(self.srv.evenimente_participanti(id_eveniment),0)
        self.assertEqual(self.srv.evenimente_participanti(self.id_eveniment),2)
        
        
            
    def test_ev_multi_particip(self):
        eveniment1 = Eveniment(1,22,6,"Pool party")
        eveniment2 = Eveniment(2,4,5,"Balroom")
        eveniment3 = Eveniment(3,13,7.5,"Revelion")
        eveniment4 = Eveniment(4,15,5.3,"Balul bobocilor")
        eveniment5 = Eveniment(5,30,4,"Reggaeton party")
        eveniment6 = Eveniment(6,25,5.6,"Haloween party")
        eveniment7 = Eveniment(7,10,2,"Serbare")
        eveniment8 = Eveniment(8,11,3.5,"Aniversare")
        eveniment9 = Eveniment(11,7,6,"Nunta")
        eveniment10 = Eveniment(10,23,5,"Botez")
        
        persoana1 = Persoana(1,"Andreea",Adresa("Pavlov",15,"Cluj"))
        persoana2 = Persoana(21,"Andrei",Adresa("Otelarilor",24,"Campia-Turzii"))
        persoana3 = Persoana(5,"Raluca",Adresa("Florilor",50,"Gherla"))
        persoana4 = Persoana(17,"Mihai",Adresa("Avram Iancu",37,"Cluj"))
        persoana5 = Persoana(33,"Adrian",Adresa("Principala",67,"Bistrita"))
        self.repo1.adauga(persoana1)
        self.repo1.adauga(persoana2)
        self.repo1.adauga(persoana3)
        self.repo1.adauga(persoana4)
        self.repo1.adauga(persoana5)

        self.repo2.adauga(eveniment1)
        self.repo2.adauga(eveniment2)
        self.repo2.adauga(eveniment3)
        self.repo2.adauga(eveniment4)
        self.repo2.adauga(eveniment5)
        self.repo2.adauga(eveniment6)
        self.repo2.adauga(eveniment7)
        self.repo2.adauga(eveniment8)
        self.repo2.adauga(eveniment9)
        self.repo2.adauga(eveniment10)
        id_inscriere1 = 1
        id_inscriere2 = 2
        id_inscriere3 = 3
        id_inscriere4 = 4
        id_inscriere5 = 14
        id_inscriere6 = 6
        id_inscriere7 = 7
        id_inscriere8 = 8
        id_inscriere9 = 9
        id_inscriere10 = 10
        id_inscriere11 = 11
        id_inscriere12 = 12
        id_inscriere13 = 13
        pret_inscriere1 = 40
        pret_inscriere2 = 150
        pret_inscriere3 = 230
        pret_inscriere4 = 700
        pret_inscriere5 = 200
        self.srv.adauga_inscriere(id_inscriere1,persoana1.get_id_persoana(),eveniment1.get_id_eveniment(), pret_inscriere3)
        self.srv.adauga_inscriere(id_inscriere2,persoana2.get_id_persoana(),eveniment4.get_id_eveniment(), pret_inscriere2)
        self.srv.adauga_inscriere(id_inscriere3,persoana3.get_id_persoana(),eveniment1.get_id_eveniment(), pret_inscriere1)
        self.srv.adauga_inscriere(id_inscriere4,persoana4.get_id_persoana(),eveniment3.get_id_eveniment(), pret_inscriere4)
        self.srv.adauga_inscriere(id_inscriere5,persoana5.get_id_persoana(),eveniment6.get_id_eveniment(), pret_inscriere5)
        self.srv.adauga_inscriere(id_inscriere6,persoana2.get_id_persoana(),eveniment9.get_id_eveniment(), pret_inscriere1)
        self.srv.adauga_inscriere(id_inscriere7,persoana5.get_id_persoana(),eveniment2.get_id_eveniment(), pret_inscriere2)
        self.srv.adauga_inscriere(id_inscriere8,persoana1.get_id_persoana(),eveniment7.get_id_eveniment(), pret_inscriere5)
        self.srv.adauga_inscriere(id_inscriere9,persoana3.get_id_persoana(),eveniment10.get_id_eveniment(), pret_inscriere4)
        self.srv.adauga_inscriere(id_inscriere10,persoana2.get_id_persoana(),eveniment5.get_id_eveniment(), pret_inscriere3)
        self.srv.adauga_inscriere(id_inscriere11,persoana1.get_id_persoana(),eveniment8.get_id_eveniment(), pret_inscriere3)
        self.srv.adauga_inscriere(id_inscriere12,persoana3.get_id_persoana(),eveniment1.get_id_eveniment(), pret_inscriere4)
        self.srv.adauga_inscriere(id_inscriere13,persoana5.get_id_persoana(),eveniment2.get_id_eveniment(), pret_inscriere2)
    
        rezultat = self.srv.evenimente_multi_participanti()
        self.assertEqual(rezultat[0].get_nr_participanti(), 3)
        self.assertEqual(rezultat[1].get_nr_participanti(), 2)
        
#if __name__ == '__main__':
#    unittest.main()
    

