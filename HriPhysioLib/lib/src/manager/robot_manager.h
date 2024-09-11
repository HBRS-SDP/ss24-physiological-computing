#ifndef HRI_PHYSIO_ROBOT_MANAGER_H
#define HRI_PHYSIO_ROBOT_MANAGER_H

#include <iostream>
#include <chrono>

#include <yaml-cpp/yaml.h>

#include "thread_manager.h"
#include "../stream/csv_streamer.h"
#include "../social/robot_interface.h"

class RobotManager : public ThreadManager {
    bool log_data;
    std::string log_name;

    CSVStreamer robot_logger;
    RobotInterface *robot;

    std::chrono::system_clock::time_point start_time;

public:
    explicit RobotManager(RobotInterface *robot);

    ~RobotManager() override;

    void configure(int argc, char **argv);

    void interactive();

private:
    static bool get_functions(const std::vector<std::string> &input);

    bool thread_init();

    void process(const std::string &input);

    bool set_functions(const std::vector<std::string> &input) const;

    void self_loop() const;

    void input_loop();
};

#endif //HRI_PHYSIO_ROBOT_MANAGER_H
