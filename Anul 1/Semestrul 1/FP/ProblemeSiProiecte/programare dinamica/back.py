'''
Created on Jan 30, 2021

@author: Admin
'''

nr_sol =0
def e_prim(el):
    if el ==2:
        return True 
    if el <=1 or not (el%2):
        return False 
    div = 3
    while div<el :
        if el%div == 0:
            return False 
        div = div + 1
    return True

def afisare_solutie(sol):

    for i in range(0,len(sol)-1):
        print(sol[i])
    print(sol[-1])
    
def backtracking_recursiv(nr,sum, sol=[]):
    for el in range (0,nr):
        if e_prim(el):
            sol.append(el)
            sum+=el 
            if sum==nr:
                afisare_solutie(sol)
            elif sum < nr:
                backtracking_recursiv(nr,sum, sol)  #invocare recursiva pt a ne confrunta cu urmatoarele componente
            sum-=el
            sol.pop()
    
backtracking_recursiv(15, 0, sol=[])