'''
Created on Jan 31, 2021

@author: Admin
'''

from testare.teste import Teste
from validare.validatori import ValidatorPiese
from bussiness.servicii import ServicePiese
from persistenta.repos import FileRepositoryPiese
from prezentare.consola import UI

if __name__ == '__main__':
    teste = Teste()
    teste.ruleaza_toate_testele()
    
    validator_piese = ValidatorPiese()
    repo_piese = FileRepositoryPiese("piese.txt")
    srv_piese = ServicePiese(repo_piese,validator_piese)
    
    cons = UI(srv_piese)
    cons.run()