#include "csv_streamer.h"

CSVStreamer::CSVStreamer() : StreamerInterface() {}

CSVStreamer::~CSVStreamer()
{
    if (this->mode == ModeTag::RECEIVER)
    {
        input.close();
    }
    else if (this->mode == ModeTag::SENDER)
    {
        output.close();
    }
}

bool CSVStreamer::open_input_stream()
{
    if (this->mode != ModeTag::NOT_SET)
    {
        return false;
    }

    this->set_mode(ModeTag::RECEIVER);

    try
    {
        input.open(this->name);
        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

bool CSVStreamer::open_output_stream()
{
    if (this->mode != ModeTag::NOT_SET)
    {
        return false;
    }

    this->set_mode(ModeTag::SENDER);

    try
    {
        output.open(this->name);
        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

void CSVStreamer::publish(const std::vector<VarTag> &buffer, const std::vector<double> *timestamps)
{
    switch (this->var)
    {
    case VarTag::CHAR:
        this->push_stream<char>(reinterpret_cast<const std::vector<char> &>(buffer), timestamps);
        break;
    case VarTag::INT16:
        this->push_stream<int16_t>(reinterpret_cast<const std::vector<int16_t> &>(buffer), timestamps);
        break;
    case VarTag::INT32:
        this->push_stream<int32_t>(reinterpret_cast<const std::vector<int32_t> &>(buffer), timestamps);
        break;
    case VarTag::INT64:
        this->push_stream<int64_t>(reinterpret_cast<const std::vector<int64_t> &>(buffer), timestamps);
        break;
    case VarTag::FLOAT:
        this->push_stream<float>(reinterpret_cast<const std::vector<float> &>(buffer), timestamps);
        break;
    case VarTag::DOUBLE:
        this->push_stream<double>(reinterpret_cast<const std::vector<double> &>(buffer), timestamps);
        break;
    default:
        break;
    }
}

void CSVStreamer::publish(const std::string &buffer, const double *timestamps)
{
    std::time_t time = std::time(nullptr);
    output << std::put_time(std::localtime(&time), "%Y/%m/%d_%H:%M:%S") << ",";

    if (timestamps == nullptr)
    {
        output << 0.0;
    }
    else
    {
        output << std::setprecision(10) << (*timestamps);
    }

    output << "," << "\"" << buffer << "\"";
    output << std::endl;
}

template <typename T>
void CSVStreamer::push_stream(const std::vector<T> &buffer, const std::vector<double> *timestamps)
{
    std::time_t time = std::time(nullptr);

    std::size_t idx_buffer = 0;
    std::size_t idx_time = 0;

    while (idx_buffer < buffer.size())
    {
        output << std::put_time(std::localtime(&time), "%Y/%m/%d_%H:%M:%S") << ",";

        if (timestamps == nullptr || timestamps->empty())
        {
            output << 0.0;
        }
        else
        {
            output << std::setprecision(10) << timestamps->at(idx_time);
            ++idx_time;
        }

        for (std::size_t ch = 0; ch < this->num_channels; ++ch)
        {
            output << "," << buffer[idx_buffer + ch];
        }
        idx_buffer += this->num_channels;

        output << std::endl;
    }
}