'''
Created on Jan 30, 2021

@author: Admin
'''

# def lista_fin(el):
#     l=[]
#     l.append(el)
 

def suma_nr_pare(l):

    if len(l)==1:
        if l[0]%2==0:  
            return l[0]
        else:
            return 0
        
    mid = int(len(l)/2)
    p1 = suma_nr_pare(l[:mid])
    p2 = suma_nr_pare(l[mid:])
        
    return p1+p2


print(suma_nr_pare([5]))

          
def nr_pare(l):
    if len(l)==1:
        if l[0]%2==0:
            return 1
        else:
            return 0
    mid = int(len(l)/2)
    p1 = nr_pare(l[:mid])
    p2 = nr_pare(l[mid:])
    return p1+p2
    
print(nr_pare([13,15,2]))
