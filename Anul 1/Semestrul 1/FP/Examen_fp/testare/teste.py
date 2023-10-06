
from domeniu.entitati import Melodie, MelodieDTO
from validare.validatori import ValidatorMelodie
from erori.exceptii import ValidError, RepoError
from persistenta.repos import FileRepositoryMelodie
from bussiness.servicii import ServiceMelodie


class Teste(object):
    
    
    def __init__(self):
        pass

    
    def __ruleaza_teste_domeniu(self):
        titlu = "Aroma"
        artist = "Antonia"
        gen = "Pop"
        durata = 120
        
        melodie = Melodie(titlu,artist,gen,durata)
        assert(melodie.get_titlu()=="Aroma")
        assert(melodie.get_artist()=="Antonia")
        assert(melodie.get_gen()=="Pop")
        assert(melodie.get_durata()==120)
        assert(str(melodie)=="Titlu:Aroma  Artist:Antonia  Gen:Pop  Durata:120")
        
        melodie.set_titlu("Vara")
        melodie.set_artist("Nicole")
        melodie.set_gen("Altele")
        melodie.set_durata(180)
        
        assert(melodie.get_titlu()=="Vara")
        assert(melodie.get_artist()=="Nicole")
        assert(melodie.get_gen()=="Altele")
        assert(melodie.get_durata()==180)
        
        
        titlu = "Toamna"
        artist = "Mira"
        gen = "Jazz"
        durata = 200
        
        melodie_dto = MelodieDTO(artist,titlu,durata,gen)
        assert(melodie_dto.get_titlu()=="Toamna")
        assert(melodie_dto.get_artist()=="Mira")
        assert(melodie_dto.get_gen()=="Jazz")
        assert(melodie_dto.get_durata()==200)
        
    
    
    def __ruleaza_teste_validatori(self):
        validator_melodie = ValidatorMelodie()
        titlu = "Aroma"
        artist = "Antonia"
        gen = "Pop"
        durata = 120
        
        melodie = Melodie(titlu,artist,gen,durata)
        validator_melodie.valideaza(melodie)
        
        try:
            validator_melodie.valideaza(Melodie("","Alex Velea","",-5))
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="Titlu invalid!\nGen invalid!\nDurata invalida!\n")
        
        try:
            validator_melodie.valideaza(Melodie("La mare","","Manele",0))
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="Artist invalid!\nGen invalid!\nDurata invalida!\n")
    
    
    def __ruleaza_teste_repo(self):
        with open("test_melodii.txt","w") as f:
            f.write("")
            
        repo_melodii = FileRepositoryMelodie("test_melodii.txt")   
        assert(len(repo_melodii.get_all())==0) 
        titlu = "Aroma"
        artist = "Antonia"
        gen = "Pop"
        durata = 120
        melodie = Melodie(titlu,artist,gen,durata)
        repo_melodii.adauga(melodie)
        
        assert(len(repo_melodii.get_all())==1)
        repo_melodii.adauga(Melodie("Vacanta","Alexandra","Jazz",200))
        assert(len(repo_melodii.get_all())==2)
        
        melodie1 = repo_melodii.cauta("Aroma", "Antonia")
        assert(str(melodie1)=="Titlu:Aroma  Artist:Antonia  Gen:Pop  Durata:120")
        
        try:
            repo_melodii.cauta("Cirese", "Mihai")
            assert(False)
        except RepoError as re:
            assert(str(re)=="Melodie inexistenta!\n")
            
            
        repo_melodii.modifica(Melodie("Aroma","Antonia","Altele",180))
        melodie_f = repo_melodii.cauta("Aroma","Antonia")
        assert(melodie_f.get_gen()=="Altele")
        assert(melodie_f.get_durata()==180)
        
 
    def __ruleaza_teste_service(self):
        with open("test_melodii.txt","w") as f:
            f.write("")
        with open("test_melodii_dto.txt","w") as f:
            f.write("")    
            
        validator_melodii = ValidatorMelodie()
        repo_melodii = FileRepositoryMelodie("test_melodii.txt")
        repo_melodie_dto = FileRepositoryMelodie("test_melodii_dto.txt")
        srv_melodii = ServiceMelodie(repo_melodii,repo_melodie_dto,validator_melodii)
        
        srv_melodii.adauga("Vacanta","Alexandra","Jazz",200)
        assert(len(repo_melodii.get_all())==1)
        melodie = srv_melodii.cauta_melodie("Vacanta","Alexandra")
        assert(str(melodie)=="Titlu:Vacanta  Artist:Alexandra  Gen:Jazz  Durata:200")
        srv_melodii.modificare_melodie(Melodie("Vacanta","Alexandra","Rock",150))
        melodie_f = srv_melodii.cauta_melodie("Vacanta","Alexandra")
        assert(melodie_f.get_gen()=="Rock")
        assert(melodie_f.get_durata()==150)
        
    
    def ruleaza_toate_testele(self):
        self.__ruleaza_teste_domeniu()
        self.__ruleaza_teste_validatori()
        self.__ruleaza_teste_repo()
        self.__ruleaza_teste_service()
    
    
    
    



