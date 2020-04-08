prop = input().split()
ok = True

if len(prop) != 2:
    ok = False

nume = prop[0]

if ord(nume[0]) < ord('A') or ord(nume[0]) > ord('Z'):
    ok = False

for i in range(1, len(nume)):
    if ord(nume[i]) < ord('a') or ord(nume[i]) > ord('z'):
        ok = False

prenume = prop[1].split("-")

if len(prenume) > 2:
    ok = False

if ord(prenume[0][0]) < ord('A') or ord(prenume[0][0]) > ord('Z') or ord(prenume[1][0]) < ord('A') or ord(prenume[1][0]) > ord('Z'):
    ok = False
for i in range(1, len(prenume[0])):
    if ord(prenume[0][i]) < ord('a') or ord(prenume[0][i]) > ord('z'):
        ok = False
for i in range(1, len(prenume[1])):
    if ord(prenume[1][i]) < ord('a') or ord(prenume[1][i]) > ord('z'):
        ok = False

if ok is True:
    print("bravo frate")
else:
    print("aoleu ce facusi nene")
