import matplotlib.pyplot as plt
import numpy as np

with open('uniform_data.txt', 'r') as f:
    data = np.loadtxt(f)

plt.hist(data, bins=100)
plt.show()