import csv
import os
import matplotlib.pyplot as plt
import neurokit2 as nk

# Define the folder path
folder_path = '../data'

# Create the folder if it doesn't exist
os.makedirs(folder_path, exist_ok=True)

# Generate sample ECG data
ecg_data = nk.ecg_simulate(duration=10, noise=0.05, heart_rate=70)

# Save the ECG data as a CSV file in the data folder
csv_file_path = os.path.join(folder_path, 'ecg_data.csv')
with open(csv_file_path, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['ECG_Data'])
    for value in ecg_data:
        writer.writerow([value])

# Plot the ECG data
plt.plot(ecg_data)
plt.xlabel('Measurement #')
plt.ylabel('Amplitude')
plt.title('ECG Data')

# Save the plot as a PNG file in the data folder
png_file_path = os.path.join(folder_path, 'ecg_data.png')
plt.savefig(png_file_path)

plt.show()  # Optional: Show the plot on the screen
