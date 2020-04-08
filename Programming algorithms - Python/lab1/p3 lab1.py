a, b = input().split()
x, y = int(a), int(b)
l1 = x
l2 = y
r = 0

while y != 0:
    r = x % y
    x = y
    y = r

print("numar placi: ", ((l1 * l2) / (x * x)))
print("dimensiune placi: ", x)