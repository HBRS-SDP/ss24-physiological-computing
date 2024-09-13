import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.signal import hilbert

def plot_ecg_data_with_hilbert(raw_ecg_file, hilbert_transformed_file):
    # Load the raw ECG data and Hilbert-transformed data
    ecg_data = pd.read_csv(raw_ecg_file)
    ecg_data_with_hilbert = pd.read_csv(hilbert_transformed_file)

    # Extract raw ECG data and Hilbert-transformed data
    raw_ecg_data = ecg_data['ECG_Data']
    hilbert_transformed_data = ecg_data_with_hilbert.iloc[:, 1]  # Assuming second column contains transformed data

    # Ensure both datasets are of the same length
    min_length = min(len(raw_ecg_data), len(hilbert_transformed_data))
    trimmed_raw_ecg_data = raw_ecg_data[:min_length]
    trimmed_hilbert_transformed_data = hilbert_transformed_data[:min_length]

    # Apply Hilbert transform to the raw ECG data for phase calculation
    analytic_signal_raw = hilbert(trimmed_raw_ecg_data)

    # Compute the phase of both raw and Hilbert-transformed data
    phase_raw = np.angle(analytic_signal_raw)
    phase_hilbert = np.angle(trimmed_hilbert_transformed_data + 1j * np.imag(trimmed_hilbert_transformed_data))

    # Plot the phases with distinct colors
    plt.figure(figsize=(8, 4))

    # Plot the corrected raw ECG phase in blue
    plt.plot(phase_raw, label='Raw ECG Phase', color='blue', linewidth=2)

    # Plot the Hilbert transformed phase in red
    plt.plot(phase_hilbert, label='Hilbert Transformed Phase', color='red', linewidth=2)

    # Add title, labels, and legend
    plt.title('Raw ECG Phase and Hilbert Transformed Phase')
    plt.xlabel('Sample Index')
    plt.ylabel('Phase (radians)')
    plt.legend()

    # Show the plot
    plt.tight_layout()
    plt.show()

# Example usage
raw_ecg_file = './ecg_data.csv'
hilbert_transformed_file = './ecg_data_with_hilbert.csv'

plot_ecg_data_with_hilbert(raw_ecg_file, hilbert_transformed_file)
