# p2 lab3
# p = 'ana are ana ion da ana ion'
# l = p.split()
# d = {}
# maxim = 1
# minim = len(p)
# for str in l:
#     if str in d:
#         d[str] +=1
#     else:
#         d[str]=1
#
# for cheie in d:
#     if d[cheie] > maxim:
#         maxim = d[cheie]
#         cuvmax = cheie
#     if d[cheie] < minim:
#         minim = d[cheie]
#         cuvmin = cheie
#
# print(cuvmax, " ", cuvmin)



#p3 lab
# p = input().split()
# d = {}
# for str in p:
#     for ch in str:
#         if ch in d:
#             d[ch] += 1
#         else:
#             d[ch] = 1
# maxim = 1
# minim = len(p[0])
# for cheie in d:
#     if d[cheie] > maxim:
#         maxim = d[cheie]
#         chmax = cheie
#     if d[cheie] < minim:
#         minim = d[cheie]
#         chmin = cheie
#
# print(chmin, chmax)

# #p4 lab
# d1 = {'ana':1, "george":2, "costel":4, "geani":5}
# d2 = { "mere":3, "pere":6, "george": 7, "luni":8, "ana":9}
# d3 = {}
# for cheie in d1:
#     if cheie in d2:
#         d3[cheie] = d1[cheie] + d2[cheie]
#     else:
#         d3[cheie] = d1[cheie]
#
# for cheie in d2:
#     if cheie in d1:
#         continue
#     else:
#         d3[cheie] = d2[cheie]
#
# print(d3)

# # p5 lab3
# p = input().split()
# cuv = input()
# dcuv = {}
# for ch in cuv:
#     dcuv[ch] = 1
# dnew = {}
# for str in p:
#     for ch in str:
#         dnew[ch] = 1
#     ok = True
#     for cheie in dcuv:
#         if cheie not in dnew:
#             ok = False
#
#     if ok is True:
#         print(str)
#
#     dnew.clear()

# # p6 lab3
# p = input().split()
# rime = {}
# for str in p:
#     newstr = str[(len(str)-2):]
#     if newstr not in rime:
#         rime[newstr] = []
#     rime[newstr].append(str)
#
# final = {}
#
# for cheie in rime:
#     if len(rime[cheie]) > 1:
#         if cheie not in final:
#             final[cheie] = rime[cheie]
#
# print(rime)
# print(final)

# # p7
# numefisier = input()
# numefisier = numefisier + ".txt"
# f = open(numefisier, "r")
# p = f.read()
# p = p.split()
# pret = []
# cantitate = []
# for i in range(len(p)-1):
#     x = p[i]
#     numar = -1
#     if x.isdecimal():
#         numar = int(x)
#     else:
#         zec = x.split(".")
#         if len(zec) == 2:
#             intreg = int(zec[0])
#             zecimall = zec[1].split()
#             zecimal = int(zec[1])
#             numar = intreg + zecimal * pow(10, (-1 * len(zecimall)))
#     if numar != -1:
#         if p[i+1] == "RON":
#             pret.append(numar)
#         else:
#             cantitate.append(numar)
#
# s = 0
# for i in range(len(pret)):
#     s += pret[i]*cantitate[i]
#
# print(s)

# # p8
# f = open("inventar.txt", "r")
# d = {}
# for p in f:
#     magazin = p.split()
#     d[magazin[0]] = magazin[1:]
#
#     # intersectie
# i = 0
# for cheie in d:
#     i += 1
#     x = cheie
#     if i == 1:
#         break
#
# intersectie = []
#
# for nr in d[x]:
#     ok = True
#     for cheie in d:
#         if cheie != x and nr not in d[cheie]:
#             ok = False
#     if ok is True:
#         intersectie.append(nr)
#
# print(intersectie)
#
# reuniune = []
#
# for cheie in d:
#     for nr in d[cheie]:
#         if nr not in reuniune:
#             reuniune.append(nr)
#
# print(reuniune)
#
# for cheie in d:
#     diferenta = []
#     for nr in d[cheie]:
#         ok = True
#         for cheie2 in d:
#             if cheie2 != cheie and nr in d[cheie2]:
#                 ok = False
#         if ok is True:
#             diferenta.append(nr)
#     print(cheie, diferenta)

# # p9
# inp = "run: to go faster than a walk : to go steadily by springing steps : to take part into a contest - ~ a marathon : to move at a fast gallop - he may occasionally run to and from work : flee, retreat, escape - drop the gun and run : to go without restraint : move freely about at will - let chickens ~ loose : consort - we run with our group \n" + "dog: canid wolves, foxes, and other dogs especially : a highly variable domestic mammal : a pet ~ : fellow, chap, a lazy person - you lucky dog \n" + "break: break a/the record to do something better than the best known speed, time, number, etc. previously achieved : to fail to keep a law, rule, or promise = ~ the law : These enzymes break down food in the stomach (= cause food to separate into smaller pieces). I needed something to break the monotony of my typing job. The phone rang, as to break my concentration. To ~ (of a storm) = to start suddenly: We arrived just as a storm was breaking. \n"
# inp = inp.split("\n")
# lista = []
# for definition in inp:
#     defin = definition.split(":")
#     cuv = defin[0]
#     definition = definition.split()
#     aparitie = definition.count(cuv)
#     aparitie += definition.count("~")
#     lista.append((cuv, aparitie))
# lista.pop()
# print(lista)

# # p10
# p = input()
# l = []
# i = 1
# while p != "-1":
#     p = p.split(" ", 1)
#     tup = (p[0], p[1], i)
#     l.append(tup)
#     p = input()
#     i += 1
#
# print(l)
#
# s = set()
# for x in l:
#     if x[0] not in s:
#         s.add(x[0])
#
# print(s)
# d = {}
# for x in l:
#     if x[0] in d:
#         d[x[0]].append((x[1], x[2]))
#     else:
#         d[x[0]] = []
#         d[x[0]].append((x[1], x[2]))
#
# print(d)

# # p11
# import math
# n = int(input())
# a = []
# k = 1
# for i in range(n):
#     a.append([])
#     for j in range(n):
#         a[i].append(k)
#         k += 1
# start = 0
# listcoord = []
# while start < n:
#     # sus
#     for j in range(start, n-start):
#         tup = (start, j)
#         if tup not in listcoord:
#             listcoord.append(tup)
#
#     # dreapta
#     for i in range(start, n-start):
#         tup = (i, n-start-1)
#         if tup not in listcoord:
#             listcoord.append(tup)
#     # jos
#     for j in range(start, n-start):
#         tup = (n-start-1, n-j-1)
#         if tup not in listcoord:
#             listcoord.append(tup)
#     #stanga
#     for i in range(start, n-start):
#         tup = (n-i-1, start)
#         if tup not in listcoord:
#             listcoord.append(tup)
#
#     start += 1
# spirala = []
# for coord in listcoord:
#     x = coord[0]
#     y = coord[1]
#     spirala.append(a[x][y])
#
# print(spirala)

# p12

def bfs(nod):
    global BF
    BF = []
    st = 0
    dr = 0
    BF.append((nod, -1))
    while st <= dr:
        tata = BF[st][0]
        f.write(str(tata) + " ")
        for fiu in lista_adiacenta[tata]:
            ok = True
            for nodviz in BF:
                if fiu in nodviz:
                    ok = False
            if ok:
                BF.append((fiu, tata))
                dr += 1
        st += 1

def dfs(nod):
    viz[nod] = 1
    f.write(str(nod) + " ")
    for nodv in lista_adiacenta[nod]:
        if viz[nodv] == 0:
            dfs(nodv)

def lant_minim(destination, nodc):
    sol.append(nodc)
    for tup in BF:
        if tup[0] == nodc:
            tata = tup[1]
            break
    if tata != destination:
        lant_minim(destination, tata)



f = open("graf_in.txt", "r")
orientare = f.readline()
if orientare[0] == 'o':
    orientare = True
else:
    orientare = False
p = f.readline()
p = p.split()
n = int(p[0])
m = int(p[1])
lista_adiacenta = {}
lista_arce = []
a = []
for i in range(n+1):
    a.append([])
    for j in range(n+1):
        a[i].append(0)

for i in range(m):
    p = f.readline()
    p = p.split()
    x = int(p[0])
    y = int(p[1])
    lista_arce.append((x, y))
    if x not in lista_adiacenta:
        lista_adiacenta[x] = []
    if y not in lista_adiacenta:
        lista_adiacenta[y] = []
    if y not in lista_adiacenta[x]:
        lista_adiacenta[x].append(y)
    a[x][y] = 1
    if orientare:
        if x not in lista_adiacenta[x]:
            lista_adiacenta[y].append(x)
        a[y][x] = 1

p = f.readline()
p = p.split()
start = int(p[0])
finish = int(p[1])

f = open("graf_out.txt", "w")
lista_arce_str = ''
for tup in lista_arce:
    lista_arce_str += "(" + str(tup[0]) + ", " + str(tup[1]) + ") "
f.write(lista_arce_str)

lista_adiacenta_str = '\n'
for cheie in lista_adiacenta:
    lista_adiacenta_str += str(cheie) + ": "
    for nr in lista_adiacenta[cheie]:
        lista_adiacenta_str += str(nr) + " "
    lista_adiacenta_str += "\n"
f.write(lista_adiacenta_str)

a_str = ""
for i in range(n+1):
    for j in range(n+1):
        a_str += str(a[i][j]) + " "
    a_str += "\n"
f.write(a_str)

f.write("bfs: ")
bfs(start)
viz = [0]*(n+1)
f.write("\ndfs: ")
dfs(start)
sol = []
f.write("\nlant minim: ")
lant_minim(start, finish)
sol.append(start)
sol.reverse()
sol_str = ""
for i in sol:
    sol_str += str(i) + " "
f.write(sol_str)
f.close()

# # p13
# f = open("persoane.in", "r")
# lista_mare = []
# for date in f:
#     date = date.split(",")
#     d = {}
#     print(date)
#     for chestie in date:
#         chestie = chestie.split(":")
#         if chestie[0] == 'nume' or chestie[0] == 'prenume':
#             d[chestie[0]] = chestie[1]
#         if chestie[0] == 'adresa':
#             d[chestie[0]] = {}
#             d["adresa"][chestie[1][1:]] = chestie[2]
#         if chestie[0] == 'strada' or chestie [0] == 'numar' or chestie[0] == 'oras':
#             d["adresa"][chestie[0]] = chestie[1]
#         if "adresa" in d:
#             for cheie in d["adresa"]:
#                 valoare = d["adresa"][cheie]
#                 valoare = valoare.split("}")
#                 valoare = valoare[0]
#                 d["adresa"][cheie] = valoare
#         for cheie in d:
#             if cheie != 'adresa':
#                 valoare = d[cheie]
#                 valoare = valoare.split("\n")
#                 valoare = valoare[0]
#                 d[cheie] = valoare
#
#         lista_mare.append(d)
# print(lista_mare)

# # p14
#
# import random
#
# f = open("date.in", "r")
# lista = []
# for p in f:
#     p = p.split()
#     email = ''
#     email = p[0] + "." + p[1] + "@myfmi.unibuc.ro,"
#     cifre = random.randint(1000, 9999)
#     alfabet = 'a b c d e f g h i j k l m n o p q r s t u v w x y z'
#     alfabet = alfabet.split()
#     stringmic = ''
#     stringmic = random.choice(alfabet) + random.choice(alfabet) + random.choice(alfabet)
#     literamare = random.choice(alfabet).upper()
#     parola = ''
#     cifre = str(cifre)
#     parola = literamare + stringmic + cifre
#     email += parola
#     lista.append(email)
#
# f = open("date.out", "w")
# for email in lista:
#     f.write(email+"\n")
# f.close()

# p15

f = open("test.in", "r")
nota = 1
text = ''
for ecuatie in f:
    a = b = c = 0
    for i in range(len(ecuatie)):
        chr = ecuatie[i]
        if chr.isdecimal():
            numar = ''
            while chr.isdecimal():
                numar += chr
                i += 1
                if i < len(ecuatie):
                    chr = ecuatie[i]
                else:
                    break
            if a == 0:
                a = int(numar)
            elif b == 0:
                b = int(numar)
            elif c == 0:
                c = int(numar)

    if a*b == c:
        nota += 1
        text += ecuatie[:(len(ecuatie) - 1)] + " Corect\n"
    else:
        d = a*b
        text += ecuatie[:(len(ecuatie) - 1)] + " Gresit " + str(d) + "\n"
text += "Nota " + str(nota)
f = open("test.out", "w")
f.write(text)
f.close()
