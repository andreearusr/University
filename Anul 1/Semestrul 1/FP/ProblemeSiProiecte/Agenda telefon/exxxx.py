'''
Created on Jan 30, 2021

@author: Admin
'''

def f(l):
    print("A")
    if l==[]:
        raise ValueError()
    print("B")
    
def start():
    l=[]
    try:
        print("A")
        f(l)
        print("D")
    except ValueError:
        print("C")

start()

class A:
    def f(self,l,nr):
        l.append(nr)
        

class B:
    def g(self,l,nr):
        nr=nr-1
        l=l+[-2]
        
a=A()
b=B()
l=[1,2]

c=-1 
a.f(l,6)
b.g(l,c)
print(l,c)
 
# def S(el):
#     
#     
#     
# def suma_nr_pare(l):
#     
#     try:
#         for el in l:
#             if el%2 == 0:
#                 S(el)
#     except ValueError:
#         print("Nu avem nr pare in lista!") 
#            
# l=[1,3,5,7,9]
# print(suma_nr_pare(l))


def funct(n):
    d=2
    while(d<n-1) and n%d>0: 
        d+=1
    return d>=n-1

assert(funct(5)==1)
assert(funct(4)==0)


def F(a,b,c):
    a=a+1
    b.append(3)
    c=c+[3]
    
a=7 
b=[1,2]
c=[1,2]
F(a,b,c)
print(a,b,c)


def Ff(l):
    if l ==None:
        raise ValueError()
    for e in l:
        if e%2==1:
            return True 
    return False 

assert(Ff([2,6,8,5,8])==True)
assert(Ff([2,6,8,8])==False)


for i in range (5,-1,-1):
    print(i)

