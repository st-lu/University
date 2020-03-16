prop = input()
sum1 = 0
sum2 = 0
prelast = 0
last = 0
numar = 0
for i in range(len(prop)):
    if prop[i] != '$':
        continue
    else:
        if i+1 < len(prop):
            i += 1
            nr = ''
            while (ord(prop[i]) >= ord('0')) & (ord(prop[i]) <= ord('9')):
                nr += prop[i]
                if i+1 < len(prop):
                    i += 1
                else:
                    break
            numar = int(nr)

            if sum1 == 0:
                sum1 = numar
            elif sum2 == 0:
                sum2 = numar
            elif prelast == 0:
                prelast = numar
            elif last == 0:
                last = numar
            else:
                prelast = last
                last = numar

print(sum1, " ", sum2)
if prelast == last:
    print("s-au inteles :)")
else:
    print("nu s-au inteles :(")


