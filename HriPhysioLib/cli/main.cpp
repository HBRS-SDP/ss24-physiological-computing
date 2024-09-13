#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "processing/hilbert_transform.h"
#include "stream/csv_streamer.h"

std::vector<double> read_csv_data(std::ifstream &input_stream) {
    std::vector<double> data;
    std::string line;

    // Skip the header line if it exists
    std::getline(input_stream, line);

    while (std::getline(input_stream, line)) {
        std::stringstream ss(line);
        std::string value;

        // Assuming the data is in the first column
        if (std::getline(ss, value, ',')) {
            try {
                data.push_back(std::stod(value));
            } catch (const std::exception &e) {
                std::cerr << "Error parsing value: " << value << "\n" << e.what() << std::endl;
            }
        }
    }

    return data;
}

int main() {
    std::cout << "HRI Physio CLI" << std::endl;

    const std::string input_csv_path = "../data/ecg_data.csv";
    const std::string output_csv_path = "../data/ecg_data_with_hilbert.csv";

    // Create and configure input CSVStreamer
    CSVStreamer input_csv_streamer;
    input_csv_streamer.set_name(input_csv_path);
    input_csv_streamer.set_data_type("double");
    input_csv_streamer.set_num_channels(1); // Assuming single-channel ECG data

    // Open the input CSV file
    if (!input_csv_streamer.open_input_stream()) {
        std::cerr << "Failed to open input CSV file: " << input_csv_path << std::endl;
        return 1;
    }

    // Read data from CSV
    std::vector<double> csv_data = read_csv_data(input_csv_streamer.input);

    // Process with Hilbert Transform
    HilbertTransform hilbert(csv_data.size());
    std::vector<double> hilbert_result(csv_data.size());
    hilbert.process(csv_data, hilbert_result);

    // Create and configure output CSVStreamer
    CSVStreamer output_csv_streamer;
    output_csv_streamer.set_name(output_csv_path);
    output_csv_streamer.set_data_type("double");
    output_csv_streamer.set_num_channels(2); // Two channels: original data and Hilbert transform

    // Open the output CSV file
    if (!output_csv_streamer.open_output_stream()) {
        std::cerr << "Failed to open output CSV file: " << output_csv_path << std::endl;
        return 1;
    }

    // Write data to the output CSV file
    std::cout << "Writing results to " << output_csv_path << std::endl;
    for (size_t i = 0; i < csv_data.size(); ++i) {
        std::vector<double> data = {csv_data[i], hilbert_result[i]};
        output_csv_streamer.publish(std::vector<VarTag>(data.size(), VarTag::DOUBLE), &data);
    }

    std::cout << "Processing complete. Results written to " << output_csv_path << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "processing/hilbert_transform.h"
#include "stream/csv_streamer.h"

std::vector<double> read_csv_data(std::ifstream &input_stream)
{
    std::vector<double> data;
    std::string line;

    // Skip the header line if it exists
    std::getline(input_stream, line);

    while (std::getline(input_stream, line))
    {
        std::stringstream ss(line);
        std::string value;

        // Assuming the data is in the first column
        if (std::getline(ss, value, ','))
        {
            try
            {
                data.push_back(std::stod(value));
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error parsing value: " << value << "\n"
                          << e.what() << std::endl;
            }
        }
    }

    return data;
}

int main()
{
    std::cout << "HRI Physio CLI" << std::endl;

    // Get the current working directory
    std::string cwd = std::filesystem::current_path().string();

    // Construct the input and output file paths relative to the current working directory
    const std::string input_csv_path = cwd + "/cli/data/ecg_data.csv";
    const std::string output_csv_path = cwd + "/cli/data/ecg_data_with_hilbert.csv";

    // Create and configure input CSVStreamer
    CSVStreamer input_csv_streamer;
    input_csv_streamer.set_name(input_csv_path);
    input_csv_streamer.set_data_type("double");
    input_csv_streamer.set_num_channels(1); // Assuming single-channel ECG data

    // Open the input CSV file
    if (!input_csv_streamer.open_input_stream())
    {
        std::cerr << "Failed to open input CSV file: " << input_csv_path << std::endl;
        return 1;
    }

    // Read data from CSV
    std::vector<double> csv_data = read_csv_data(input_csv_streamer.input);

    // Process with Hilbert Transform
    HilbertTransform hilbert(csv_data.size());
    std::vector<double> hilbert_result(csv_data.size());
    hilbert.process(csv_data, hilbert_result);

    // Create and configure output CSVStreamer
    CSVStreamer output_csv_streamer;
    output_csv_streamer.set_name(output_csv_path);
    output_csv_streamer.set_data_type("double");
    output_csv_streamer.set_num_channels(2); // Two channels: original data and Hilbert transform

    // Open the output CSV file
    if (!output_csv_streamer.open_output_stream())
    {
        std::cerr << "Failed to open output CSV file: " << output_csv_path << std::endl;
        return 1;
    }

    // Write data to the output CSV file
    std::cout << "Writing results to " << output_csv_path << std::endl;
    for (size_t i = 0; i < csv_data.size(); ++i)
    {
        std::vector<double> data = {csv_data[i], hilbert_result[i]};
        output_csv_streamer.publish(std::vector<VarTag>(data.size(), VarTag::DOUBLE), &data);
    }

    std::cout << "Processing complete. Results written to " << output_csv_path << std::endl;

    return 0;
}
