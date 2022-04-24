import math
for case in range(1,int(input())+1):
    r,a,b=map(int,input().split())
    t=math.pi*r*r
    while r>0:
        r*=a
        t+=math.pi*r*r
        r//=b
        t+=math.pi*r*r
    print('Case #',case,': ',t,sep='')
