import matplotlib.pyplot as plt

# Read data from file
with open('mom_normal_part_7_obs.txt', 'r') as file:
    data = file.readlines()[1:]  # Skip the first line (headers)

# Extract x and y values
x = []
y = []
for line in data:
    line = line.strip().split(',')
    x.append(int(line[0]))  # Assuming the first column contains integers
    y.append(float(line[1]))  # Assuming the second column contains floating-point numbers

# Plot the graph
plt.plot(x, y, marker='o', linestyle='-')

# Add labels and title
plt.xlabel('Divide Size')
plt.ylabel('Average Time (ms)')
plt.title('Average Time vs. Divide Size')

# Add grid
plt.grid(True)

# Show the graph
plt.show()