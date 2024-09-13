---
# 🚀 **CLI Testing Instructions for HriPhysioLib** 🚀

Welcome to the **CLI Testing Instructions** for **HriPhysioLib**! This guide will walk you through testing the **Hilbert Transform** functionality using sample ECG (Electrocardiogram) data. The Hilbert Transform is a key mathematical tool used for signal analysis in physiological studies like ECG, where it helps extract important signal properties like the **instantaneous phase** and **amplitude**.

Let's get started! 🏁

---

## 🎯 **Requirements** 

Before you start, ensure the following steps are completed:

- ✅ **Install the required Python libraries** listed in `requirements.txt`.
- ✅ **Generate ECG data** using the Python script `generate_data.py`.
- ✅ **Build HriPhysioLib** using the provided **Makefile**.
- ✅ **Run the CLI test** to verify the Hilbert Transform on ECG data.

---

## 📋 **Step-by-Step Instructions**

### 1️⃣ **Install the Required Libraries** 

To ensure all necessary Python libraries are installed, run:

```bash
pip install -r HriPhysioLib/cli/scripts/requirements.txt
```

> **Note:** The `requirements.txt` file contains all the dependencies needed to run the ECG data generation, Hilbert Transform, and plotting scripts.

### 2️⃣ **Generate ECG Data**

Next, generate the ECG data by running the `generate_data.py` script located in the **scripts** folder. This script will simulate ECG data, store it in a CSV file (`ecg_data.csv`), and generate a plot (`ecg_data.png`).

Here’s how you can run it:

```bash
cd HriPhysioLib/cli/scripts
python generate_data.py
```

📝 **What does `generate_data.py` do?**

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

# Plot the ECG data
plt.plot(ecg_data)
plt.xlabel('Measurement #')
plt.ylabel('Amplitude')
plt.title('ECG Data')
plt.savefig('ecg_data.png')
```

📌 **Key Features**:
- **Simulates** a 10-second ECG signal with **NeuroKit2**.
- Saves the data to a **CSV file** (`ecg_data.csv`).
- Generates an ECG **plot image** (`ecg_data.png`).

---

### 3️⃣ **Build HriPhysioLib**

Once the ECG data is generated, it's time to build the **HriPhysioLib** library. You can do this using the **Makefile** in the root directory. This step compiles the library and prepares it for running the CLI test.

To build the library and run the test, simply run:

```bash
make run-cli
```

This command will:
- ✅ Compile the **HriPhysioLib** library.
- ✅ Apply the **Hilbert Transform** to the generated ECG data.
- ✅ Save the transformed data as `ecg_data_with_hilbert.csv`.

---

### 4️⃣ **Plot ECG Data with Hilbert Transform**

Now that the Hilbert Transform has been applied to the ECG data, you can visualize it using the `plot_data.py` script. This will plot both the **raw ECG phase** and the **Hilbert-transformed phase**.

To run the plot:

```bash
python plot_data.py
```

📝 **What does `plot_data.py` do?**

```python
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.signal import hilbert

def plot_ecg_data_with_hilbert(raw_ecg_file, hilbert_transformed_file):
    # Load raw ECG data and Hilbert-transformed data
    ecg_data = pd.read_csv(raw_ecg_file)
    ecg_data_with_hilbert = pd.read_csv(hilbert_transformed_file)

    # Extract ECG and Hilbert-transformed data
    raw_ecg_data = ecg_data['ECG_Data']
    hilbert_transformed_data = ecg_data_with_hilbert.iloc[:, 1]

    # Ensure same length for comparison
    min_length = min(len(raw_ecg_data), len(hilbert_transformed_data))
    trimmed_raw_ecg_data = raw_ecg_data[:min_length]
    trimmed_hilbert_transformed_data = hilbert_transformed_data[:min_length]

    # Compute Hilbert Transform phase for raw ECG
    analytic_signal_raw = hilbert(trimmed_raw_ecg_data)
    phase_raw = np.angle(analytic_signal_raw)

    # Plot the phases
    plt.figure(figsize=(8, 4))
    plt.plot(phase_raw, label='Raw ECG Phase', color='blue', linewidth=2)
    plt.plot(np.angle(trimmed_hilbert_transformed_data), label='Hilbert Phase', color='red', linewidth=2)
    plt.title('Raw ECG and Hilbert-Transformed Phases')
    plt.xlabel('Sample Index')
    plt.ylabel('Phase (radians)')
    plt.legend()
    plt.tight_layout()
    plt.show()

# Example usage:
plot_ecg_data_with_hilbert('./ecg_data.csv', './ecg_data_with_hilbert.csv')
```

📌 **Key Features**:
- **Loads** the raw ECG data (`ecg_data.csv`) and Hilbert-transformed data (`ecg_data_with_hilbert.csv`).
- **Plots** both the **raw phase** and **Hilbert-transformed phase** for comparison.

---

## 🧠 **Understanding the Hilbert Transform**

The **Hilbert Transform** is used to derive the **analytic signal** from real-valued signals (like ECG), which allows us to compute the **instantaneous phase** and **amplitude**.

- **Instantaneous Phase**: This reveals the signal’s phase at any given point in time.
- **Instantaneous Amplitude (Envelope)**: This tells us the energy of the signal over time.

In this test, we apply the Hilbert Transform to ECG data, which is a commonly used signal in both research and clinical settings for analyzing the heart's electrical activity.

---

## ✅ **Summary of Steps**:

1. **Generate ECG Data** using `generate_data.py` 🎛️.
2. **Build the HriPhysioLib Library** using `make run-cli` 🔨.
3. **Plot the Data** using `plot_data.py` 📊.

By following these steps, you'll be able to successfully verify the Hilbert Transform functionality in **HriPhysioLib**.

---

💡 **Pro Tip**: Always check that all required files, such as `ecg_data.csv` and `ecg_data_with_hilbert.csv`, are in the correct folder (`/cli/data`) before running the plotting script.

Good luck with your testing, and have fun exploring the power of the **Hilbert Transform**! 🚀🔬