import numpy as np
import matplotlib.pyplot as plt

N = 100
x = np.arange(0, N, 1)
y = np.arange(0, N, 1)

phi = np.fromfile("phi.avd", dtype="f8").reshape([N, N])

plt.figure()
plt.axis("off")

im = plt.imshow(phi, cmap="jet", interpolation="bessel")
plt.colorbar(im)

plt.contour(x, y, phi, linewidths=0.5, colors="k")

plt.show()

