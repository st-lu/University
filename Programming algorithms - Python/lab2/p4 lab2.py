s1 = input()
s2 = input()
okk = True
for x in s1:
    ok = False
    for y in s2:
        if x == y:
            s2 = s2.replace(y, '1', 1)
            ok = True
            break
    if ok is False:
        print("sirurile nu sunt anagrame")
        okk = False
        break

if okk is True:
    print("sirurile sunt anagrame")