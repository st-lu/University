n = int(input())
v = input().split(",")
s = [0.0]*n
maxim = 0
for i in range(n):
    s[i] = float(v[i])
    if i > 0:
        dif = s[i] - s[i-1]
        if dif > maxim:
            maxim = dif

print(maxim)