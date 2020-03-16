prop = input()
k = int(input())

#criptare
propcript = ""
a = ord("a")
space = " "
for i in range(len(prop)):
    if prop[i] != space:
        propcript += chr((ord(prop[i]) + k - a) % 26 + a)

    else:
        propcript += space

print(propcript)

#decriptare
propdecript = ""
a = ord("a")
space = " "
for i in range(len(propcript)):
    if propcript[i] != space:
        propdecript += chr((ord(propcript[i]) - k - a) % 26 + a)

    else:
        propdecript += space

print(propdecript)
