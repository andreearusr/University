

from domeniu.entitati import Opera,PiesaDTO
from infrastructura.repos import FileRepoPiesa
from business.servicii import ServicePiesa
from erori.exceptii import RepoError
class Teste(object):
    
    
    def __init__(self):
        pass
    
    def ruleaza_teste_domeniu(self):
        id_opera = 5
        titlu = "Harap-Alb"
        gen = "Basm"
        pret = 30
        opera = Opera(id_opera,titlu,gen,pret)
        assert(opera.get_id_opera()==5)
        assert(opera.get_titlu()=="Harap-Alb")
        assert(opera.get_gen()=="Basm")
        assert(opera.get_pret()==30)
        assert(str(opera)=="id opera:5  titlu:Harap-Alb  gen:Basm  pret:30")
        
        opera1 = Opera(7,"Moara cu noroc","Nuvela",45)
        piesa = PiesaDTO(opera1,550)
        assert(piesa.get_opera()==opera1)
        assert(piesa.get_suma()==550)
        

    def ruleaza_teste_repo(self):
        repo_opere = FileRepoPiesa("test_opere.txt")
        alls = repo_opere.get_all()
        assert(len(alls)==6)
        
        opera = repo_opere.cauta_dupa_id(5)
        assert(str(opera)=="id opera:5  titlu:Harap-Alb  gen:basm  pret:80")
        try:
            repo_opere.cauta_dupa_id(150)
            assert(False)
        except RepoError as re:
            assert(str(re)=="Opera inexistenta!")
        
    def ruleaza_teste_service(self):
        repo_opere = FileRepoPiesa("test_opere.txt")
        srv_opere = ServicePiesa(repo_opere)
        opera = srv_opere.cumpara_bilete(4,3)
        assert(opera.get_suma()==210)
 
    
    def ruleaza_toate_testele(self):
        self.ruleaza_teste_domeniu()
        self.ruleaza_teste_repo()
        self.ruleaza_teste_service()
    


