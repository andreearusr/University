
from erori.exceptii import ValidError
class ValidatorPiese(object):
    '''
    Tip de date abstract
    Domeniu: validarea unei piese de teatru, cu datele introduse de catre utilizator
    '''
    
    
    def __init__(self):
        pass
    
    def valideaza(self, piesa):
        '''
        Functie ce verifica daca datele introduse de catre utilizator sunt corecte in functie de cerinte:
            titlu - string, sa nu fie vid
            regizor - string, sa nu fie vid
            gen - string, sa nu fie vid
            durata - int(numar intreg), pozitiv
        Daca nu sunt satisfacute una dintre cerinte => se arunca Valid Error:
            titlu:    Titlu invalid!\n
            regizor:   Regizor invalid!\n
            gen:      Gen invalid!\n
            durata:    Durata negativa!\n
            
        :param piesa - o piesa de teatru
        '''
        
        erori =""
        if piesa.get_titlu()=="":
            erori+= "Titlu invalid!\n"
        if piesa.get_regizor()=="":
            erori+= "Regizor invalid!\n"
        if piesa.get_durata()<1:
            erori+= "Durata negativa!\n"
        if piesa.get_gen()!="Comedie":
            if piesa.get_gen()!="Drama":
                if piesa.get_gen()!="Satira":
                    if piesa.get_gen()!="Altele":
                        erori+= "Gen invalid!\n"
            
        if len(erori)>0:
            raise ValidError(erori)



