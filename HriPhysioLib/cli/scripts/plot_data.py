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
 
 /* ================================================================================
 * Copyright: (C) 2024, Trushar Ghanekar,
 *     Hochschule Bonn-Rhein-Sieg (H-BRS), All rights reserved.
 * 
 * Author: 
 *     Trushar Ghanekar <trushar.ghanekar@smail.inf.h-brs.de>
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

    # Apply Hilbert transform to the raw ECG data
    analytic_signal_raw = hilbert(trimmed_raw_ecg_data)
    magnitude_raw = np.abs(analytic_signal_raw)

    # Compute the phase of both raw and Hilbert-transformed data
    phase_raw = np.angle(analytic_signal_raw)
    phase_hilbert = np.angle(trimmed_hilbert_transformed_data + 1j * np.imag(trimmed_hilbert_transformed_data))

    # Plot amplitude and phase changes
    fig, axs = plt.subplots(2, 1, figsize=(10, 8))

    # Plot the amplitudes
    axs[0].plot(trimmed_raw_ecg_data, label='Raw ECG Data', color='blue', alpha=0.7)
    axs[0].plot(magnitude_raw, label='Hilbert Transformed Magnitude', color='green', linestyle='--', alpha=0.7)
    axs[0].set_title('Amplitude Comparison')
    axs[0].set_xlabel('Sample Index')
    axs[0].set_ylabel('Amplitude')
    axs[0].legend()

    # Plot the phases
    axs[1].plot(phase_raw, label='Raw ECG Phase', color='blue', linewidth=2)
    axs[1].plot(phase_hilbert, label='Hilbert Transformed Phase', color='red', linewidth=2)
    axs[1].set_title('Phase Comparison')
    axs[1].set_xlabel('Sample Index')
    axs[1].set_ylabel('Phase (radians)')
    axs[1].legend()

    # Adjust layout and show plot
    plt.tight_layout()
    plt.show()

# Example usage
raw_ecg_file = './cli/data/ecg_data.csv'
hilbert_transformed_file = './cli/data/ecg_data_with_hilbert.csv'

plot_ecg_data_with_hilbert(raw_ecg_file, hilbert_transformed_file)
