l1 = [1,2,3,4,5]
l2 = [6,5,4,3,2]
l3 = [False,False,True,False,True]
x = 0
s = ""
flag = 0
while ( x != len(l3) ):
    if (flag == 1):
        s = s + ","
    if (l3[x] == False):
        s = s + str(l2[x])
    else:
        s = s + str(l1[x])
    x += 1
    
    flag = 1

print("["+s+"]")