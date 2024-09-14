---

# 🌟 **HRI Physio Library** 🌟

**Last Updated:** *Sept 14, 2024*

---

## 📜 **Table of Contents** 

- [📘 Introduction](#introduction)
- [🧩 Library Components](#library-components)
  - [📦 External Libraries](#external-libraries)
  - [📂 Source Modules](#source-modules)
    - [🛠️ Core](#core)
    - [🔧 Manager](#manager)
    - [🤖 Social](#social)
    - [🔬 Processing](#processing)
    - [💾 Stream](#stream)
    - [⚙️ Utilities](#utilities)
    - [🧪 Tests](#tests)
- [🖥️ CLI Testing](#cli-testing)
- [🚀 Getting Started](#getting-started)
  - [💻 Installation](#installation)
    - [🔍 Method 1: Recursive Git Clone](#method-1-recursive-git-clone)
    - [🔧 Method 2: Manual Git Clone and Adding Submodules](#method-2-manual-git-clone-and-adding-submodules)
- [👥 Contributors](#contributors)
- [📄 License](#license)

---

## 📘 **Introduction**

Welcome to **HriPhysioLib**! 🎉 This library is designed for researchers in **Human-Robot Interaction (HRI)**, specifically tailored for **physiological signal processing**. Whether you're analyzing **ECG data** 🩺 or synchronizing robotic systems with physiological inputs 🤖, this library provides the tools to make that happen seamlessly!

With support for **Lab Streaming Layer (LSL)** and **Robot Operating System (ROS)**, and advanced signal processing techniques like **bi-quadratic filtering** and the **Hilbert Transform**, it's ideal for cutting-edge research in physiological data analysis.

Let’s dive into the details!

---

## 🧩 **Library Components**

### 📦 **External Libraries**

**HriPhysioLib** integrates external submodules to extend its functionality. These are:

- **`liblsl`** 🛠️: For streaming physiological data using **Lab Streaming Layer (LSL)**.
- **`yaml-cpp`** 🗂️: For parsing and emitting **YAML** files, useful in handling configurations.

### 📂 **Source Modules**

The **source** folder is divided into several modules, each with a specific role:

#### 🛠️ **Core**
The **Core** module provides essential data structures. The key component here is the **Ring Buffer**, a circular structure used for managing physiological data streams in **FIFO** (First In, First Out) order.

- **`ringbuffer.h`**: The heart of this module, providing the ring buffer functionality.

#### 🔧 **Manager**
The **Manager** module handles the coordination between robotic systems 🤖 and physiological data. It includes multithreading for efficient, real-time operations.

- **`robot_manager.h/cpp`**: Enables data exchange between robots and physiological data.
- **`thread_manager.h/cpp`**: Manages multithreaded processes for data streaming and processing.

#### 🤖 **Social**
The **Social** module is all about integrating robots with the outside world using physiological signals to drive behaviors 🚶‍♂️→🤖.

- **`robot_interface.h/cpp`**: The standard interface to communicate with robots.

#### 🔬 **Processing**
This is where the magic of transforming raw data into something meaningful happens! 🧙‍♂️ The **Processing** module includes:

- **`hilbert_transform.h/cpp`**: For applying the **Hilbert Transform** to physiological signals.
- **`pocketfft.h`**: Handles **Fourier Transforms** for time-frequency analysis.
- **`spectrogram.h/cpp`**: Generates **spectrograms** for visualizing signal frequencies over time.

#### 💾 **Stream**
The **Stream** module manages data flow from external sources to the processing pipeline 📊.

- **`csv_streamer.h/cpp`**: Handles data in **CSV format**.
- **`lsl_streamer.h/cpp`**: Facilitates **LSL-based** physiological data streaming.

#### ⚙️ **Utilities**
The **Utilities** module offers various helper tools to smooth your workflow 🛠️.

- **`arg_parser.h/cpp`**: Parses command-line arguments for easy library configuration.
- **`helper.h/cpp`**: Contains useful functions like data conversion and logging.

#### 🧪 **Tests**
The **Tests** module is vital for ensuring all the core functionalities work as intended. ✔️

Certainly! Here’s the updated **Tests** section with the details you provided about the test cases and how to run them.

---

## 🧪 **Tests**

The **Tests** module includes comprehensive test suites to verify the core functionalities of the library. These tests ensure that critical components, such as the **RingBuffer** and the **HilbertTransform**, behave as expected in various scenarios.

### **Test Suites and Cases**

#### 📦 **Ring Buffer Test Suite**

The **RingBuffer** test suite ensures that the circular buffer, essential for streaming continuous physiological data, operates correctly.

- **Test Cases:**
  
  1. **InitializeBuffer**  
     - Ensures the ring buffer is initialized with the specified size, starts empty, and reports a size of zero.
  
  2. **PushAndPop**  
     - Verifies that data is added and retrieved in the correct order (FIFO – First In, First Out).
  
  3. **OverflowHandling**  
     - Tests how the buffer behaves when it reaches its capacity. It verifies that when full, the buffer overwrites the oldest data.

#### 🧠 **HilbertTransform Test Suite**

This test suite ensures the **HilbertTransform** class, responsible for signal processing, works as expected across different use cases.

- **Test Cases:**
  
  1. **ConstructorTest**  
     - Ensures the constructor of the **HilbertTransform** class initializes without errors for valid input sizes.
  
  2. **ResizeTest**  
     - Verifies the **resize()** function changes the size of the internal buffer without issues.
  
  3. **ProcessZeroInput**  
     - Confirms that when a vector of zeros is processed, the output is also a vector of zeros, validating the handling of edge cases.
  
  4. **ProcessDifferentSizes**  
     - Ensures the **process()** method correctly handles input vectors of varying sizes and returns output of matching size.

- **Helper Function:**
  - **ExpectNearVector**  
    - Compares two vectors with a specified tolerance to ensure the accuracy of results during the tests.

---

### 🔧 **Running the Tests**

To build and run the test suite, follow these steps:

```bash
# Create a build directory and navigate into it
mkdir build && cd build

# Generate the build system files
cmake ..

# Build the tests
make

# Run the test suite
./run-tests.sh
```

This will execute all the test cases and display the results in the terminal.

---

## 🖥️ **CLI Testing**

The **CLI testing** framework 🖥️ allows you to test the library’s functionality directly from the command line, focusing on the **Hilbert Transform** application on **ECG data** generated using the [NeuroKit library](https://github.com/neuropsychology/NeuroKit). 

### Key Features:
Key features of the `cli` testing setup:

- **Data Input and Output**: The CLI reads ECG data from a CSV file, applies the Hilbert Transform to the data, and writes the results to a new CSV file. This allows for a straightforward method of verifying the functionality of the processing algorithms.
  
- **Hilbert Transform**: The primary processing function tested is the Hilbert Transform, which is implemented in the library to compute the analytic signal of the ECG data, providing both amplitude and phase information.

- **CSV Streamers**: The testing program utilizes `CSVStreamer` for both input and output operations, facilitating the reading and writing of data in CSV format. The CSV files are expected to contain single-channel ECG data, and the output file includes both the original data and the Hilbert-transformed data.

The `cli` folder contains a simple test program (`main.cpp`) that executes the entire process. This setup allows researchers and developers to verify the processing functions of the library before integrating it into larger systems. However, it does not utilize the full functionality of the library, such as streaming protocols or robotic control.

For more detailed instructions on using the example, visit the [Instructions](./HriPhysioLib/cli/README.md).


## 🚀 **Getting Started**

### 💻 **Installation**

There are two methods to install **HriPhysioLib**:

#### 🔍 **Method 1: Recursive Git Clone**

This method automatically pulls the external submodules for you.

```bash
git clone --recursive https://github.com/HBRS-SDP/ss24-physiological-computing.git
cd hri-physio/HriPhysioLib
```

Then, to build and test the library, simply use:

```bash
make build-library
make run-library-tests
make run-cli
```

#### 🔧 **Method 2: Manual Git Clone and Adding Submodules**

Alternatively, if you prefer manual control over submodules, follow these steps:

```bash
git clone https://github.com/HBRS-SDP/ss24-physiological-computing.git
cd hri-physio/HriPhysioLib
```

Next, initialize and update the submodules:

```bash
git submodule init
git submodule update
```

Then, use the same **Makefile** commands as in Method 1 to build and run tests:

```bash
make build-library
make run-library-tests
make run-cli
```

---

### 🖥️ **Tested and Verified On**

- **64-bit Ubuntu 22.04.5 LTS** 🐧
- **macOS Sonoma 14.6.1** 🍎

---

## 👥 **Contributors**

Big thanks to our amazing contributors who made **HriPhysioLib** possible! 🙌

- **Austin Kothig** 📧: austin.kothig@uwaterloo.ca
- **Jessy Song**
- **Trushar Ghanekar** 📧: trushar.ghanekar@smail.inf.h-brs.de
- **Vedika Chauhan** 📧: vedika.chauhan@smail.inf.h-brs.de
- **Shrikar Nakhye** 📧: shrikar.nakhye@smail.inf.h-brs.de

---

## 📄 **License**

**HriPhysioLib** is licensed under the **MIT License** 📜. For more details, please visit the [GitHub Repository](https://github.com/kothiga/hri-physio).

---

Enjoy exploring the world of **Human-Robot Interaction** with physiological data! 🧠🤖