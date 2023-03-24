import numpy as np
import matplotlib.pyplot as plt
from scipy import misc, ndimage
from scipy.fft import dctn, idctn

import cv2  # video processing


# 1
Q_jpeg = [
    [16, 11, 10, 16, 24, 40, 51, 61],
    [12, 12, 14, 19, 26, 28, 60, 55],
    [14, 13, 16, 24, 40, 57, 69, 56],
    [14, 17, 22, 29, 51, 87, 80, 62],
    [18, 22, 37, 56, 68, 109, 103, 77],
    [24, 35, 55, 64, 81, 104, 113, 92],
    [49, 64, 78, 87, 103, 121, 120, 101],
    [72, 92, 95, 98, 112, 100, 103, 99]
]

img = misc.ascent()


def to_jpeg(img, Q_jpeg):
    imgH = img.shape[0]
    imgW = img.shape[1]
    y_nnz = 0
    y_jpeg_nnz = 0
    img_jpeg = np.zeros((imgH, imgW))

    for h in range(int(imgH / 8)):
        for w in range(int(imgW / 8)):
            x = img[(h * 8):((h + 1) * 8), (w * 8):((w + 1) * 8)]
            y = dctn(x)
            y_jpeg = Q_jpeg * np.round(y / Q_jpeg)

            x_jpeg = idctn(y_jpeg)

            y_nnz += np.count_nonzero(y)
            y_jpeg_nnz += np.count_nonzero(y_jpeg)

            img_jpeg[(h * 8):((h + 1) * 8), (w * 8):((w + 1) * 8)] = x_jpeg

    # print('Componente în frecvență:' + str(y_nnz) +
    #       '\nComponente în frecvență după cuantizare: ' + str(y_jpeg_nnz))

    return img_jpeg


img_jpeg = to_jpeg(img, Q_jpeg).astype(np.uint8)
plt.imshow(img)
plt.show()
plt.imshow(img_jpeg)
plt.show()

# 2
img = misc.face()


# ITU-R BT.601 conversion
def rgb_to_ycbcr(R, G, B):
    Y = 16 + 65.738 * R / 256 + 129.057 * G / 256 + 25.064 * B / 256
    Cb = 128 - 37.945 * R / 256 - 74.494 * G / 256 + 112.439 * B / 256
    Cr = 128 + 112.439 * R / 256 - 94.154 * G / 256 - 18.285 * B / 256

    return Y, Cb, Cr


def ycbcr_to_rgb(Y, Cb, Cr):
    R = (298.082 * Y / 256 + 408.583 * Cr / 256 - 222.921).astype(np.uint8)
    G = (298.082 * Y / 256 - 100.291 * Cb / 256 - 208.120 * Cr / 256 + 135.576).astype(np.uint8)
    B = (298.082 * Y / 256 + 516.412 * Cb / 256 - 276.836).astype(np.uint8)

    return R, G, B


def to_rgb_jpeg(img, Q_jpeg):
    R = img[:, :, 0]
    G = img[:, :, 1]
    B = img[:, :, 2]

    Y, Cb, Cr = rgb_to_ycbcr(R, G, B)
    Y = to_jpeg(Y, Q_jpeg)
    Cb = to_jpeg(Cb, Q_jpeg)
    Cr = to_jpeg(Cr, Q_jpeg)
    R_jpeg, G_jpeg, B_jpeg = ycbcr_to_rgb(Y, Cb, Cr)
    img_jpeg = np.stack([R_jpeg, G_jpeg, B_jpeg], axis=2)

    return img_jpeg


img_jpeg = to_rgb_jpeg(img, Q_jpeg)
plt.imshow(img)
plt.show()
plt.imshow(img_jpeg)
plt.show()

# 3
target_mse = 1
quality = 1
img_jpeg = to_rgb_jpeg(img, quality*np.ceil(np.array(Q_jpeg) / quality))
quality += 1
mse = np.mean((img-img_jpeg) ** 2)

while mse > target_mse:
    # used ceil to avoid division by 0
    img_jpeg = to_rgb_jpeg(img, quality*np.ceil(np.array(Q_jpeg) / quality))
    quality += 1
    mse = np.mean((img-img_jpeg) ** 2)
    print(mse, quality)

plt.imshow(img_jpeg)
plt.show()


# 4

vid = cv2.VideoCapture('horses.mp4')

success = True
while success:
    success, img = vid.read()
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

    img_jpeg = to_rgb_jpeg(img)
    img_jpeg = cv2.cvtColor(img_jpeg, cv2.COLOR_RGB2BGR)

    cv2.imshow('imagine',img_jpeg)

vid.release()
