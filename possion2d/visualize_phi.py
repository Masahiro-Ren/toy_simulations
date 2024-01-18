import numpy as np
import matplotlib.pyplot as plt

N = 100
x = np.linspace(0, 1, N)
y = np.linspace(0, 1, N)

phi = np.fromfile("phi.avd", dtype="f8").reshape([N, N])

extent = [x[0] - 0.005, x[-1] + 0.005, y[0] - 0.005, y[-1]+0.005]

plt.figure()
plt.axis("off")

im = plt.imshow(phi, cmap="jet", interpolation="bessel", extent=extent)
plt.colorbar(im)

plt.contour(x, y, phi, levels=10, linewidths=0.5, colors="k")

plt.savefig("phi2d.png")
plt.show()

