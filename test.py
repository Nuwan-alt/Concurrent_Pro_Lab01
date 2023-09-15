import matplotlib.pyplot as plt
import stat  # Import your stat.py module with data

# Extract data from stat.py
# Replace these with the actual data structures from stat.py
case1_data = {
    'threads': [1, 2, 4, 8],
    'serial_times': [10.5, 6.2, 4.1, 3.5],
    'mutex_times': [12.1, 7.9, 5.8, 4.2],
}

case2_data = {
    'threads': [1, 2, 4, 8],
    'serial_times': [9.5, 5.9, 3.8, 3.2],
    'mutex_times': [11.2, 7.3, 5.2, 4.0],
}

case3_data = {
    'threads': [1, 2, 4, 8],
    'serial_times': [8.8, 5.3, 3.6, 3.0],
    'mutex_times': [10.6, 6.7, 4.7, 3.8],
}

# Create three subplots (one for each case)
fig, axs = plt.subplots(1, 3, figsize=(15, 5))

# Plot each case
for i, data in enumerate([case1_data, case2_data, case3_data]):
    ax = axs[i]
    ax.bar(data['threads'], data['serial_times'], label='Serial', color='blue', alpha=0.6)
    ax.bar(data['threads'], data['mutex_times'], label='Mutex', color='green', alpha=0.6, bottom=data['serial_times'])

    ax.set_xlabel('Number of Threads')
    ax.set_ylabel('Average Execution Time')
    ax.set_title(f'Case {i+1}')
    ax.set_xticks(data['threads'])
    ax.legend()

plt.tight_layout()
plt.show()