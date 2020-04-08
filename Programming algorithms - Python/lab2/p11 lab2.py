text = input()
propozitii = [""] * 1000
cnt = 0
i = 0
while i < len(text):
    if ord(text[i]) >= ord("A") or ord(text[i]) <= ord("Z"):
        ok = True
        while ok is True:
            propozitii[cnt] += text[i]
            if i+1 < len(text):
                i += 1
            if i == (len(text) - 1) and text[i] == '.':
                ok = False
                break
            if i+2 < len(text):
                if text[i] == '.' and (ord(text[i+2]) >= ord("A") or ord(text[i+2]) <= ord("Z")):
                    ok = False

        cnt += 1
        i += 1



for x in propozitii:
    print(x)
