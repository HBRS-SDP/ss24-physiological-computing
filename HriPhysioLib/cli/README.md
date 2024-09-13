## Updated README for CLI Testing Instructions

This README provides detailed instructions for testing the **Hilbert Transform** functionality of the **HriPhysioLib** library. The Hilbert Transform is a crucial mathematical tool used for analyzing physiological signals like ECG (Electrocardiogram). This test verifies the correct functionality of the library by applying the Hilbert Transform to ECG data and plotting the results.

## Requirements

Before proceeding, ensure you have completed the following:

1. **Install the necessary Python libraries** listed in the `requirements.txt`.
2. **Generate ECG data** using `generate_data.py` from the Python scripts.
3. **Build the HriPhysioLib Library** using the provided Makefile.
4. **Run the CLI test** to apply the Hilbert Transform to the generated ECG data.

### Requirements File

The `requirements.txt` file lists all the necessary Python packages for this test. You can find it at the following location:

```
HriPhysioLib/cli/requirements.txt
```

Use the following command to install the required packages:

```bash
pip install -r HriPhysioLib/cli/scripts/requirements.txt
```

## Step-by-Step Instructions

### 1. Install the Required Python Libraries

Install the required Python libraries by running the following command in your terminal:
```bash
pip install -r HriPhysioLib/cli/scripts/requirements.txt
```

### 2. Generate ECG Data

The `generate_data.py` script is used to generate a sample ECG signal and save it as a CSV file for further processing. The file is located in the **scripts** folder inside the CLI directory: 

```bash
HriPhysioLib/cli/scripts/generate_data.py
```

This script generates a simulated ECG signal using **NeuroKit2**, saves the data as `ecg_data.csv`, and also generates a plot of the ECG signal saved as `ecg_data.png`.

#### `generate_data.py` Code Explanation

Here is a breakdown of what `generate_data.py` does:

```python
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
```

- **ECG Signal Generation**: It uses **NeuroKit2** to simulate ECG data for 10 seconds with a heart rate of 70 bpm.
- **CSV Export**: The ECG data is saved as `ecg_data.csv` in the current directory.
- **Plot Export**: It also plots the ECG signal and saves it as `ecg_data.png`.

To generate the ECG data, run:

```bash
cd HriPhysioLib/cli/scripts
python generate_data.py
```

### 3. Build the HriPhysioLib Library

After generating the data, you need to build the **HriPhysioLib** library. The library can be built using the Makefile located in the root directory. This will compile the library and prepare it for the CLI test.

In the root folder, run:

```bash
make run-cli
```

This command does the following:
- Builds the **HriPhysioLib** library.
- Runs the CLI test that applies the Hilbert Transform on the generated ECG data.

### 4. Plot Hilbert-Transformed ECG Data

After running the test, the Hilbert Transform will be applied to the ECG data and saved in `ecg_data_with_hilbert.csv`. You can then plot and compare the raw ECG data and its Hilbert-transformed phase using the `plot_data.py` script.

#### `plot_data.py` Code Explanation

The `plot_data.py` script is located in the **scripts** folder inside the CLI directory: 

```bash
HriPhysioLib/cli/scripts/plot_data.py
```

This script reads both the raw ECG data and the Hilbert-transformed data from CSV files, computes the phases of the signals, and plots them.

```python
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

    # Plot the raw ECG phase in blue
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
```

### Explanation:
- **Loading Data**: The raw ECG data (`ecg_data.csv`) and Hilbert-transformed data (`ecg_data_with_hilbert.csv`) are loaded into Pandas DataFrames.
- **Phase Computation**: The phase of both the raw ECG data and the Hilbert-transformed data is computed using the **Hilbert Transform**.
- **Plotting**: The script plots the phases of the raw and Hilbert-transformed ECG signals on the same graph for comparison.

To plot the data, run:

```bash
python plot_data.py
```

### 5. Hilbert Transform Overview

The **Hilbert Transform** is a mathematical technique used in signal processing to obtain the **analytic signal** from a real-valued signal. This analytic signal helps extract important information such as:

- **Instantaneous Phase**: Provides insight into the timing characteristics of a signal.
- **Instantaneous Amplitude (Envelope)**: Gives information about the signal's energy, often used to assess physiological data.

This test applies the Hilbert Transform to ECG data to extract the **instantaneous phase** and compare it with the original signal's phase, thus verifying the transform's correctness.

## Summary of Steps

1. **Generate Data** using `generate_data.py`.
2. **Build the Library** using `make run-cli`.
3. **Plot Data** using `plot_data.py` to visualize both the raw and Hilbert-transformed phases.

By following these steps, you can successfully test the Hilbert Transform functionality of the **HriPhysioLib** library using the CLI tool.