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

import os
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

    # Create subplots for the raw ECG, Hilbert-transformed data, and phase plots
    plt.figure(figsize=(10, 10))

    # Plot 1: Raw ECG data
    plt.subplot(3, 1, 1)
    plt.plot(trimmed_raw_ecg_data, label='Raw ECG Data', color='green', linewidth=1.5)
    plt.title('Raw ECG Data')
    plt.xlabel('Sample Index')
    plt.ylabel('Amplitude')
    plt.legend()

    # Plot 2: Hilbert Transformed Data
    plt.subplot(3, 1, 2)
    plt.plot(trimmed_hilbert_transformed_data, label='Hilbert Transformed Data', color='orange', linewidth=1.5)
    plt.title('Hilbert Transformed Data')
    plt.xlabel('Sample Index')
    plt.ylabel('Amplitude')
    plt.legend()

    # Plot 3: Phases of Raw and Hilbert Transformed Data
    plt.subplot(3, 1, 3)
    plt.plot(phase_raw, label='Raw ECG Phase', color='blue', linewidth=2)
    plt.plot(phase_hilbert, label='Hilbert Transformed Phase', color='red', linewidth=2)
    plt.title('Raw ECG Phase and Hilbert Transformed Phase')
    plt.xlabel('Sample Index')
    plt.ylabel('Phase (radians)')
    plt.legend()

    # Adjust layout and show the plots
    plt.tight_layout()
    plt.show()

# Example usage

# Get the directory where the script is located
script_dir = os.path.dirname(os.path.abspath(__file__))

# Define the file paths relative to the script directory
raw_ecg_file = os.path.join(script_dir, '../data/ecg_data.csv')
hilbert_transformed_file = os.path.join(script_dir, '../data/ecg_data_with_hilbert.csv')

plot_ecg_data_with_hilbert(raw_ecg_file, hilbert_transformed_file)
