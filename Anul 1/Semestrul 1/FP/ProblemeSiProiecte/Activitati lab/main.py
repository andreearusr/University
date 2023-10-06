'''
Created on Jan 29, 2021

@author: Admin
'''

from testare.teste import Teste
from bussiness.servicii import ServiceStudenti, ServiceLaboratoare
from validare.validatori import ValidatorStudenti, ValidatorLaboratoare
from infrastructura.repos import FileRepositoryStudenti, FileRepositoryLaboratoare
from prezentare.consola import UI


if __name__ == '__main__':
    teste = Teste()
    teste.ruleaza_toate_testele()
    
    repo_studenti = FileRepositoryStudenti("studenti.txt")
    validator_studenti = ValidatorStudenti()
    srv_studenti = ServiceStudenti(validator_studenti,repo_studenti)
    
    repo_laboratoare = FileRepositoryLaboratoare("labs.txt")
    validator_laboratoare = ValidatorLaboratoare()
    srv_laboratoare = ServiceLaboratoare(validator_laboratoare,repo_laboratoare,repo_studenti)
    
    cons = UI(srv_studenti,srv_laboratoare)
    cons.run()
    