# Scripts

This folder contains basic Python scripts to generate test ECG data and plot the data generated by the sample CLI application.

## Setup

1. Create a new virtual environment:
   ```bash
   python3 -m venv venv
   ```

2. Activate the virtual environment:
   ```bash
   source venv/bin/activate
   ```

3. Install the required dependencies:
   ```bash
   pip install -r requirements.txt
   ```

## Usage

- To generate test ECG data, run:
  ```bash
  python3 generate_data.py
  ```

- To plot the ECG data (run the CLI application first), run:
  ```bash
  python3 plot_data.py
  ```