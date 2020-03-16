a, b, c, d = input().split()
x, n, p, m = int(a), int(b), int(c), int(d)
dist = 0
while m > 0:
    if m > n:
        m -= n
        dist += n*x
        x -= x * p / 100
    else:
        dist += x*m
        break

print(dist)
