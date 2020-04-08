n = int(input())
cnt = 0
v = []

while n > 0:
    v.append(n % 10)
    n //= 10

v.sort()
n = 0
for i in range(len(v)):
    n += v[i] * (10 ** (len(v) - i - 1))

print(n)

i = len(v)-1
k = 0
n = 0
while i >= 0:
    n += v[i] * (10 ** (len(v) - k - 1))
    i -= 1
    k += 1

print(n)
