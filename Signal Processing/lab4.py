# Luana Strimbeanu Grupa 343

# 1
fs = 44.1  # kHz
fs *= 1000  # Hz
bindist = 1  # Hz
# bindist = fs/N
N = fs / bindist

print(N)

# 2

import numpy as np
import matplotlib.pyplot as plt


def rectangle(dim):
    return 1


def hanning(dim):
    return 0.5 * (1 - np.cos(2 * np.pi * dim / Nw))


# a
Nw = 200
fs = 100
t = np.linspace(0, 1, num=Nw)
x = np.sin(2 * np.pi * fs * t)

xwr = []
for i in range(Nw):
    xwr.append(x[i] * rectangle(i))

xwhn = []
for i in range(Nw):
    xwhn.append(x[i] * hanning(i))

# plt.plot(xwr)
# plt.plot(xwhn)
# plt.show()

# b

f1 = 1000  # Hz
f2 = 1100  # Hz
fs = 8000  # Hz
Nw = 1000

t = np.linspace(0, Nw, num=fs)
x1 = np.sin(2 * np.pi * f1 * t)
x2 = np.sin(2 * np.pi * f2 * t)

xwr1 = []
for i in range(Nw):
    xwr1.append(x1[i] * rectangle(i))

xwr2 = []
for i in range(Nw):
    xwr2.append(x2[i] * rectangle(i))

# plt.plot(xwr1)
# plt.plot(xwr2)
# plt.show()

# sinusoida ce utilizeaza cea de-a 2a frecventa are
# o probabilitate mai mare sa prinda mai multe semnale

# 3

# a

nsamples = 3 * 24  # (3 zile x 24h)
f = open('trafic.csv')

cnt = 1
samples = []

for lin in f:
    if cnt > nsamples:
        break
    else:
        # primul sample apare ciudat for some reason
        if cnt != 1:
            samples.append(int(lin.strip()))
    cnt += 1

# b

avg = []
for windowsize in [5, 9, 13, 17]:
    average = np.convolve(samples, np.ones(windowsize) / windowsize, 'valid')  # rezultatele mediei mobile
    avg.append(average)
    plt.plot(average)

plt.show()



