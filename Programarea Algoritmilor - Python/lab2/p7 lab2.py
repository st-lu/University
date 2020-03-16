a, b, c = input().split()
ziua, luna, anul = int(a), int(b), int(c)

luni = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
sapt = ["duminica", "luni", "marti", "miercuri", "joi", "vineri", "sambata"]
zile = 0

if anul < 2000:
    zile = (anul - 1702) * 365 + (anul - 1704) // 4 - (anul - 1700) // 100
else:
    zile = (anul - 1702) * 365 + (anul - 1704) // 4 - (anul - 1700) // 100 + 1

i = 0
while i+1 < luna:
    zile += luni[i]
    i += 1

zile += ziua
zile %= 7
print(sapt[zile])



