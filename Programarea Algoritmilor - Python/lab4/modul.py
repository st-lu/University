def citire(n, v):
    n = int(input())
    for i in range(n):
        x = int(input())
        v.append(x)

def afisare(v):
    string = ''
    for i in v:
        string += str(i) + " "
    print(string)

def valpoz(v):
    pozitive = []
    for i in v:
        if i > 0:
            pozitive.append(i)
    return pozitive

def semn(v):
    for i in range(len(v)):
        v[i] = (-1)*v[i]
