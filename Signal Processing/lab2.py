# Luana Strimbeanu - 343

# 1
B = 200
fs = B*2
print("1\n" + str(fs) + "\n")


# 2
def subNiquist(m):
    ceil = (2 * fc - B) / m
    floor = max((2 * fc + B) / (m + 1), 2.0 * B)

    print(str(floor) + " <= fs <= " + str(ceil))


B = 10
fc = 90

print("2. a)")
str(subNiquist(1))
print("2. b)")
str(subNiquist(2))
print("2. c)")
str(subNiquist(4))

# 3
import numpy as np
import matplotlib.pyplot as plt

fc = 10
fs = 1000
t = np.linspace(0, 1, num=fs)
x = np.sin(2*np.pi*fc*t)
X = np.fft.fft(x)
X = np.abs(X)
X = X[:500]
plt.plot(X)
plt.show()


