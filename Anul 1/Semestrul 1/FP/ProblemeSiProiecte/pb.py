
'''
def f2(n):
    if n<=0:
        raise ValueError()
    l = [x for x in range(n-1,-1,-1)]
    print (l)

    for i in range(n-1):
        l[i+1]+=l[i]
    return l[-1]

print(f2(6))
print(f2(7))


def nr_negative(l):
    if len(l)==1:
        if l[0]<0:
            return 1
        else:
            return 0
    m = len(l)//2
    return nr_negative(l[:m])+nr_negative(l[m:])

print(nr_negative([-5,1,2,3,4,-9,-7]))

def nr_negative1(l):
    if len(l)==1:
        if l[0]<0:
            return 1
        else:
            return 0
    m = int(len(l)/2)
    s1 = nr_negative(l[:m])
    s2 = nr_negative(l[m:])
    return s1+s2

print(nr_negative1([-5,1,2,3,-4,-9,-7]))


def f(n):
 if n<0: raise ValueError()
 if n <= 1: return n
 l = [0] * (n + 1)
 l[1] = 1
 for i in range(2, n+1):
     l[i] = l[i - 1] + l[i - 2]
 return l[n]

print(f(5))

print(f(1))

print(f(0))

def f(n):
 if (n<=0): raise ValueError()
 while n>0:
     c = n % 10
     n = n//10
     if (c%2==0): return True
 return False

print(f(1344))
assert(f(132)==True)


def s(l,poz=0):
 if poz<len(l):
     a = s(l,poz+1)
     b = s(l,poz+1)
     return a + b
 else: return 1

print(s([5],poz=0))

def nr_par(l):

    if len(l)==0:
        return
    if len(l)==1:
        if l[0]%2==0:
            return True
        else:
            return False
    m = len(l)//2
    return (nr_par(l[:m]))or(nr_par(l[m:]))

print(nr_par([1,3,5,7,11]))
print(nr_par([1,3,5,7,4,11,4,2]))

def prim(nr):
    ok = 1
    for i in range(1,int(nr/2)):
        if nr%i == 0:
            ok=0
    return ok
  
def longestSublist(a):

    l=[0]*len(a)
    p=[0]*len(a)
    l[len(a)-1]=1
    p[len(a)-1]=1

    for k in range(len(a)-2,-1,-1):
        p[k]=-1
        l[k]=1
        for i in range(k+1,len(a)):
            if a[i]>=a[k] and prim(a[i]) and prim(a[k]) and l[k]<l[i]+1:
                l[k]=l[i]+1
                p[k]=i

    j=0
    for i in range (0,len(a)):
        if l[i]>l[j]:
            j=i
    rez =[]
    while j!=-1:
        rez = rez +[a[j]]
        j=p[j]
    return rez

print(longestSublist([1,3,22,7,4,9,10,13,17,19,15,234,5]))

def f(n):
 if n<=0: raise ValueError()
 l = []
 while n>0:
     c = n % 10
     n = n//10
     l.append(c)
 for i in range(len(l)-1): l[i + 1] += l[i]
 return l[-1]


print(f(4532))


def inversare(l):
    if len(l)==0:
        return

    if len(l)==1:
        return [l[0]]
    m=len(l)//2

    return inversare(l[m:])+ inversare(l[:m])

print(inversare([1,2,3,4,5,6,7,8,9]))

def longestSublist_nr_pare_descresc(a):

    l=[0]*len(a)
    p=[0]*len(a)
    l[len(a)-1]=1
    p[len(a)-1]=1

    for k in range(len(a)-2,-1,-1):
        p[k]=-1
        l[k]=1
        for i in range(k+1,len(a)):
            if a[i]>=a[k] and a[i]%2==0 and a[k]%2==0 and l[k]<l[i]+1:
                l[k]=l[i]+1
                p[k]=i

    j=0
    for i in range (0,len(a)):
        if l[i]>l[j]:
            j=i
    rez =[]
    while j!=-1:
        rez = rez +[a[j]]
        j=p[j]
    return rez

print(longestSublist_nr_pare_descresc([2,12,3,6,14,3,4,7,2]))

def f(l):
 if l==None or l==[]: raise ValueError()
 aux = l[0]-1
 for e in l:
     if (aux-e>=0):
         return False
     aux = e
 return True

print(f([1,2,4,5,7,8,23,45,67]))
print(f([1,22,4,5,77,8,23,45,67]))

def produs(l):
    if len(l)==0:
        return
    if len(l)==1:
        return l[0]
    m=len(l)//2
    return produs(l[:m])*produs(l[m:])

print(produs([1,3,2,5,3,7]))

def f(l):
 if l==None or l==[]: raise ValueError()
 aux = {0:0,1:0}
 for e in l:
     aux[e % 2] += 1
 return aux[0]

 
print(f([1,5,7,9]))
'''

def sterge(l):
    if len(l)==0:
        return
    
    if len(l)==1:
        if l[0]%2==0:
            del(l[0])
        else:
            return l[0]
        
    m=len(l)//2
    return sterge(l[:m])+sterge(l[m:])

print(sterge([1,2,3,4,5]))

