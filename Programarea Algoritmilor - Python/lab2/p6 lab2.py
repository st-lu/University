prop = input().split()
numar = 0
suma = 0
for x in prop:
    if (ord(x[0]) <= ord('0')) or (ord(x[0]) >= ord('9')):
        continue
    else:
        for i in range(len(x)):
            numar = (ord(x[i]) - ord('0')) * (10**(len(x) - i - 1))
            suma += numar

print(suma, "RON")