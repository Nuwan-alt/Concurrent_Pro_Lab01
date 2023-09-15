
import os
import numpy as np
import matplotlib.pyplot as plt

# Define the root directory
root_directory = "./results/"
mutex_data = [[0,0,0,0],[0,0,0,0],[0,0,0,0]]
rw_data = [[0,0,0,0],[0,0,0,0],[0,0,0,0]]
serial_data = [[0,0,0,0],[0,0,0,0],[0,0,0,0]]
# Define a function to process a single file
def process_file(filepath, filename):
    data = []

    # Open and read the file
    with open(filepath, "r") as file:
        for line in file:
            val = float(line.split()[0])
            data.append(val)

    data = np.array(data)
    avg = round(np.mean(data),3)

    if(filename.startswith("Mutex")):
        if(filename.__contains__("Case1")):
            if(filename.endswith("1.txt")):
                mutex_data[0][0] = avg
            elif(filename.endswith("2.txt")):
                mutex_data[0][1] = avg
            elif(filename.endswith("4.txt")):
                mutex_data[0][2] = avg
            elif(filename.endswith("8.txt")):
                mutex_data[0][3] = avg
        elif(filename.__contains__("Case2")):
            if(filename.endswith("1.txt")):
                mutex_data[1][0] = avg
            elif(filename.endswith("2.txt")):
                mutex_data[1][1] = avg
            elif(filename.endswith("4.txt")):
                mutex_data[1][2] = avg
            elif(filename.endswith("8.txt")):
                mutex_data[1][3] = avg
        if(filename.__contains__("Case3")):
            if(filename.endswith("1.txt")):
                mutex_data[2][0] = avg
            elif(filename.endswith("2.txt")):
                mutex_data[2][1] = avg
            elif(filename.endswith("4.txt")):
                mutex_data[2][2] = avg
            elif(filename.endswith("8.txt")):
                mutex_data[2][3] = avg

    if(filename.startswith("RW")):
        if(filename.__contains__("Case1")):
            if(filename.endswith("1.txt")):
                rw_data[0][0] = avg
            elif(filename.endswith("2.txt")):
                rw_data[0][1] = avg
            elif(filename.endswith("4.txt")):
                rw_data[0][2] = avg
            elif(filename.endswith("8.txt")):
                rw_data[0][3] = avg
        elif(filename.__contains__("Case2")):
            if(filename.endswith("1.txt")):
                rw_data[1][0] = avg
            elif(filename.endswith("2.txt")):
                rw_data[1][1] = avg
            elif(filename.endswith("4.txt")):
                rw_data[1][2] = avg
            elif(filename.endswith("8.txt")):
                rw_data[1][3] = avg
        if(filename.__contains__("Case3")):
            if(filename.endswith("1.txt")):
                rw_data[2][0] = avg
            elif(filename.endswith("2.txt")):
                rw_data[2][1] = avg
            elif(filename.endswith("4.txt")):
                rw_data[2][2] = avg
            elif(filename.endswith("8.txt")):
                rw_data[2][3] = avg

    if(filename.startswith("Serial")):
        if(filename.__contains__("Case1")):
                serial_data[0][0] = avg

        elif(filename.__contains__("Case2")):
                serial_data[1][0] = avg

        if(filename.__contains__("Case3")):
                serial_data[2][0] = avg

    print(f"Stats for {filename}")
    print(f"Average: {np.mean(data)}")
    print(f"STD: {np.std(data)}")
    print()

# Recursively traverse the directory
for root, _, files in os.walk(root_directory):
    for filename in files:
        if filename.endswith(".txt"):  # Make sure it's a .txt file
            filepath = os.path.join(root, filename)
            process_file(filepath, filename)


num_threads = [1, 2, 4, 8]

# Set the width of the bars
bar_width = 0.2

# Generate positions for bars for each case
positions = np.arange(len(num_threads))
print(serial_data)
print(mutex_data)
print(rw_data)
#
# for j in range (0,3):
#     data = {
#         'Serial': serial_data[j],  # Average execution times for Serial case
#         'Mutex': mutex_data[j],  # Average execution times for Mutex case
#         'ReadWriteLock': rw_data[j],  # Average execution times for ReadWriteLock case
#     }
#
#     for i, (case, times) in enumerate(data.items()):
#         # Adjust the x positions for each set of bars to avoid overlap
#         x_positions = positions + i * bar_width
#
#         # Create the bar chart
#         plt.bar(x_positions, times, bar_width, label=case)
#
#     # Customize the plot
#     plt.xlabel('Number of Threads')
#     plt.ylabel('Average Execution Time')
#     plt.title(f'Scenario {j+1} Average Execution Time vs. Number of Threads')
#     plt.xticks(positions + bar_width * (len(data) - 1) / 2, num_threads)
#     plt.legend()
#
#     # Show the plot
#     plt.tight_layout()
#     plt.show()

for j in range(3):
    data = {
        'Serial': serial_data[j],  # Average execution times for Serial case
        'Mutex': mutex_data[j],  # Average execution times for Mutex case
        'ReadWriteLock': rw_data[j],  # Average execution times for ReadWriteLock case
    }

    for i, (case, times) in enumerate(data.items()):
        # Adjust the x positions for each set of bars to avoid overlap
        x_positions = positions + i * bar_width

        # Create the bar chart
        plt.bar(x_positions, times, bar_width, label=case)

    # Customize the plot
    plt.xlabel('Number of Threads')
    plt.ylabel('Average Execution Time')
    plt.title(f'Scenario {j+1} Average Execution Time vs. Number of Threads')
    plt.xticks(positions + bar_width * (len(data) - 1) / 2, num_threads)
    plt.legend()

    # Set the y-axis range to 0-70000
    plt.ylim(0, 70000)

    # Show the plot
    plt.tight_layout()
    plt.show()
