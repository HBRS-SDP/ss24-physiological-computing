# HRI Physio

**Authors:** Shrikar Nakhye, Vedika Chauhan, Trushar Ghanekar
**Date:** Updated on 12 June 2024

## Table of Contents

- [Introduction](#introduction)
- [Library Components](#library-components)
    - [Core Modules](#core-modules)
        - [Signal Acquisition](#signal-acquisition)
        - [Signal Processing](#signal-processing)
        - [Feature Extraction and Analysis](#feature-extraction-and-analysis)
    - [Utilities](#utilities)
        - [File I/O](#file-io)
        - [Miscellaneous](#miscellaneous)
    - [Integration Modules](#integration-modules)
        - [Robot Interaction](#robot-interaction)
        - [PocketFFT Integration](#pocketfft-integration)
- [Getting Started](#getting-started)
    - [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Introduction

HriPhysioLib is a cutting-edge library specifically designed to advance research in human-robot interaction (HRI) by
focusing on the processing and analysis of physiological signals. This library integrates multiple data acquisition
methods, sophisticated signal processing algorithms, and robust analysis tools, making it a comprehensive solution for
researchers and developers. By facilitating the seamless collection and manipulation of physiological data, HriPhysioLib
aims to bridge the gap between human physiological responses and robotic systems, thereby enhancing the capabilities and
responsiveness of robots in interactive scenarios.

The library supports various physiological data sources, including Lab Streaming Layer (LSL), Robot Operating System (
ROS), ensuring broad compatibility and flexibility in research setups. It includes a range of signal processing
techniques such as bi-quadratic filtering, Butterworth filters (band-pass, band-notch, high-pass, and low-pass), and
Hilbert Transform, which are essential for cleaning and transforming raw physiological data. Additionally, feature
extraction methods like spectrogram generation and comprehensive data visualization tools enable detailed analysis and
interpretation of physiological signals.

HriPhysioLib also addresses the practical aspects of integrating physiological data with robotic systems. With modules
for file I/O, threading, and a factory pattern for creating streamers, it provides a solid infrastructure for building
scalable and efficient research applications. The library's robot interaction modules further allow for seamless
communication between physiological sensors and robotic platforms, facilitating real-time interaction and data-driven
decision-making.

Designed with ease of use in mind, HriPhysioLib offers documentation, example use cases, and a structured API reference,
making it accessible even to those who are new to the field. Whether you are developing new HRI applications, conducting
experimental research, or exploring novel ways to enhance robot responsiveness through physiological data, HriPhysioLib
is an invaluable resource.

## Library Components

### Core Modules

#### Signal Acquisition

- `lslStreamer.cpp`: Manages streaming of physiological data using Lab Streaming Layer.
- `rosStreamer.cpp`: Integrates ROS for streaming physiological data.
- `yarpStreamer.cpp`: Utilizes YARP for physiological data streaming.

#### Signal Processing

- `biquadratic.cpp`: Implements bi quadratic filtering.
- `butterworthBandNotch.cpp`: Provides Butterworth band-notch filtering.
- `butterworthBandPass.cpp`: Implements Butterworth band-pass filtering.
- `butterworthHighPass.cpp`: High-pass filtering with Butterworth filter.
- `butterworthLowPass.cpp`: Low-pass filtering using Butterworth filter.
- `hilbertTransform.cpp`: Applies Hilbert Transform for signal processing.

#### Feature Extraction and Analysis

- `spectrogram.cpp`: Generates spectrograms for signal analysis.
- `graph.cpp`: Visualizes physiological signals.

### Utilities

#### File I/O

- `csvStreamer.cpp`: Facilitates reading and writing CSV files.

#### Miscellaneous

- `helpers.cpp`: Contains various helper functions.
- `streamerFactory.cpp`: Factory pattern implementation for creating streamers.
- `streamerInterface.cpp`: Interface for different streamers.
- `threadManager.cpp`: Manages threading for concurrent operations.

### Integration Modules

#### Robot Interaction

- `robotInterface.cpp`: Interfaces with robotic systems.
- `robotManager.cpp`: Manages robot-related tasks.
- `physioManager.cpp`: Manages physiological data processing.

#### PocketFFT Integration

The library integrates the PocketFFT library, which is a highly optimized Fast Fourier Transform (FFT) implementation.
PocketFFT offers several advantages:

- Strictly C++17 compliant.
- Supports multidimensional arrays and various data types (float, double, long double).
- Offers both complex and half-complex FFTs.
- Utilizes CPU vector instructions for higher-dimensional transforms.

## Getting Started

### Installation

Clone the repository and build the library:

```bash
git clone https://github.com/kothiga/hri-physio.git
cd hri-physio/HriPhysioLib
mkdir build
cd build
cmake ..
make
```

## Contributing

Contributions are welcome. Fork the repository, create a feature branch, commit your changes, and open a pull request.

## License

HriPhysioLib is licensed under the MIT License.

For more information, visit the [GitHub repository](https://github.com/kothiga/hri-physio).
