'''
Created on Jan 30, 2021

@author: Admin
'''

from testare.teste import TestCaseContactDomeniu,TestCaseContactDTODomeniu,TestCaseValidatorContact,TestCaseRepoContact,\
                        TestCaseFileRepoContact,TestCaseFileRepoContactDTO,TestCaseServiceAgenda
from bussiness.servicii import ServiceAgenda 
from prezentare.consola import UI 
from validare.validatori import ValidatorContact
from infrastructura.repos import FileContactRepository, FileContactDTORepository

import unittest

def suite():
    suite = unittest.TestSuite()
    suite.addTest(TestCaseContactDomeniu)
    suite.addTest(TestCaseContactDTODomeniu)
    suite.addTest(TestCaseValidatorContact)
    suite.addTest(TestCaseRepoContact)
    suite.addTest(TestCaseFileRepoContact)
    suite.addTest(TestCaseFileRepoContactDTO)
    suite.addTest(TestCaseServiceAgenda)
    
    return suite

if __name__ == '__main__':

#     teste = Teste()
#     teste.ruleaza_toate_testele()
    
    repo_contact = FileContactRepository("contacte.txt")
    repo_contact_dto = FileContactDTORepository("csv.txt")
    validator_contact = ValidatorContact()
    srv_agenda = ServiceAgenda(repo_contact_dto, repo_contact,validator_contact)
    
    cons = UI(srv_agenda)
    cons.run()
    
    runner = unittest.TextTestRunner()
    runner.run(suite())
    