'''
    Ex1

    fs = 44.1kHz
    distanta = 1Hz

    Avem distanta dintre 2 bin-uri = fs / N => N = fs / distanta
    Asadar N = 44100 / 1 = 44100 sample-uri
'''

import numpy as np
import matplotlib.pyplot as plt
import scipy

f1 = 1000
f2 = 1100
fs = 8000

time_of_view = 0.25
n_samples = fs * time_of_view + 1
time = np.linspace(0, time_of_view, int(n_samples))


def sine(frequency, time, amplitude=1, phase=0):
    return amplitude * np.sin(2 * np.pi * frequency * time + phase)


def rectangle_window(n):
    wdw = np.zeros(n)
    for i in range(n):
        wdw[i] = 1.

    return wdw


def hanning_window(n):
    wdw = np.zeros(n)
    for i in range(n):
        wdw[i] = 0.5 * (1 - np.cos(2 * np.pi * i / n))

    return wdw


def hamming_window(n):
    wdw = np.zeros(n)
    for i in range(n):
        wdw[i] = 0.54 - 0.46 * np.cos(2 * np.pi * i / n)

    return wdw


def blackman_window(n):
    wdw = np.zeros(n)
    for i in range(n):
        wdw[i] = 0.42 - 0.5 * np.cos(2 * np.pi * i / n) + 0.08 * np.cos(6 * np.pi * i / n)

    return wdw


def flattop_window(n):
    wdw = np.zeros(n)
    for i in range(n):
        wdw[i] = 0.22 - 0.42 * np.cos(2 * np.pi * i / n) + 0.28 * np.cos(6 * np.pi * i / n)
        + 0.007 * np.cos(8 * np.pi * i / n)

    return wdw


def apply_window(x, w):
    # am considerat aplicarea unei ferestre ca fiind inmultirea w[i]*x[i] pe primele esantioane
    # ale semnalului(care corespund ferestrei) si 0 in rest
    res = np.zeros(x.shape)
    for i in range(len(res)):
        if i < w.shape[0]:
            res[i] = x[i] * w[i]
        else:
            res[i] = 0.

    return res


def ex2a():
    fig, axs = plt.subplots(6, figsize=(6, 8))
    fig.tight_layout(pad=3.0)

    f_100 = 100
    n_samples_a = 200
    time_a = np.linspace(0, time_of_view, int(n_samples_a))

    sine100 = (sine(f_100, time_a))

    w1 = rectangle_window(200)
    filtered1 = apply_window(sine100, w1)

    w2 = hanning_window(200)
    filtered2 = apply_window(sine100, w2)

    w3 = hamming_window(200)
    filtered3 = apply_window(sine100, w3)

    w4 = blackman_window(200)
    filtered4 = apply_window(sine100, w4)

    w5 = flattop_window(200)
    filtered5 = apply_window(sine100, w5)

    axs[0].set_title('Semnalul initial')
    axs[0].plot(time_a, sine100)

    axs[1].set_title('Fereastra dreptunghiulara')
    axs[1].plot(time_a, filtered1)

    axs[2].set_title('Fereastra Hanning')
    axs[2].plot(time_a, filtered2)

    axs[3].set_title('Fereastra Hamming')
    axs[3].plot(time_a, filtered3)

    axs[4].set_title('Fereastra Blackman')
    axs[4].plot(time_a, filtered4)

    axs[5].set_title('Fereastra Flat Top')
    axs[5].plot(time_a, filtered5)

    plt.show()


def ex2b():
    fig, axs = plt.subplots(3, figsize=(8, 6))
    fig.tight_layout(pad=3.0)

    time_of_view_b = 1
    fs = 8000
    n_samples_b = time_of_view_b * fs + 1
    time_b = np.linspace(0, time_of_view_b, int(n_samples_b))

    f1 = 1000
    f2 = 1100
    sine1 = sine(f1, time_b)
    sine2 = sine(f2, time_b)

    axs[0].set_title('Semnalele initiale')
    axs[0].plot(time_b, sine1)
    axs[0].plot(time_b, sine2)

    w = rectangle_window(1000)

    fft1 = np.abs(np.fft.fft(sine1, 8000))
    fft2 = np.abs(np.fft.fft(sine2, 8000))

    N_fft1 = len(fft1)
    N_fft2 = len(fft2)

    fft1_filtered = np.abs(np.fft.fft(apply_window(sine1, w)))
    fft2_filtered = np.abs(np.fft.fft(apply_window(sine2, w)))

    N_fft1_filtered = len(fft1_filtered)
    N_fft2_filtered = len(fft2_filtered)

    axs[1].set_title('FFT-ul semnalelor initiale')
    axs[1].plot(fft1[:N_fft1 // 2])
    axs[1].plot(fft2[:N_fft2 // 2])

    axs[2].set_title('FFT-ul ferestrelor')
    axs[2].plot(fft1_filtered[:N_fft1_filtered // 2])
    axs[2].plot(fft2_filtered[:N_fft2_filtered // 2])

    plt.show()


def ex3():
    n_cars = 3 * 24  # 3 zile * 24 de esantioane pe zi
    time_3 = np.linspace(0, 72, 72)
    f = open('trafic.csv')
    cars = []

    f.readline()
    for _ in range(n_cars):  # citesc datele ca dintr-un fisier text oarecare
        x = int(f.readline().strip())
        cars.append(x)
    f.close()

    cars = np.array(cars)

    plt.figure()
    plt.grid(True)
    data_line, = plt.plot(time_3, cars, label='Data')

    lines_legend = [data_line]  # legenda plot-ului
    for w_size in [5, 9, 13, 17]:
        cars_ext = np.pad(cars, (w_size - 1, 0), 'constant')

        moving_avg = np.convolve(cars_ext, np.ones(w_size) / w_size, 'valid')  # rezultatele mediei mobile

        print("Moving_avg pentru w = " + str(w_size) + ":")
        print(moving_avg)

        line, = plt.plot(time_3[w_size:], moving_avg[w_size:], label='W_size = ' + str(w_size))
        lines_legend.append(line)

    plt.legend(handles=lines_legend)
    plt.show()


if __name__ == '__main__':
    ex2a()
    ex2b()
    ex3()