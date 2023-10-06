    
class GenericSort(object):
    
    def key(self,o1):
        return o1.name 
    
    def rev(self,o2):
        return o2.name
    
        
    def sortare(self, lista,*, algoritm = "Selection Sort", key = None, rev = False):
        
        if rev == False:
            if algoritm == "Selection Sort":
                return GenericSort.selection_sort(self, lista, key , rev )
        
            elif algoritm == "Shell Sort":
                return GenericSort.shell_sort(self, lista, key , rev )
            
        elif rev == True:
            if algoritm == "Selection Sort":
                return GenericSort.selection_sort(self, lista, key , rev )
        
            elif algoritm == "Shell Sort":
                return GenericSort.shell_sort(self, lista, key , rev )
            
            
    def selection_sort(self, lista, key, rev):
        
        for i in range(0,len(lista)-1):
            ind = i
            for j in range(i+1,len(lista)):
                if rev == False:
                    if key(lista[j])<key(lista[ind]):
                        ind = j 
                    if (i<ind):
                        aux = lista[i]
                        lista[i]=lista[ind]
                        lista[ind]=aux 
        
                if rev == True:
                    if key(lista[j])>key(lista[ind]):
                        ind = j 
                    if (i<ind):
                        aux = lista[i]
                        lista[i]=lista[ind]
                        lista[ind]=aux 
        return lista
                      

    def shell_sort(self, lista, key, rev):
        
        n = len(lista)
        interval = n//2
        while interval>0:
            for i in range(int(interval),n):
                temp = lista[i]
                j=i
                if rev == False:
                    while j>=interval and key(lista[int(j-interval)])>key(lista[i]):
                        lista[int(j)]=lista[int(j-interval)]
                        j=int(j-interval)
                        lista[int(j)]=temp
                
                if rev == True:
                    while j>=interval and key(lista[int(j-interval)])<key(temp):
                        lista[i]=lista[int(j-interval)]
                        j=int(j-interval)
                        lista[int(j)]=temp
                interval = interval/2
        return lista
        
        
        
    