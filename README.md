# HRI Physio

**Date:** Updated on 12 June 2024

## Table of Contents

- [Introduction](#introduction)
- [Library Components](#library-components)
    - [External Libraries](#external-libraries)
    - [Source Modules](#source-modules)
        - [Core](#core)
        - [Manager](#manager)
        - [Social](#social)
        - [Processing](#processing)
        - [Stream](#stream)
        - [Utilities](#utilities)
        - [Tests](#tests)
- [Test](#test)
- [Getting Started](#getting-started)
    - [Installation](#installation)
- [Contributors](#contributors)
- [License](#license)

## Introduction

HriPhysioLib is a specialized library developed to support research in human-robot interaction (HRI) by focusing on the processing and analysis of physiological signals. It provides tools for data acquisition, signal processing, and analysis, allowing researchers to integrate physiological data with robotic systems effectively. The library is compatible with various data sources like Lab Streaming Layer (LSL) and Robot Operating System (ROS), and includes several signal processing techniques, such as bi-quadratic filtering and Hilbert Transform. HriPhysioLib is designed to be user-friendly, with clear documentation.

## Library Components

### External Libraries

HriPhysioLib integrates two external libraries as Git submodules:

- `liblsl`: A library for streaming physiological data using Lab Streaming Layer (LSL).
- `yaml-cpp`: A library for parsing and emitting YAML, useful for configuration files and data serialization.

### Source Modules

The `source` folder is organized into several modules, each containing specific functionalities necessary for processing and managing physiological signals.

#### Core

The `Core` module provides foundational structures necessary for the library's operation, specifically focusing on data handling.

- `ringbuffer.h`: Implements a ring buffer, a circular data structure that efficiently stores and retrieves data in a FIFO (First In, First Out) manner. This is particularly useful for managing continuous streams of physiological data, ensuring that old data is automatically overwritten when new data comes in.

#### Manager

The `Manager` module is responsible for managing the interaction between the physiological data and robotic systems, as well as handling multithreading.

- `robot_manager.h`, `robot_manager.cpp`: Define and implement the `RobotManager` class, which handles all interactions with robotic systems. It manages data exchange between the physiological data streams and the robot, ensuring that the robot can respond to physiological signals in real-time.

- `thread_manager.h`, `thread_manager.cpp`: Define and implement the `ThreadManager` class, which manages multithreading within the library. Multithreading is crucial for the efficient processing of data and the management of tasks that need to run concurrently, such as data streaming, signal processing, and robot interaction.

#### Social

The `Social` module focuses on the interaction between the robot and the external environment, specifically through interfaces that allow physiological data to influence robot behavior.

- `robot_interface.h`, `robot_interface.cpp`: Define and implement the `RobotInterface` class, which provides a standardized way for the library to interact with various robotic platforms. This interface ensures that physiological data can be used to control or influence robot actions, facilitating real-time, data-driven robotic behavior.

#### Processing

The `Processing` module includes all the tools and algorithms necessary for transforming raw physiological data into meaningful signals that can be analyzed or used to control robotic systems.

- `hilbert_transform.h`, `hilbert_transform.cpp`: Define and implement the Hilbert Transform, a mathematical tool used to obtain the analytic representation of a signal. It is crucial for analyzing the phase and envelope of physiological signals, which can provide deeper insights into the underlying physiological processes.

- `math.h`: Contains various mathematical utilities and functions that are used across the processing module. These utilities support the core signal processing tasks, such as filtering, transformations, and spectral analysis.

- `pocketfft.h`: Integrates the PocketFFT library, which provides an efficient implementation of the Fast Fourier Transform (FFT). The FFT is essential for converting time-domain signals into their frequency-domain representations, enabling the analysis of the signal's frequency content.

- `spectrogram.h`, `spectrogram.cpp`: Define and implement the generation of spectrograms, which are visual representations of a signal's frequency spectrum over time. Spectrograms are useful for analyzing how the frequency content of a physiological signal changes, which can be crucial for tasks like detecting patterns or anomalies.

#### Stream

The `Stream` module handles the streaming of physiological data, both from external sources and to external destinations. This module includes tools for working with different streaming protocols and data formats.

- `csv_streamer.h`, `csv_streamer.cpp`: Define and implement the `CSVStreamer` class, which handles the reading from and writing to CSV files. CSV is a common format for storing physiological data, and this class allows for easy integration with other tools that work with CSV files.

- `lsl_streamer.h`, `lsl_streamer.cpp`: Define and implement the `LSLStreamer` class, which manages the streaming of physiological data using the Lab Streaming Layer (LSL) protocol. LSL is widely used in research for synchronizing data streams from different sources, and this class enables the integration of physiological data into LSL-compatible systems.

- `streamer_factory.h`, `streamer_factory.cpp`: Define and implement the `StreamerFactory` class, which uses the factory design pattern to create instances of different streamers. This pattern allows for flexibility in choosing and switching between different streaming methods (e.g., CSV or LSL) depending on the specific requirements of the research.

- `streamer_interface.h`, `streamer_interface.cpp`: Define and implement a common interface for all streamers, ensuring that they all adhere to a consistent API. This makes it easier to work with different streaming protocols without needing to modify the core library code.

#### Utilities

The `Utilities` module provides various helper functions and tools that support the other modules in the library. These utilities handle common tasks that are necessary across the different modules.

- `arg_parser.h`, `arg_parser.cpp`: Define and implement a command-line argument parser, making it easier to configure and control the library from the command line. This is particularly useful for researchers who need to quickly adjust settings or parameters without modifying the source code.

- `helper.h`, `helper.cpp`: Contain various helper functions that are used across different modules. These functions handle common tasks, such as data conversion, logging, and error handling, which are essential for the smooth operation of the library.

- `enums.h`: Defines various enumerations that are used throughout the library. Enumerations provide a clear and consistent way to represent different states, options, or configurations, making the code easier to read and maintain.

### CLI Testing

The `cli` folder in the main library is designed for testing the library's processing capabilities, specifically focusing on the Hilbert Transform. This command-line interface (CLI) primarily tests the processing of ECG (Electrocardiogram) data, which is generated using the [NeuroKit library](https://github.com/neuropsychology/NeuroKit).

Key features of the `cli` testing setup:

- **Data Input and Output**: The CLI reads ECG data from a CSV file, applies the Hilbert Transform to the data, and writes the results to a new CSV file. This allows for a straightforward method of verifying the functionality of the processing algorithms.
  
- **Hilbert Transform**: The primary processing function tested is the Hilbert Transform, which is implemented in the library to compute the analytic signal of the ECG data, providing both amplitude and phase information.

- **CSV Streamers**: The testing program utilizes `CSVStreamer` for both input and output operations, facilitating the reading and writing of data in CSV format. The CSV files are expected to contain single-channel ECG data, and the output file includes both the original data and the Hilbert-transformed data.

The `cli` folder contains a simple test program (`main.cpp`) that executes the entire process. This setup allows researchers and developers to verify the processing functions of the library before integrating it into larger systems. However, it does not utilize the full functionality of the library, such as streaming protocols or robotic control.

For more detailed instructions on using the example, visit the [Instructions](./HriPhysioLib/cli/README.md).

### Tests
The `Tests` module provides test functions and tools that test certain functions in the library.
- **test ring buffer**: 
This test suite verifies the functionality of the `RingBuffer`.

### Test Cases:

1. **InitializeBuffer**  
   - Ensures the ring buffer initializes correctly with a specified size, starts empty, and reports a size of zero.

2. **PushAndPop**  
   - Verifies that data can be pushed to and popped from the buffer in the correct order (FIFO).

3. **OverflowHandling**  
   - Tests how the buffer handles overflow when it reaches its capacity. Assumes that the buffer overwrites the oldest data when full.


## Test
## HilbertTransform Test Suite

This test suite ensures the correct functionality of the `HilbertTransform` class.

### Test Cases:

1. **ConstructorTest**  
   - Ensures that the `HilbertTransform` constructor initializes without throwing exceptions for valid input sizes.

2. **ResizeTest**  
   - Verifies that the `resize()` function operates correctly, allowing size changes without errors.

3. **ProcessZeroInput**  
   - Confirms that processing a vector of zeros results in an output of zeros, validating handling of zero input.

4. **ProcessDifferentSizes**  
   - Ensures the `process()` method can handle different input sizes and returns an output of matching size.

### Helper Function:
- `ExpectNearVector`: Used to compare two vectors with a specified tolerance, ensuring accurate result comparisons during tests.

### Running the Tests:

```bash
mkdir build && cd build
cmake ..
make
./run-tests.sh

### Installation

You can install HriPhysioLib using one of two methods, depending on whether you want to include the external submodules automatically or manually.

#### Method 1: Recursive Git Clone

This method automatically includes the external libraries as submodules.

```bash
git clone --recursive https://github.com/kothiga/hri-physio.git
cd hri-physio/HriPhysioLib
```

Then, to build the library, simply run the provided build script:

```bash
./lib/build.sh
```

#### Method 2: Manual Git Clone and Adding Submodules

If you clone the repository without the `--recursive` option, you'll need to manually add the external submodules.

1. Clone the repository:

 ```bash
git clone https://github.com/kothiga/hri-physio.git
cd hri-physio/HriPhysioLib
```

2. Initialize and update the submodules:

```bash
git submodule init
git submodule update
```

3. To build the library, use the following command:

```bash
./lib/build.sh
```
#### Method 3: Makefile
- Use `make build-library` to build the library.
- Use `make run-library-tests` to build the library and run its tests.
- Use `make run-cli` to build the library, build the CLI, and run it.

## Tested and Verified on:

* 64 Bit Ubuntu 22.04.5 LTS
* macOS Sonoma 14.6.1

## Contributors

- Austin Kothig <austin.kothig@uwaterloo.ca>
- Jessy Song
- Trushar Ghanekar <trushar.ghanekar@smail.inf.h-brs.de>
- Vedika Chauhan <vedika.chauhan@smail.inf.h-brs.de>
- Shrikar Nakhye <shrikar.nakhye@smail.inf.h-brs.de>

## License

HriPhysioLib is licensed under the MIT License.

For more information, visit the [GitHub repository](https://github.com/kothiga/hri-physio).
