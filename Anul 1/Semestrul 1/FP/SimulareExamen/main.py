'''
Created on 9 Dec 2020

@author: HP
'''

from testare.teste import Teste
from business.servicii import ServicePiesa
from infrastructura.repos import FileRepoPiesa
from prezentare.consola import UI

if __name__ == '__main__':
    teste = Teste()
    teste.ruleaza_toate_testele()
    
    repo_piesa = FileRepoPiesa("opere.txt")
    srv_piesa = ServicePiesa(repo_piesa)
    
    cons = UI(srv_piesa)
    cons.run()