import matplotlib.pyplot as plt
import numpy as np

# Sample data structure (replace this with your actual data)
data = {
    'Serial': [0.1, 0, 0, 0],  # Average execution times for Serial case
    'Mutex': [0.08, 0.18, 0.28, 0.38],  # Average execution times for Mutex case
    'ReadWriteLock': [0.06, 0.16, 0.26, 0.36],  # Average execution times for ReadWriteLock case
}

# Number of threads used for the experiments
num_threads = [1, 2, 4, 8]  # Adjust this list according to your data

# Set the width of the bars
bar_width = 0.2

# Generate positions for bars for each case
positions = np.arange(len(num_threads))

# Plotting
for i, (case, times) in enumerate(data.items()):
    # Adjust the x positions for each set of bars to avoid overlap
    x_positions = positions + i * bar_width

    # Create the bar chart
    plt.bar(x_positions, times, bar_width, label=case)

# Customize the plot
plt.xlabel('Number of Threads')
plt.ylabel('Average Execution Time')
plt.title('Average Execution Time vs. Number of Threads')
plt.xticks(positions + bar_width * (len(data) - 1) / 2, num_threads)
plt.legend()

# Show the plot
plt.tight_layout()
plt.show()