import matplotlib.pyplot as plt
import numpy as np

x, y = np.loadtxt('merge_sort.txt', delimiter=',', unpack=True)
plt.plot(x,y, label='Runtime')

plt.xlabel('Input Size')
plt.ylabel('Seconds')
plt.title('Runtime Complexity\nMerge-Sort')
plt.legend()
plt.show()
