# Luana Strimbeanu - Grupa 343

# 1
# a)
import math

import numpy as np

fs = 2000
T = 2*math.pi/2000
print(T)

# b) 1h = 3600s, 1 byte = 8 bits
bytes = round(3600/T * 4/8)

print("bytes: " + str(bytes))

# 2

# perioada lui x(t) = 2pi/200pi = 1/100
# perioada lui y(t) = 2pi/80pi = 1/40
# cmmdc 100 si 40 = 20 => perioada lui z(x) = 1/20

Tx = 2 * math.pi / 200 * math.pi
Ty = 2 * math.pi / 80 * math.pi
cmmdc = math.gcd(int(1/Tx), int(1/Ty))
Tz = 1/cmmdc

fs = 2 * math.pi / Tz
fN = 0.5 * fs

print("fN: " + str(fN))

# 3
import matplotlib.pyplot as plt

# a), b)
# t = axa reala
t = np.linspace(0, 0.03, num=60)
x = np.cos(520*math.pi*t + math.pi/3)
y = np.cos(280*math.pi*t - math.pi/3)
z = np.cos(120*math.pi*t + math.pi/3)

# fig, axs = plt.subplots(3)
# fig.suptitle('Plots')
# axs[0].plot(t, x, 'b')
# axs[1].plot(t, y, 'r')
# axs[2].plot(t, z, 'g')

# c), d)
fs = 200  # Hz
at = np.linspace(0, 0.03, int(fs * 0.03) + 1)
xn = np.cos(520*math.pi*at + math.pi/3)
yn = np.cos(280*math.pi*at - math.pi/3)
zn = np.cos(120*math.pi*at + math.pi/3)

fig, axs = plt.subplots(3)
fig.suptitle('Plots')
axs[0].plot(t, x, 'b')
axs[0].grid("true")
axs[0].stem(at, xn, 'white', markerfmt='C8p')
axs[1].plot(t, y, 'r')
axs[1].grid("true")
axs[1].stem(at, yn, 'white', markerfmt='C8p')
axs[2].plot(t, z, 'g')
axs[2].grid("true")
axs[2].stem(at, zn, 'white', markerfmt='C8p')

plt.show()

# 4

PsemnaldB = 80
SNRdB = 90
# SNR = Psemnal/Pzgomot
# SNRdb = 10log10SNR
# PsemnaldB = 10log10Psemnal
# PzgomotdB = 10log10Pzgomot
# SNRdB = 10log10SNR = 10log10(Psemnal/Pzgomot) =
#   = 10log10Psemnal - 10log10Pzgomot = PsemnaldB - PzgomotdB

PzgomotdB = abs(PsemnaldB - SNRdB)

print(PzgomotdB)


# 5
import scipy.io.wavfile as wav
import scipy.signal as signal
rate, x = wav.read('sound.wav')
f, t, s = signal.spectrogram(x, fs=rate)
fig = plt.figure()
plt.pcolormesh(t, f, 10*np.log10(s), shading='gouraud')
plt.ylabel('Frequency [Hz]')
plt.xlabel('Time [sec]')
plt.show()
# daca plotam puterea semnalului in decibeli obtinem
# un grafic pe care pare ca daca am pastra
# doar sunetele care au coordonata y aka valoarea in decibeli
# mai mare ca aprox 15, am izola cele 2 sunete
plt.plot(10*np.log10(s))
plt.show()
