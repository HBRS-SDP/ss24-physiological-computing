#ifndef HRI_PHYSIO_ROBOT_MANAGER_H
#define HRI_PHYSIO_ROBOT_MANAGER_H

#include <iostream>
#include <chrono>

#include <yaml-cpp/yaml.h>

#include "thread_manager.h"
#include "../stream/csv_streamer.h"
#include "../social/robot_interface.h"
#include "../utilities/arg_parser.h"
#include "../utilities/helpers.h"

class RobotManager : public ThreadManager {
private:
    bool log_data;
    std::string log_name;

    CSVStreamer robot_logger;
    RobotInterface *robot;

    std::chrono::system_clock::time_point start_time;

public:
    explicit RobotManager(RobotInterface *robot);

    ~RobotManager();

    void configure(int argc, char **argv);

    void interactive();

private:
    bool thread_init();

    void process(const std::string &input);

    bool set_functions(const std::vector<std::string> &input);

    bool get_functions(const std::vector<std::string> &input);

    void self_loop();

    void input_loop();
};

#endif //HRI_PHYSIO_ROBOT_MANAGER_H