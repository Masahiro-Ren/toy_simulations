import numpy as np
import matplotlib.pyplot as plt

N = 100

elec = np.fromfile("electric.avd", dtype="f8").reshape([N * N, 3]).T

Ex = elec[0].reshape([N, N])
Ey = elec[1].reshape([N, N])
Esqrt = elec[2].reshape([N, N])

plt.figure()
plt.axis("off")

im = plt.imshow(Esqrt, cmap="jet", interpolation="bessel")
plt.colorbar(im)

plt.show()

