'''
Created on 15 Nov 2020

@author: Rus Andreea
'''


from coordonare.appcoord import AppCoord
import unittest
from testare.teste import TestCasePersoanaDomeniu,TestCaseEvenimentDomeniu,TestCaseInscriereDTODomeniu,TestCaseInscrDTODomeniu,\
    TestCaseParticipantDTODomeniu,TestCaseEvenimenteDTODomeniu,TestCaseRepoPersoana,TestCaseRepoEveniment,TestCaseRepoInscriere,\
    TestCaseValidatorPersoana,TestCaseValidatorEveniment,TestCaseValidatorInscriere,TestCaseServicePersoana,\
    TestCaseServiceEveniment,TestCaseServiceInscriere,TestCaseFileRepoPersoana,TestCaseFileRepoEveniment,\
    TestCaseFileRepoInscriere


def suite():
    suite = unittest.TestSuite()
    suite.addTest(TestCasePersoanaDomeniu)
    suite.addTest(TestCaseEvenimentDomeniu)
    suite.addTest(TestCaseInscriereDTODomeniu)
    suite.addTest(TestCaseInscrDTODomeniu)
    suite.addTest(TestCaseParticipantDTODomeniu)
    suite.addTest(TestCaseEvenimenteDTODomeniu)
    suite.addTest(TestCaseRepoPersoana)
    suite.addTest(TestCaseRepoEveniment)
    suite.addTest(TestCaseRepoInscriere)
    suite.addTest(TestCaseValidatorPersoana)
    suite.addTest(TestCaseValidatorEveniment)
    suite.addTest(TestCaseValidatorInscriere)
    suite.addTest(TestCaseServicePersoana)
    suite.addTest(TestCaseServiceEveniment)
    suite.addTest(TestCaseServiceInscriere)
    suite.addTest(TestCaseFileRepoPersoana)
    suite.addTest(TestCaseFileRepoEveniment)
    suite.addTest(TestCaseFileRepoInscriere)
    
    return suite

if __name__ == '__main__':

    appCoord = AppCoord()
    appCoord.start()
    
    runner = unittest.TextTestRunner()
    runner.run(suite())
    