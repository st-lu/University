prop = input().split()
cuvex = input()
cuvnou = input()
propnoua = ''
for x in prop:
    if x == cuvex:
        propnoua += cuvnou
        propnoua += " "
    else:
        propnoua += x
        propnoua += " "

print(propnoua)


