#include "lsl_streamer.h"

#include <unordered_map>

LSLStreamer::LSLStreamer() = default;

LSLStreamer::~LSLStreamer() {
    if (this->mode == RECEIVER) {
        inlet->close_stream();
        inlet.reset();
    } else if (this->mode == SENDER) {
        outlet.reset();
    }
}

lsl::channel_format_t LSLStreamer::get_lsl_format_type() const {
    static const std::unordered_map<VarTag, lsl::channel_format_t> var_tag_to_channel_format = {
        {CHAR, lsl::channel_format_t::cf_int8},
        {INT16, lsl::channel_format_t::cf_int16},
        {INT32, lsl::channel_format_t::cf_int32},
        {INT64, lsl::channel_format_t::cf_int64},
        {FLOAT, lsl::channel_format_t::cf_float32},
        {DOUBLE, lsl::channel_format_t::cf_double64},
        {STRING, lsl::channel_format_t::cf_string}
    };

    auto candidate = var_tag_to_channel_format.find(this->var);
    return candidate != var_tag_to_channel_format.end()
               ? candidate->second
               : lsl::channel_format_t::cf_undefined;
}

bool LSLStreamer::open_input_stream() {
    if (this->mode != NOT_SET) {
        return false;
    }

    this->set_mode(RECEIVER);
    try {
        const std::vector<lsl::stream_info> resolved_streams = lsl::resolve_stream("name", this->name);
        const lsl::stream_info &first_resolved_stream = resolved_streams[0];

        const auto stream_inlet = new lsl::stream_inlet(first_resolved_stream);
        inlet.reset(stream_inlet);

        return true;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

bool LSLStreamer::open_output_stream() {
    if (this->mode != NOT_SET) {
        return false;
    }

    this->set_mode(SENDER);
    try {
        lsl::stream_info info(
            this->name,
            "",
            static_cast<int32_t>(this->num_channels),
            static_cast<double>(this->sampling_rate),
            this->get_lsl_format_type(),
            this->name
        );

        auto stream_outlet = new lsl::stream_outlet(
            info,
            static_cast<int32_t>(this->frame_length),
            static_cast<int32_t>(this->frame_length * 2)
        );
        outlet.reset(stream_outlet);

        return true;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

void LSLStreamer::publish(const std::vector<VarTag> &buffer) {
    switch (this->var) {
        case CHAR:
            this->push_stream<char>(reinterpret_cast<const std::vector<char> &>(buffer));
            break;
        case INT16:
            this->push_stream<int16_t>(reinterpret_cast<const std::vector<int16_t> &>(buffer));
            break;
        case INT32:
            this->push_stream<int32_t>(reinterpret_cast<const std::vector<int32_t> &>(buffer));
            break;
        case INT64:
            this->push_stream<int64_t>(reinterpret_cast<const std::vector<int64_t> &>(buffer));
            break;
        case FLOAT:
            this->push_stream<float>(reinterpret_cast<const std::vector<float> &>(buffer));
            break;
        case DOUBLE:
            std::cerr << "<double>" << std::endl;
            this->push_stream<double>(reinterpret_cast<const std::vector<double> &>(buffer));
            break;
        default:
            std::cerr << "Unsupported VarTag" << std::endl;
            break;
    }
}

void LSLStreamer::receive(std::vector<VarTag> &buffer, std::vector<double> *timestamps) {
    switch (this->var) {
        case CHAR:
            this->pull_stream<char>(reinterpret_cast<std::vector<char> &>(buffer), timestamps);
            break;
        case INT16:
            this->pull_stream<int16_t>(reinterpret_cast<std::vector<int16_t> &>(buffer), timestamps);
            break;
        case INT32:
            this->pull_stream<int32_t>(reinterpret_cast<std::vector<int32_t> &>(buffer), timestamps);
            break;
        case INT64:
            this->pull_stream<int64_t>(reinterpret_cast<std::vector<int64_t> &>(buffer), timestamps);
            break;
        case FLOAT:
            this->pull_stream<float>(reinterpret_cast<std::vector<float> &>(buffer), timestamps);
            break;
        case DOUBLE:
            this->pull_stream<double>(reinterpret_cast<std::vector<double> &>(buffer), timestamps);
            break;
        default:
            break;
    }
}

void LSLStreamer::publish(const std::string &buffer) const {
    outlet->push_sample(&buffer);
}

void LSLStreamer::receive(std::string &buffer, double *timestamps) {
    //    auto timestamp = inlet->pull_sample(&buffer, 1, 0.2);
    //    if (timestamp != nullptr) {
    //        *timestamps = timestamp;
    //    }
}

template<typename T>
void LSLStreamer::push_stream(const std::vector<T> &buffer) {
    outlet->push_chunk_multiplexed(buffer);
}

template<typename T>
void LSLStreamer::pull_stream(std::vector<T> &buffer, std::vector<double> *timestamps) {
    inlet->pull_chunk_multiplexed(buffer, timestamps, 5.0);
}
