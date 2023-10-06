'''
Created on Feb 1, 2021

@author: Admin
'''

from testare.teste import Teste
from validare.validatori import ValidatorMelodie
from persistenta.repos import FileRepositoryMelodie,FileRepositoryMelodiiDTO
from bussiness.servicii import ServiceMelodie
from prezentare.consola import UI

if __name__ == '__main__':
    teste = Teste()
    teste.ruleaza_toate_testele()
    
    validator_melodie = ValidatorMelodie()
    repo_melodie = FileRepositoryMelodie("melodii.txt")
    repo_melodie_dto = FileRepositoryMelodiiDTO("csv.txt")
    srv_melodie = ServiceMelodie(repo_melodie,repo_melodie_dto,validator_melodie)
    
    cons = UI(srv_melodie)
    cons.run()