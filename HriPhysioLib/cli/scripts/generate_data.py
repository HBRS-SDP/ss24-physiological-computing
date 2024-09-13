import csv

import matplotlib.pyplot as plt
import neurokit2 as nk

# Generate sample ECG data
ecg_data = nk.ecg_simulate(duration=10, noise=0.05, heart_rate=70)

# Store data as CSV
with open('ecg_data.csv', mode='w', newline='') as file:
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
