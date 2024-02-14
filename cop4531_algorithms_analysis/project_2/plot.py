import matplotlib.pyplot as plt
import numpy as np

x, y1, y2 = np.loadtxt('part1_output.txt', delimiter=',', unpack=True)
plt.plot(x,y1,label='Actual')
plt.plot(x, y2,label='Ideal')

plt.ylim(0, 2500)

plt.xlabel('Load Factor')
plt.ylabel('Number of probes')
plt.title('Number of Required Probes\nNew Method')
plt.legend()
plt.show()
