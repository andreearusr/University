'''
Created on Jan 30, 2021

@author: Admin
'''
def suma(l):
    s = 0
    for el in l:
        s = s + el
    return s 

def solution(sol,limit):
    return suma(sol)==limit

def selectMostPromissing(candidates):
    return max(candidates)

def acceptable(element,solution,limit):
    return suma(solution)+element<=limit

def greedy_coins(coins,Sum):
    sol =[]
    while not solution(sol,Sum) and coins!=[]:
        candidat = selectMostPromissing(coins)
        coins.remove(candidat)
        if acceptable(candidat,sol,Sum):
            sol.append(candidat)
            
    if solution(sol,Sum):
        return sol 
    return None

rez = greedy_coins([1, 5, 10, 25, 50], 60)
print(rez)

