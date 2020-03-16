# lab 6

# backtracking

# # p1
#
# def back(k):
#     for i in range(1,n):
#         if i not in x:
#             x[k] = i
#             suma = 0
#             for j in range(0, k+1):
#                 suma += x[j]
#             if suma == n:
#                 f.write(str(x[:k+1]))
#                 f.write("\n")
#             elif suma < n:
#                 back(k+1)
#
# f = open("descompunere.in", "r")
# n = int(f.read())
# x = [0]*n
# f = open("descompunere.out", "w")
# back(0)
# f.close()

# p2
# def back(k):
#     for i in range(1,10):
#         if i not in x:
#             x[k] = i
#             suma = 0
#             for j in range(0, k+1):
#                 suma += x[j]
#             if suma == n:
#                 text = ''
#                 for i in range(k+1):
#                     text += str(x[i])
#                 f.write(text)
#                 f.write("\n")
#             elif suma < n:
#                 back(k+1)
#
# f = open("generare.in", "r")
# n = int(f.read())
# x = [0]*n
# f = open("generare.out", "w")
# back(0)
# f.close()

# # p3
#
# def back(taracrt):
#     if taracrt == n+1:
#         print(culori)
#     else:
#         for culoare in range(1, n+1):
#             # iau o culoare si vreau sa vad daca pot sa o pun pe culori[k]
#             ok = True
#             for tara in range(1,taracrt):
#                 if tara in lista_adiacenta[taracrt] and culori[tara] == culoare:
#                     ok = False
#             if ok:
#                 culori[taracrt] = culoare
#                 back(taracrt+1)
#
#
#
# f = open("harti.in", "r")
# n = int(f.readline())
# lista_adiacenta = {}
# for tup in f:
#     tup = tup.split()
#     x = int(tup[0])
#     y = int(tup[1])
#     if x not in lista_adiacenta:
#         lista_adiacenta[x] = []
#     if y not in lista_adiacenta:
#         lista_adiacenta[y] = []
#     if x not in lista_adiacenta[y]:
#         lista_adiacenta[y].append(x)
#     if y not in lista_adiacenta[x]:
#         lista_adiacenta[x].append(y)
#
# culori = [0]*(n+1)
# back(1)

# p3 fara generarea tuturor colorarilor
# f = open("harti.in", "r")
# n = int(f.readline())
# lista_adiacenta = {}
# for tup in f:
#     tup = tup.split()
#     x = int(tup[0])
#     y = int(tup[1])
#     if x not in lista_adiacenta:
#         lista_adiacenta[x] = []
#     if y not in lista_adiacenta:
#         lista_adiacenta[y] = []
#     if x not in lista_adiacenta[y]:
#         lista_adiacenta[y].append(x)
#     if y not in lista_adiacenta[x]:
#         lista_adiacenta[x].append(y)
#
# culori = [0]*(n+1)
# culori[1] = 1
# lastcol = 0
# for taracrt in range(1,n+1):
#     ok1 = True
#     for tarax in range(1,taracrt):
#         if tarax not in lista_adiacenta[taracrt]:
#             ok = True
#             for taray in range(tarax, taracrt):
#                 if culori[taray] == culori[tarax] and taray in lista_adiacenta[taracrt]:
#                     ok = False
#             if ok is True:
#                 culori[taracrt] = culori[tarax]
#                 ok1 = False
#     if ok1 is True:
#         lastcol += 1
#         culori[taracrt] = lastcol
#
# print(culori)

# # p4
#
# def final(t):
#     return t[1]
#
# def back(k):
#     if k == n+1:
#         print(x)
#     else:
#         if k == 1:
#             for spectacol in spectacole:
#                 x[k] = spectacol
#                 back(k+1)
#         else:
#             last = x[k-1][1]
#             for i in range(k-1, len(spectacole)):
#                 if spectacole[i][0] >= last:
#                     x[k] = spectacole[i]
#                     back(k+1)
#
#
# f = open("spectacole.txt", "r")
# spectacole = []
# for p in f:
#     p = p.split("-")
#     spectacole.append((p[0], p[1][:5], p[1][6:len(p[1])-1]))
# spectacole.sort(key=final)
# program = []
# program.append(spectacole[0])
# last = spectacole[0][1]
# for i in range(1,len(spectacole)):
#     if spectacole[i][0] > last:
#         program.append(spectacole[i])
#         last = spectacole[i][1]
# n = len(program)
# x = [0]*(n+1)
# back(1)


# lab6 partea de divide

# p3

# mergesort
# def mergesort(v):
#     if len(v) == 1:
#         return v
#     else:
#         n = len(v)
#         x = mergesort(v[:(n//2)])
#         y = mergesort(v[(n//2):])
#         n = len(x)
#         m = len(y)
#         cpy = []
#         cnt = 0
#         i = 0
#         j = 0
#         while i < n and j < m:
#             while i < n and i < n and x[i] <= y[j]:
#                 cpy.append(x[i])
#                 i += 1
#             while j < m and i < n and y[j] <= x[i]:
#                 cpy.append(y[j])
#                 j += 1
#         while i < n:
#             cpy.append(x[i])
#             i += 1
#         while j < m:
#             cpy.append(y[j])
#             j += 1
#         return cpy
#
# # bravo sora mea ai mergesortat
#
# def cautare_bin(st, dr):
#     if dr == st:
#         if v[dr] == x:
#             global end, start
#             if 0 < dr < len(v)-1:
#                 if v[dr-1] != x:
#                     start = dr
#                 if v[dr+1] != x:
#                     end = dr
#             if dr == 0:
#                 start = dr
#             if dr == len(v)-1:
#                 end = dr
#     else:
#         cautare_bin(st, (st+dr)//2)
#         cautare_bin((st+dr)//2 + 1, dr)
#
# # bravo sora mea ai cautat si binar
#
#
# f = open("data.in", "r")
# x = int(f.readline())
# v = f.read().split()
# for i in range(len(v)):
#     v[i] = int(v[i])
#
# x = int(input())
# v = mergesort(v)
# print(v)
# cautare_bin(0,len(v)-1)
# print(start, end)

# # p1 si chiar merge W O W
#
# def rucsac(v, G):
#     global sol
#     if v != []:
#         pivot = v[0]
#         rappiv = pivot[1]/pivot[0]
#         st = []
#         sumst = 0
#         dr = []
#         sumdr = 0
#         profit = 0
#         for obiect in v[1:]:
#             rap = obiect[1]/obiect[0]
#             if rap < rappiv:
#                 st.append(obiect)
#                 sumst += obiect[0]
#             else:
#                 dr.append(obiect)
#                 sumdr += obiect[0]
#                 profit += obiect[1]
#         if sumdr <= G and sumdr + pivot[0] >= G:
#             sol.append(pivot)
#             for x in dr:
#                 sol.append(x)
#             return profit + ((G - sumdr)/pivot[0])*pivot[1]
#         elif sumdr > G:
#             return rucsac(dr, G)
#         else:
#             sol.append(pivot)
#             for x in dr:
#                 sol.append(x)
#             return profit + pivot[1] + rucsac(st, G - pivot[0] - sumdr)
#
#
# f = open("rucsac.in", "r")
# G = int(f.readline())
# obiecte = []
# for tup in f:
#     tup = tup.split()
#     tup[0] = int(tup[0])
#     tup[1] = int(tup[1])
#     tup = tuple(tup)
#     obiecte.append(tup)
# sol = []
# fragment = ()
# print(rucsac(obiecte, G))
# print(sol)


# mediana obtinuta in urma interclasarii a 2 vectori sortati de aceeasi dimensiune

# def mediana(x,y):
#     if len(x) >= 2 and len(y) >= 2:
#         stx = x[len(x) // 2-1]
#         drx = x[len(x) // 2 + len(x) % 2]
#         sty = y[len(y) // 2-1]
#         dry = y[len(y) // 2 + len(y) % 2]
#         if stx > sty:
#             newx = x[:len(x) // 2]
#         else:
#             newx = y[:len(y) // 2]
#         if drx < dry:
#             newy = x[(len(x) + len(x) % 2) // 2:]
#         else:
#             newy = y[(len(y) + len(y) % 2) // 2:]
#         mediana(newx, newy)
#     if len(x) == 1 and len(y) == 1:
#         print((x[0]+y[0])/2)
#
#
#
# f = open("mediana.in", "r")
# x = f.readline().split()
# y = f.readline().split()
# for i in range(len(x)):
#     x[i] = int(x[i])
#     y[i] = int(y[i])
# mediana(x, y)


# gauri in panza aka copaci in padure aka p3 lab 6

# def dreptunghi(jos, stanga, sus, dreapta):
#     ok = True
#     for gaura in gauri:
#         if sus > gaura[0] > jos and dreapta > gaura[1] > stanga:
#             dreptunghi(gaura[0], stanga, sus, dreapta)
#             dreptunghi(jos, gaura[1], sus, dreapta)
#             dreptunghi(jos, stanga, gaura[0], dreapta)
#             dreptunghi(jos, stanga, sus, gaura[1])
#             ok = False
#     if ok:
#         sup = (dreapta - stanga)*(sus - jos)
#         global maxim, coord
#         if sup > maxim:
#             maxim = sup
#             coord = (jos, stanga, sus, dreapta)
#
#
# f = open("copaci.in", "r")
# tup = f.readline().split(); x1 = int(tup[0]); y1 = int(tup[1])
# tup = f.readline().split(); x2 = int(tup[0]); y2 = int(tup[1])
# f.readline()
# gauri = []
# for tup in f:
#     tup = tup.split()
#     x = int(tup[0])
#     y = int(tup[1])
#     gauri.append((x, y))
# maxim = 0
# coord = ()
# dreptunghi(x1, y1, x2, y2)
# print(maxim)
# print(coord)

# # mediana ponderata
#
# def weighted_median(v):
#     if len(v) == 1:
#         print(v[0])
#     if len(v) == 2:
#         if v[0][1] > v[1][1]:
#             print(v[0])
#         else:
#             print(v[1])
#     else:
#         pivot = v[0]
#         sumst = 0; sumdr = 0
#         vst = []; vdr = []
#         for elem in v[1:]:
#             if elem[0] < pivot[0]:
#                 vst.append(elem)
#                 sumst += elem[1]
#             else:
#                 vdr.append(elem)
#                 sumdr += elem[1]
#         if sumst < 0.5 and sumdr <= 0.5:
#             print(pivot)
#         if sumdr > 0.5:
#             pivot[1] += sumst
#             vdr.append(pivot)
#             weighted_median(vdr)
#
#         if sumst > 0.5:
#             pivot[1] += sumdr
#             vst.append(pivot)
#             weighted_median(vst)
#
# f = open("mediana_ponderata.in", "r")
# vector = f.readline().split()
# for i in range(len(vector)):
#     vector[i] = int(vector[i])
# v_ponderat = []
# ponderi = f.readline().split()
# for i in range(len(ponderi)):
#     ponderi[i] = float(ponderi[i])
#     v_ponderat.append([vector[i], ponderi[i]])
# print(v_ponderat)
# weighted_median(v_ponderat)

# # mediana a 2 vec de dim dif
#
# def mediana(v, w):
#     if len(v) <= 2:
#
#     else:
#         if len(v)%2:
#             x
#
# f = open("mediana_len_dif.in", "r")
# v = f.readline().split()
# for i in range(len(v)):
#     v[i] = int(v[i])
# w = f.readline().split()
# for i in range(len(w)):
#     w[i] = int(w[i])
# if len(v) > len(w):
#     aux = v
#     v = w
#     w = aux
# mediana(v, w)




