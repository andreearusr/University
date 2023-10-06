'''
Created on Feb 1, 2021

@author: Admin
'''

def f2(n):
    if n<=0:
        raise ValueError()
    l = [x for x in range(n-1,-1,-1)]
    print(l)
    for i in range(n-1):
        l[i+1]+=l[i]
    return l[-1]

print(f2(6))
