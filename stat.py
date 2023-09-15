import os
import numpy as np

# Define the root directory
root_directory = "./results/"

# Define a function to process a single file
def process_file(filepath):
    data = []

    # Open and read the file
    with open(filepath, "r") as file:
        for line in file:
            val = float(line.split()[0])
            data.append(val)

    data = np.array(data)

    # Print statistics for the current file
    print(f"Stats for {filepath}")
    print(f"Average: {np.mean(data)}")
    print(f"STD: {np.std(data)}")
    print()

# Recursively traverse the directory
for root, _, files in os.walk(root_directory):
    for filename in files:
        if filename.endswith(".txt"):  # Make sure it's a .txt file
            filepath = os.path.join(root, filename)
            process_file(filepath)
