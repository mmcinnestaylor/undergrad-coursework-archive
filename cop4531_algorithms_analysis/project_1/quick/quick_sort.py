import matplotlib.pyplot as plt
import numpy as np

x, y = np.loadtxt('quicksort.txt', delimiter=',', unpack=True)
plt.plot(x,y, label='Runtime')

plt.xlabel('Input Size')
plt.ylabel('Seconds')
plt.title('Runtime Complexity\nQuicksort')
plt.legend()
plt.show()
