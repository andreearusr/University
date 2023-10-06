'''
Created on Jan 30, 2021

@author: Admin
'''


def longestSublist(a):
    lg=len(a)
    l = [0]*len(a)
    p = [0]*len(a)
    
    l[lg-1] = 1
    p[lg-1] = -1
    for k in range (lg-2,-1,-1):
       # print (p,l) 
        p[k]=-1
        l[k]=1
        
        for i in range(k+1,lg):
            if a[i]>=a[k] and l[k]<l[i]+1:
                l[k]=l[i]+1
                p[k]=i 
    
    j=0
    for i in range(0,lg):
        if l[i]>l[j]:
            j=i 
    
    rez=[]
    while j!= -1:
        rez=rez+[a[j]]
        j=p[j]
    
    return rez 
 
l=[2,7,13,45,78,9,3,5,90,120,234,567,7877]
rezz =longestSublist(l)
print(rezz)





def longestSublistPar(b):
    lg=len(b)
    l = [0]*len(b)
    p = [0]*len(b)
    
    l[lg-1] = 1
    p[lg-1] = -1
    for k in range (lg-2,-1,-1):
        # print (p,l) 
        p[k]=-1
        l[k]=1
        
        for i in range(k+1,lg):
            if b[i]%2 == 0 and b[k]%2==0:
                if l[k]%2==0 and (l[i]+1)%2==0:
                    l[k]=l[i]+1
                    p[k]=i 
    
    j=0
    for i in range(0,lg):
        if l[i]>l[j]:
            j=i 
    
    rez=[]
    while j!= -1:
        rez=rez+[b[j]]
        j=p[j]
    
    return rez 
 
# l=[2,7,13,4,6,11]
# rezz =longestSublistPar(l)
# print(rezz)
