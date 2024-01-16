import numpy as np
import matplotlib.pyplot as plt

Temp = np.fromfile("heat.dat", "f8")

Temp = Temp.reshape([12, 12])

fig, ax = plt.subplots()

heatmap = ax.pcolor(Temp, cmap=plt.cm.jet)
ax.set_xticks(np.arange(Temp.shape[0]), minor=False)
ax.set_yticks(np.arange(Temp.shape[1]), minor=False)

plt.show()
