#Luana Strimbeanu 343

import numpy as np
import matplotlib.pyplot as plt
import scipy.signal


# 1
def rectangle(dim):
    w = np.ones(dim)
    return w


def hanning(dim):
    w = []
    for i in range(dim):
        w.append(0.5 * (1 - np.cos(2 * np.pi * i / dim)))
    return w


def hamming(dim):
    w = []
    for i in range(dim):
        w.append(0.54 - 0.46 * np.cos(2 * np.pi * i / dim))
    return w


def blackman(dim):
    w = []
    for i in range(dim):
        w.append((0.42 - 0.5 * np.cos(2 * np.pi * i / dim)
                  + 0.08 * np.cos(4 * np.pi * i / dim)))
    return w


def flattop(dim):
    w = []
    for i in range(dim):
        w.append(0.22 - 0.42 * np.cos(2 * np.pi * i / dim)
                 + 0.28 * np.cos(4 * np.pi * i / dim)
                 - 0.08 * np.cos(6 * np.pi * i / dim)
                 + 0.007 * np.cos(8 * np.pi * i / dim))
    return w


def hzResponse(window):
    w, h = scipy.signal.freqz(window)

    plt.plot(w, 20 * np.log10(abs(h)))
    plt.show()


# 2

# a
data = np.genfromtxt('trafic.csv')
data = data[1:]
x = np.fft.rfft(data)
X = np.abs(x)

plt.plot(X)
plt.show()

# b
# datele au fost esantionate la o ora (3600s) deci f = 1/3600
f = 1/3600
fN = f/2

# traficul este mai intens ziua, in special dimineata, seara si la pranz.
# in csv se observa o perioada variabila intre 7-9h zilnic (deci aprox 8h) in care traficul este mai mare
# asa ca vom filtra esantioanele cu frecventa mai mare de 8/24f = 1/3f
fT = f/3
fT = fT / fN  # normalizare

# c

# order = 7
# order = 10
order = 5
rp = 5
butterworthB, butterworthA = scipy.signal.butter(order, fT)
chebyshevB, chebyshevA = scipy.signal.cheby1(order, rp, fT)

# d
w, h = scipy.signal.freqz(butterworthB, butterworthA)
plt.plot(w, 20 * np.log10(np.abs(h) + 1))
plt.show()

w, h = scipy.signal.freqz(chebyshevB, chebyshevA)
plt.plot(w, 20 * np.log10(np.abs(h) + 1))
plt.show()

# e

butterworthFilter = scipy.signal.filtfilt(butterworthB, butterworthA, data)
chebyshevFilter = scipy.signal.filtfilt(chebyshevB, chebyshevA, data)

# am folosit variabila zile ca sa vad cum arata datele pe esantioane mai mici (ex. pt 2/3/5 zile)
zile = 24*7
plt.plot(data[:zile], label='Raw Data')
plt.plot(butterworthFilter[:zile], label='Butterworth Filter')
plt.plot(chebyshevFilter[:zile], label='Chebyshev Filter')

plt.legend()
plt.show()

# chebyshev filtreaza mai bine datele cu frecvente mari


# f
# obtinem rezultate bune cu ord = 7 si rp = 10

