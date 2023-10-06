
from erori.exceptii import ValidError
class ValidatorMelodie(object):
    '''
    Tip de date abstract
    Domeniu: verificarea corectitudinii datelor introduse de catre utilizator
    '''
    
    
    def __init__(self):
        pass
    
    
    def valideaza(self,melodie):
        '''
        Functie care verifica daca datele introduse de catre utilizator respecta cerintele
        :param melodie - o melodie care este formata din :
                titlu - un string, trebuie sa fie nevid
                artist - string, trebuie sa fie nevid 
                gen - string, trebuie sa fie unul dintre: "Rock", "Pop", "Jazz" sau "Altele"
                durata - intreg, trebuie sa fie pozitiv 
        
        Daca nu se respecta cerintele de mai sus => se arunca Valid Error in functie de ce date sunt introduse gresit:
                titlu gresit =>  Titlu invalid!\n
                artist gresit =>   Artist invalid!\n 
                gen gresit =>   Gen invalid!\n
                durata gresita =>   Durata invalida!\n
        '''
        
        erori =""
        if melodie.get_titlu()=="":
            erori+="Titlu invalid!\n"
        if melodie.get_artist()=="":
            erori+= "Artist invalid!\n"
        if melodie.get_gen() != "Rock":
            if melodie.get_gen() != "Pop":
                if melodie.get_gen() != "Jazz":
                    if melodie.get_gen() != "Altele":
                        erori+="Gen invalid!\n"
                        
        if melodie.get_durata()<1:
            erori+="Durata invalida!\n"
            
        if len(erori)>0:
            raise ValidError(erori)
    



