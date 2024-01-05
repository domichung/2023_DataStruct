s = "123,456.88"
x = 0
out = "" 
while ( x < len(s) ):
    if ( s[x] >= "0" and s[x]<= "9" ):
        out = out + s[x]
    if ( s[x] == '.' ):
        out = out + s[x]
    x+=1

print(float(out))