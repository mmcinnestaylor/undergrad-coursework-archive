# Marlan McInnes-Taylor mm05f
import numpy as np
import matplotlib.pyplot as plt

temperature = int(input())
currentTemp = np.zeros((temperature + 2, temperature + 2))
iterations = 0

# Initialize matrix with leftmost column set to initial temperature
for i in range(0, temperature + 2):
    currentTemp[i, 0] = temperature

# Calculate heat distribution until there is no change between iterations, or 3000 iterations have ocured
while iterations < 3000:
    oldTemp = np.copy(currentTemp)
    iterations += 1

    for i in range(1, temperature + 1):
        for j in range(1, temperature + 1):
            currentTemp[i,j] = .25 * (oldTemp[i - 1,j] + oldTemp[i + 1,j] + oldTemp[i,j - 1] + oldTemp[i,j + 1])

    if np.array_equal(oldTemp, currentTemp):
        break

# Plot heat distribution and assign color based on 8 choices 
for i in range(1, temperature + 1):
    for j in range(1, temperature + 1):
        if currentTemp[i,j] <= (1/8) * temperature:
            plt.plot(j, i, color='darkblue', marker='o')
        elif currentTemp[i,j] <= (2/8) * temperature:
            plt.plot(j, i, color='blue', marker='o')
        elif currentTemp[i,j] <= (3/8) * temperature:
            plt.plot(j, i, color='aqua', marker='o')
        elif currentTemp[i,j] <= (4/8) * temperature:
            plt.plot(j, i, color='lawngreen', marker='o')
        elif currentTemp[i,j] <= (5/8) * temperature:
            plt.plot(j, i, color='yellow', marker='o')
        elif currentTemp[i,j] <= (6/8) * temperature:
            plt.plot(j, i, color='orange', marker='o')
        elif currentTemp[i,j] <= (7/8) * temperature:
            plt.plot(j, i, color='red', marker='o')
        else:
            plt.plot(j, i, color='darkred', marker='o')
plt.show()
