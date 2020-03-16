prop = input()

propnoua = ''

for i in range(len(prop)):

    # if prop[i] == '-':
    #     continue

    propnoua += prop[i]
    if i+1 < len(prop):
        if prop[i+1] == '-' or prop[i+1] == ' ' or prop[i+1] == '.':
            propnoua += 'p'
            propnoua += prop[i]

print(propnoua)
