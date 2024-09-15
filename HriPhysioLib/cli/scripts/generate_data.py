"""
* ================================================================================
 * Copyright: (C) 2024, Vedika Chauhan,
 *     Hochschule Bonn-Rhein-Sieg (H-BRS), All rights reserved.
 * 
 * Author: 
 *     Vedika Chauhan <vedika.chauhan@smail.inf.h-brs.de>
 * 
 * CopyPolicy: Released under the terms of the MIT License.
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */ 
 
"""
import csv
import os
import os.path as path
import matplotlib.pyplot as plt
import neurokit2 as nk

# Generate sample ECG data
ecg_data = nk.ecg_simulate(duration=10, noise=0.05, heart_rate=70)

# Get the directory path where the script is located
script_dir = path.dirname(path.abspath(__file__))

# Define the directory and file path for saving the CSV
data_dir = path.join(script_dir, '../data')
file_path = path.join(data_dir, 'ecg_data.csv')

# Ensure the directory exists; if not, create it
if not os.path.exists(data_dir):
    os.makedirs(data_dir)

# Store data as CSV
with open(file_path, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['ECG_Data'])
    for value in ecg_data:
        writer.writerow([value])

# Plot data
plt.plot(ecg_data)
plt.xlabel('Measurement #')
plt.ylabel('Amplitude')
plt.title('ECG Data')
plt.savefig('ecg_data.png')
