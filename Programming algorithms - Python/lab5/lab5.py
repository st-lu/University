''' versiune lab'''
# # p1
#
# def cmp(t):
#     return t[1]
#
# L = []
# f = open("tis.txt").read().split()
# for i in range(len(f)):
#     tup = (i+1, int(f[i]))
#     L.append(tup)
#
# L.sort(key=cmp)
# suma = Sum = 0
# for i in range(len(L)):
#     tup = L[i]
#     suma += tup[1]
#     Sum += suma
#
# print(round(Sum/len(L), 2))

# # p2
# def cmp(t):
#     return t[2]
#
# f = open("spectacole.txt").read().split("\n")
# L = []
#
# for str in f:
#     nume = str[12:]
#     spectacol = str[:11].split(":")
#     t = spectacol[1].split("-")
#     minlast = spectacol[2]
#     spectacol[1] = t[0]
#     spectacol[2] = t[1]
#     spectacol.append(minlast)
#     spectacol.append(nume)
#     spectacol = tuple(spectacol)
#     L.append(spectacol)
#
# L.sort(key=cmp)
# program = []
# program.append(L[0])
# i = 1
# lasth = L[0][2]
# lastm = L[0][3]
# while i < len(L):
#     starth = L[i][0]
#     startm = L[i][1]
#     if starth > lasth or (starth == lasth and lastm < startm):
#         program.append(L[i])
#     lasth = L[i][0]
#     lastm = L[i][1]
#     i += 1
#
#
# print(program)
# g = open("programe.txt","w")
# for p in program:
#     g.write(p[0]+":"+p[1]+'-'+p[2]+":"+p[3]+" "+p[4]+"\n")





''' versiunea mea de acasa'''
# # p1
# f = open("tis.txt", "r")
# v = f.read()
# v = v.split()
# for i in range(len(v)):
#     v[i] = int(v[i])
# v.sort()
# print(v)
# # #suma medie
# # sum = 0
# # Sum = 0
# # for elem in v:
# #     sum += elem
# #     Sum += sum
# # Sum /= len(v)
# # print(Sum)

# # p2
#
# def ora_final(t):
#     return t[1]
#
# f = open("spectacole.txt", "r")
# p = f.read()
# p = p.split("\n")
# spectacole = []
# for spect in p:
#     spect = spect.split("-")
#     spectacol = []
#     spectacol.append(spect[0])
#     s = spect[1][:5]
#     spectacol.append(s)
#     s = spect[1][6:]
#     spectacol.append(s)
#     spectacole.append(spectacol)
#
# # print(spectacole)
# spectacole.sort(key=ora_final)
# print(spectacole)
# program = []
# program.append(spectacole[0])
# last = spectacole[0][1]
# for i in range(1,len(spectacole)):
#     if spectacole[i][0] > last:
#         program.append(spectacole[i])
#         last = spectacole[i][1]
#
# print(program)
# text = ''
# for spectacol in program:
#     text += spectacol[0] + "-" + spectacol[1] + " " + spectacol[2] + "\n"
# f = open("program.txt", "w")
# f.write(text)
# f.close()

# # p3
#
# def latura(t):
#     return t[0]
#
# f = open("cuburi.txt", "r")
# p = f.read()
# p = p.split("\n")
#
# n = int(p[0])
# cuburi = []
# for i in range(1,n+1):
#     cub = p[i].split()
#     cub[0] = int(cub[0])
#     cub = tuple(cub)
#     cuburi.append(cub)
# cuburi.sort(key=latura, reverse=True)
# print(cuburi)
# turn = []
# turn.append(cuburi[0])
# last = cuburi[0][1]
# sum = cuburi[0][0]
# for cub in cuburi:
#     if cub[1] != last:
#         turn.append(cub)
#         last = cub[1]
#         sum += cub[0]
#
# print(turn)
# text = ''
# for cub in turn:
#     text += str(cub[0]) + ' ' + cub[1] + "\n"
# text += "\n" + "Inaltime totala: " + str(sum)
# f = open("turn.txt", "w")
# f.write(text)

# # p4
#
# f = open("bani.txt", "r")
# p = f.read()
# p = p.split("\n")
# suma = int(p[1])
# bancnote = p[0].split()
# for i in range(len(bancnote)):
#     bancnote[i] = int(bancnote[i])
#
# bancnote.sort(reverse=True)
# sumacpy = suma
# cnt = 0
# plata = []
# while sumacpy != 0:
#     k = 0
#     ok = False
#     while sumacpy >= bancnote[cnt]:
#         sumacpy -= bancnote[cnt]
#         k += 1
#         ok = True
#     if ok:
#         plata.append((bancnote[cnt], k))
#     cnt += 1
#
# print(plata)
# text = str(suma) + " = "
# tuplast = plata.pop()
# for tup in plata:
#     text += str(tup[0]) + "*" + str(tup[1]) + " + "
#
# text += str(tuplast[0]) + "*" + str(tuplast[1])
# f = open("plata.txt", "w")
# f.write(text)
# f.close()

# # p5
#
# def deadline(t):
#     return t[1]
#
# f = open("activitati.txt", "r")
# n = int(f.readline())
# activitati = []
# for i in range(n):
#     activitate = f.readline()
#     activitate = activitate.split()
#     activitate[0] = int(activitate[0])
#     activitate[1] = int(activitate[1])
#     activitate = tuple(activitate)
#     activitati.append(activitate)
#
# activitati.sort(key=deadline)
#
# timp = 0
# maxim = 0
# text = "Interval     Termen     Intarziere\n"
# for activitate in activitati:
#     text += "("+ str(timp) + " --> "
#     timp += activitate[0]
#     text += str(timp) + ")     " + str(activitate[1]) + "          "
#     if timp > activitate[1] and timp - activitate[1] > maxim:
#         maxim = timp - activitate[1]
#     text += str(max(0,timp - activitate[1])) + "\n"
#
# f = open("intarzieri.txt", "w")
# f.write(text)
# f.close()

# # p6
#
# f = open("spectacole.txt", "r")
# spectacole = []
# for p in f:
#     p = p.split()
#     ore = p[0].split("-")
#     spectacol = (ore[0], ore[1], p[1])
#     spectacole.append(spectacol)
#
# spectacole.sort()
# program = []
# #program[0].append(spectacole[0])
# for spectacol in spectacole:
#     ok = False
#     for i in range(len(program)):
#         s = program[i]
#         last = s[len(s)-1]
#         if spectacol[0] >= last[1]:
#             program[i].append(spectacol)
#             ok = True
#             break
#
#     if ok is False:
#         program.append([spectacol])
#
# text = str(len(program)) + " sali\n\n"
# for sala in program:
#     sala_str = str(sala)
#     text += sala_str[1:len(sala_str)-1] + "\n\n"
#
# f = open("sali.txt", "w")
# f.write(text)
# f.close()

# # p7
#
# def raport(t):
#     return t[0]/t[1]
#
# f = open("obiecte.txt", "r")
# n = int(f.readline())
# obiecte = []
#
# for i in range(n):
#     tup = f.readline()
#     tup = tup.split()
#     tup[0] = int(tup[0])
#     tup[1] = int(tup[1])
#     tup = tuple(tup)
#     obiecte.append(tup)
#
# greutate = int(f.readline())
#
# obiecte.sort(key=raport, reverse=True)
# s = 0
# rucsac = []
# for obiect in obiecte:
#     if obiect[1] <= greutate:
#         greutate -= obiect[1]
#         rucsac.append((obiect, 1))
#     elif greutate != 0:
#         rap = greutate/obiect[1]
#         rucsac.append((obiect, rap))
# greutate = 0
# valoare = 0
# for obiect in rucsac:
#     greutate += obiect[0][1]*obiect[1]
#     valoare += obiect[0][0]*obiect[1]
#
# print(rucsac)
# print(greutate)
# print(valoare)

# # p8
#
# def profit(t):
#     return t[2]
#
# f = open("proiecte.txt", "r")
# proiecte = []
# maxim = 0
# for proiect in f:
#     proiect = proiect.split()
#     print(proiect)
#     proiect[1] = int(proiect[1])
#     proiect[2] = int(proiect[2])
#     proiect = tuple(proiect)
#     proiecte.append(proiect)
#     if proiect[1] > maxim:
#         maxim = proiect[1]
#
# proiecte.sort(key=profit, reverse=True)
# program = {}
# for i in range(1, maxim+1):
#     program[i] = None
#
# available = 1
# for proiect in proiecte:
#     if proiect[1] >= available:
#         program[available] = proiect
#         available += 1
#         if available > maxim:
#             break
#
# text = 'T=' + str(len(program)) + "\nproiecte: "
# for proiect in program:
#     text += program[proiect][0] + ", "
# text += "\nprofit: "
# profitt = 0
# for proiect in program:
#     text += str(program[proiect][2]) + "+"
#     profitt += program[proiect][2]
# text = text[:len(text)-1] + " = " +str(profitt)
# f = open("profit.txt", "w")
# f.write(text)