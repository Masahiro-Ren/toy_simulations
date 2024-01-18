import numpy as np
import matplotlib.pyplot as plt

N = 100

elec = np.fromfile("electric.avd", dtype="f8").reshape([N * N, 3]).T

x = np.linspace(0.0, 1.0, 100)
y = np.linspace(0.0, 1.0, 100)

Ex = elec[0].reshape([N, N])
Ey = elec[1].reshape([N, N])
Esqrt = elec[2].reshape([N, N])

extent = [x[0] - 0.005, x[-1] + 0.005, y[0] - 0.005, y[-1]+0.005]

plt.figure()
plt.axis("off")

im = plt.imshow(Esqrt, cmap="jet", interpolation="bessel", extent=extent)
plt.colorbar(im)
# plt.streamplot(x, y, Ey, Ex, linewidth=1,density=2, color="k")
plt.quiver(x, y, Ey, Ex)

plt.savefig("electric2d.png")
plt.show()

