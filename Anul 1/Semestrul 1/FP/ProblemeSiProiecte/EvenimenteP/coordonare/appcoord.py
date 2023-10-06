from infrastructura.repo import RepositoryPersoana, RepositoryEveniment,\
    RepositoryInscriere,FileRepoPersoana,FileRepoEveniment,FileRepoInscriere
from validare.validatori import ValidatorPersoana, ValidatorEveniment, ValidatorInscriere
from bussines.servicii import ServicePersoana, ServiceEveniment, ServiceInscriere
from prezentare.consola import UI
class AppCoord(object):
    
    def __init__(self):
        pass
    
    def start(self):
        while True:
            metoda = input("Alegeti metoda dorita: memorie sau fisier?  ")
            if metoda =="memorie":
                repo_persoana = RepositoryPersoana()
                repo_eveniment = RepositoryEveniment()
                repo_inscriere = RepositoryInscriere()
            elif metoda =="fisier":
                repo_persoana = FileRepoPersoana("persoane.txt")
                repo_eveniment = FileRepoEveniment("evenimente.txt")
                repo_inscriere = FileRepoInscriere("inscrieri.txt")
            else:
                print("Metoda aleasa inexistenta! ")
                continue
            
            
            validator_persoana = ValidatorPersoana()
            validator_eveniment = ValidatorEveniment()
            validator_inscriere = ValidatorInscriere()
            srv_persoana = ServicePersoana(validator_persoana, repo_persoana)
            srv_eveniment = ServiceEveniment(validator_eveniment, repo_eveniment)
            srv_inscriere = ServiceInscriere(validator_inscriere, repo_inscriere, repo_persoana, repo_eveniment)
            
            cons = UI(srv_persoana, srv_eveniment, srv_inscriere)
            cons.run()
            