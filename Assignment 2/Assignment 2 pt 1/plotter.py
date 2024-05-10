import matplotlib.pyplot as plt
import pandas as pd

# Load data from CSV file
data = pd.read_csv('newobs.txt')

# Extract columns as numpy arrays
vertices = data['Vertices'].values
dp_time = data[' Avg.Time Taken DP'].values
greedy_time = data[' Avg.Time Taken Greedy'].values

# Plot the data
plt.plot(vertices, dp_time, label='DP')
plt.plot(vertices, greedy_time, label='Greedy')
plt.xlabel('Number of vertices')
plt.ylabel('Time (seconds)')
plt.title('Time taken for Greedy vs. DP')
plt.legend()
plt.show()
