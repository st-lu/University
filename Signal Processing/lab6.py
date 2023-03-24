# Luana Strimbeanu 343

import dictlearn
import numpy as np
from matplotlib import image
from dictlearn import methods
from matplotlib import pyplot as plt
from dictlearn import DictionaryLearning
from sklearn.datasets import make_sparse_coded_signal
from sklearn.feature_extraction.image import extract_patches_2d
from sklearn.feature_extraction.image import reconstruct_from_patches_2d
from sklearn.preprocessing import normalize

p = 8 # dimensiunea unui patch (numar de pixeli)
s = 6 # sparsitatea
N = 1000 # numarul total de patch-uri
n = 256 # numarul de atomi din dictionar
K = 50 # numarul de iteratii DL
sigma = 0.075 # deviatia standard a zgomotului


#1
#a
I = image.imread('barbara.png')
#b
Inoisy = I + sigma * np.random.rand(I.shape[0], I.shape[1])
#c
Ynoisy = extract_patches_2d(Inoisy, (p, p))
Ynoisy = Ynoisy.reshape(Ynoisy.shape[0], -1)
Ynoisy -= np.mean(Ynoisy, axis=0)
Ynoisy = Ynoisy.transpose()
#d
Y = Ynoisy[:,np.random.choice(Ynoisy.shape[1], N, replace=False)]


#2

#a
D0 = np.random.randn(Ynoisy.shape[0], n)

#b
D0 = normalize(D0, axis=0, norm='max')

dl = DictionaryLearning(n_components=n,max_iter=K,fit_algorithm='ksvd',n_nonzero_coefs=s,
                        code_init=None,dict_init=D0,params=None,data_sklearn_compat=False)
dl.fit(Y)
D = dl.D_

#3

# a
Xc, err = methods.omp(Ynoisy, D, algorithm='omp', n_nonzero_coefs=s)
# b
Yc = D*Xc
Yc += np.mean(Ynoisy, axis=0)
# c
Ic = reconstruct_from_patches_2d(Yc, (n,n))

#4

#a
plt.imshow(I)
plt.show()
plt.imshow(Inoisy)
plt.show()
plt.imshow(Ic)
plt.show()

#b
def psnr(img1, img2):
    mse = np.mean((img1 - img2) ** 2)
    if(mse == 0):
        return 0
    max_pixel = 255
    psnr = 20 * np.log10(max_pixel / np.sqrt(mse))
    return psnr


print(psnr(I, Inoisy))
print(psnr(I, Ic))





