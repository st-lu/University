# a,b,c - rasp delta
import math

x, y, z = input().split()
a, b, c = int(x), int(y), int(z)

if a == 0:
    print((-1)*(c/b))
else:
    delta = b*b - 4*a*c
    if delta < 0:
        print("ecuatia nu are solutie")
    elif delta > 0:
        print("x1 = ", ((-1) * b + math.sqrt(delta)) / (2 * a))
        print ("x2 = " , ((-1) * b - math.sqrt(delta)) / (2 * a))
    else:
        print("x = ", ((-1) * b + math.sqrt(delta)) / (2 * a))