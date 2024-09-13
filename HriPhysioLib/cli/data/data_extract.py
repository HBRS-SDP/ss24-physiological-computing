import neurokit2 as nk
import pandas as pd
import os

# Load ECG data (returns a NumPy array)
ecg = nk.data('ecg_1000hz.csv')

# Convert the NumPy array to a Pandas DataFrame
df_ecg = pd.DataFrame(ecg)

# Define the path where you want to save the file
save_directory = os.path.join('HriPhysioLib', 'cli', 'data')

# Ensure the directory exists
os.makedirs(save_directory, exist_ok=True)

# Save the DataFrame as a CSV file in the specified directory
file_path = os.path.join(save_directory, 'ecg_data.csv')
df_ecg.to_csv(file_path, index=False)
