# CLI Testing Instructions

This README provides detailed instructions for testing the Hilbert Transform functionality of the **HriPhysioLib** library. The Hilbert Transform is a mathematical tool used to derive the analytic representation of a signal, which is crucial in analyzing the phase and envelope of physiological signals such as ECG (Electrocardiogram). This test will verify that the library has been built correctly by applying the Hilbert Transform to ECG data.

## Requirements

Before proceeding with the CLI test, you'll need to:

1. **Install NeuroKit2**: This Python library will be used to generate ECG data.
2. **Save ECG data using NeuroKit2**: If you don’t have ECG data available, you can create one.[NeuroKit library](https://github.com/neuropsychology/NeuroKit)
3. **Build the HriPhysioLib Library**: Follow the instructions to build the library using provided bash scripts.
4. **Run the CLI test**: After building the library, run the bash script in the CLI folder to verify the Hilbert Transform functionality.

## Step-by-Step Instructions

### 1. Install NeuroKit2[NeuroKit library](https://github.com/neuropsychology/NeuroKit)

**NeuroKit2** is a Python package designed to provide easy access to physiological data such as ECG signals. You need to install it before proceeding.

To install **NeuroKit2**, use the following command in your terminal:

```bash
pip install neurokit2
```

Make sure that **Pandas** is also installed, as it will be used to handle the ECG data in CSV format. If you don’t have Pandas installed, use:

```bash
pip install pandas
```

### 2. Save ECG Data from NeuroKit2

In order to test the Hilbert Transform with the CLI tool, you need a CSV file containing ECG data. You can either use an existing ECG data file or generate one using **NeuroKit2**.

#### Generating and Saving ECG Data

There is a Python file named `data_extract.py` located in the `./HriPhysioLib/cli/data/` directory. This script will generate and save ECG data as a CSV file using **NeuroKit2**.

Here is how the `data_extract.py` file looks:

```python
import neurokit2 as nk
import pandas as pd

# Load ECG data (returns a NumPy array)
ecg = nk.data('ecg_1000hz.csv')

# Convert the NumPy array to a Pandas DataFrame
df_ecg = pd.DataFrame(ecg)

# Save the DataFrame as a CSV file
df_ecg.to_csv('ecg_data.csv', index=False)
```

To run this script and generate the `ecg_data.csv` file, navigate to the `./HriPhysioLib/cli/data/` directory and execute the Python script:

```bash
python data_extract.py
```

This will save the ECG data in `ecg_data.csv` in the same folder.

### 3. Build the Main Library

Before running the CLI test, you need to ensure that the main **HriPhysioLib** library is built.

Navigate to the **build.sh** script located at `./HriPhysioLib/lib/build.sh`. Run the following commands to build the library:

```bash
cd ./HriPhysioLib/lib
bash build.sh
```

This script will compile the library and prepare it for use.

### 4. Build the CLI Example

After building the main library, you need to build the CLI example, which is designed to test the Hilbert Transform on the generated ECG data.

The CLI example has its own `build.sh` script located at `./HriPhysioLib/cli/build.sh`. To build the CLI example, navigate to the `cli` folder and run the following commands:

```bash
cd ./HriPhysioLib/cli
bash build.sh
```

### 5. Run the CLI Test

Once the CLI example is built, you can run the Hilbert Transform test on the ECG data. Ensure that the `ecg_data.csv` file (generated from the NeuroKit2 library) is in the correct directory (`./HriPhysioLib/cli/data/`).


This will apply the Hilbert Transform to the ECG data and verify that the library processes the signals correctly.

## Understanding the Hilbert Transform

The **Hilbert Transform** is a fundamental mathematical tool used in signal processing to extract the **analytic signal** from a real-valued signal. It is used to compute the **instantaneous phase** and **instantaneous amplitude** (also known as the envelope) of a signal, which is crucial in analyzing physiological signals like ECG.

- **Instantaneous Phase**: Provides information about the signal's timing characteristics.
- **Instantaneous Amplitude (Envelope)**: Represents the signal's energy over time, which is useful for understanding the overall behavior of physiological data.

In this test, the Hilbert Transform will be applied to ECG data, which is a widely used signal in both research and clinical settings to analyze the heart's electrical activity.