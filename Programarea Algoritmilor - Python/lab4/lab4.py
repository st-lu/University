# am ajuns si la lab4 fratii mei!

# # p1
# import math
# def ipotenuza(a, b):
#     c = round(math.sqrt(a*a + b*b), 2)
#     return c
#
# b = int(input())
# for i in range(1, b+1):
#     teoretic = i*i + b*b
#     c = ipotenuza(i, b)
#     if c*c == teoretic:
#         c = int(c)
#         print(i, b, c)

# # p2
# import  math
# def lungime_arie_cerc(r):
#     pi = math.pi
#     lungime = 2*pi*r
#     raza = pi*r*r
#     return lungime, raza
#
# r = int(input())
# print(lungime_arie_cerc(r))

# # p3
#
# def min_max(*argvec):
#     maxim = 0
#     minim = 1e29
#     ok = False
#     arg = argvec[0]
#     for x in arg:
#         x = int(x)
#         ok = True
#         if x > maxim:
#             maxim = x
#         if x < minim:
#             minim = x
#     if ok:
#         return minim, maxim
#     else:
#         return None
#
# f = open("numere.txt", "r")
#
# tup = min_max(f.read().split())
# print(str(tup))
# f = open("impartire.txt", "w")
# if tup != None:
#     f.write(str(tup[1]/tup[0]))
# else:
#     f.write("None")


# # p4
#
# def ciur(n):
#     a = [1]*1000001
#     a[0] = a[1] = 0
#     i = 2
#     while i*i <= 1000001:
#         if a[i]:
#             for j in range(i, 1000001//i):
#                 a[i*j] = 0
#         i += 1
#     for i in range(n+1):
#         if a[i] == 1:
#             yield i
#     yield -1
#     k = 1
#     i = 2
#     while k <= n:
#         if a[i] == 1:
#             yield i
#             k += 1
#         i += 1
#
#
# n = int(input())
# i = 0
# end = False
# primul = ''
# aldoilea = ''
# for i in ciur(n):
#     if i != -1 and end is False:
#         primul += str(i) + " "
#     if i == -1:
#         end = True
#         continue
#
#     if end:
#         aldoilea += str(i) + " "
#     if i == "end2":
#         break
#
# print(primul)
# print(aldoilea)

# # p6
# import modul
# n = 0
# v = []
# modul.citire(n, v)
# pozitive = modul.valpoz(v)
# modul.semn(v)
# negative = modul.valpoz(v)
# modul.semn(negative)
# modul.afisare(negative)
# modul.afisare(pozitive)

# # p7
#
# def lungime(t):
#     return len(t)
#
# f = open("cuvinte.txt", "r")
# p = f.read()
# p = p.split()
# l = p.copy()
# p.sort(reverse=True)
# f = open("cuv_sortate.txt", "w")
# f.write(str(p)+"\n")
# p.sort()
# p.sort(key=lungime)
# f.write(str(p) + "\n")
# l.sort(key=lungime)
# f.write(str(l))
# f.close()

# # p8
#
# def nume(t):
#     return t[0]
#
# def varsta(t):
#     return t[1]
#
# def salariu(t):
#     return t[2]
#
# f = open("angajati.txt", "r")
# p = f.read()
# p = p.split("\n")
# n = int(p[0])
# angajati = []
# for i in range(1, n+1):
#     angajat = p[i].split(",")
#     angajati.append(angajat)
#
#
# angajat_cautat = input()
# for pers in angajati:
#     if angajat_cautat in pers:
#         print(pers)
#         break
#
# maxim = 0
# list_max = []
# for angajat in angajati:
#     if int(angajat[2]) > maxim:
#         maxim = int(angajat[2])
#         list_max.clear()
#         list_max.append(angajat[0])
#     elif int(angajat[2] == maxim):
#         list_max.append(angajat[0])
#
# print(maxim, list_max)
#
# sum = 0
# for angajat in angajati:
#     sum += int(angajat[2])
# sum /= n
# print(sum)
#
# angajati.sort(key=nume)
# f = open("angajati_nume.txt", "w")
# f.write(str(angajati))
# f.close()
#
# angajati.sort(key=varsta, reverse=True)
# f = open("angajati_varsta_nume.txt", "w")
# f.write(str(angajati))
# f.close()
#
# angajati.sort(key=varsta)
# angajati.sort(key=salariu, reverse=True)
# f = open("angajati_salariu_varsta.txt", "w")
# f.write(str(angajati))
# f.close()

# # p9
#
# def citire():
#     n = int(input())
#     p = input()
#     p = p.split()
#     for i in range(n):
#         p[i] = int(p[i])
#     return n, p
#
# def mai_mare(i, j, x, p):
#     ok = False
#     for k in range(i,j):
#         if p[k] > x:
#             return k
#             ok = True
#     if ok is False:
#         return -1
#
# tup = citire()
# n = tup[0]
# v = tup[1]
# ok = True
# for i in range(n):
#     y = mai_mare(i+1, n-1, v[i], v)
#     if y != -1:
#         ok = False
#
# if ok is True:
#     print("Da")
# else:
#     print("Nu")


