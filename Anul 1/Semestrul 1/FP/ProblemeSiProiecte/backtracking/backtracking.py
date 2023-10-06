'''
Created on 1 Jan 2021

@author: HP
'''

def cifra_comuna(a,b):
    ok=0
    c= str(b)
    while a>0:
        cifra = a%10
        if str(cifra) in c:
            ok=1
        a=a//10
           
    return ok

def bun(l,sol):
    if len(sol) == 1:
        return True
    return (sol[-1] == sol[-2] + 1) and (l[sol[-2]] <= l[sol[-1]]) and (cifra_comuna(l[sol[-2]], l[sol[-1]]))

def afisare_solutie(l,sol):
    rez=[]
    for el in sol:
        rez.append(l[el])
    print(rez)

def backtracking_iterativ(l):
    sol = [-1] #solutia candidat
    while len(sol) > 0:
        choosed = False
        while not choosed and sol[-1] < len(l) - 1:
            sol[-1] = sol[-1] + 1 #incrementam ultimul component
            choosed = bun(l, sol)
        if choosed:
            if len(sol) >= 2:
                afisare_solutie(l, sol)
            sol.append(-1) #expansiune solutie candidat
        else:
            sol = sol[:-1] #mergem inapoi un component

def backtracking_recursiv(l,sol=[]):
    sol.append(0)  #adaugare component nou la solutia candidat
    for i in range (0,len(l)):
        sol[-1]=i  #setam componentul curent
        if bun(l,sol):
            if len(sol) >= 2:
                afisare_solutie(l, sol)
            backtracking_recursiv(l,sol)  #invocare recursiva pt a ne confrunta cu urmatoarele componente
    sol.pop()
    


l=[11,121,7,3,13,34,45,55,9]
#backtracking_iterativ(l)
backtracking_recursiv(l,sol=[])   