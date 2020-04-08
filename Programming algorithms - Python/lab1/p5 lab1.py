n = int(input())
v = input().split()
s = [0]*n
max2 = 0
max1 = 0
for i in range(n):
    s[i] = int(v[i])
    if s[i] > max1:
        max2 = max1
        max1 = s[i]
    elif (s[i] < max1) & (s[i] > max2):
        max2 = s[i]

print(max2, max1)