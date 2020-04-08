prop = input()

propnoua = ''
vocale = 'aeiou'

for i in range(len(prop)):
    propnoua += prop[i]
    if vocale.find(prop[i]) != -1:
        propnoua += 'p'
        propnoua += prop[i]

print(propnoua)