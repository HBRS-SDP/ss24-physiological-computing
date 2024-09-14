/* ================================================================================
 * Copyright: (C) 2021, SIRRL Social and Intelligent Robotics Research Laboratory, 
 *     University of Waterloo, All rights reserved.
 * 
 * Authors: 
 *     Austin Kothig <austin.kothig@uwaterloo.ca>
 * 
 * CopyPolicy: Released under the terms of the BSD 3-Clause License. 
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */

/* ================================================================================
 * Copyright: (C) 2024, Vedika Chauhan,
 *     Hochschule Bonn-Rhein-Sieg (H-BRS), All rights reserved.
 * 
 * Author: 
 *     Vedika Chauhan <vedika.chauhan@smail.inf.h-brs.de>
 * 
 * CopyPolicy: Released under the terms of the MIT License.
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */

#ifndef HRI_PHYSIO_ROBOT_MANAGER_H
#define HRI_PHYSIO_ROBOT_MANAGER_H

#include <iostream>
#include <chrono>
#include <yaml-cpp/yaml.h>
#include "thread_manager.h"
#include "../stream/csv_streamer.h"
#include "../social/robot_interface.h"

/**
 * @class RobotManager
 * Manages the robot operations and logging.
 */
class RobotManager final : public ThreadManager
{
    /**
     * Flag to indicate if data logging is enabled.
     */
    bool log_data;

    /**
     * Name of the log file.
     */
    std::string log_name;

    /**
     * CSV streamer for logging robot data.
     */
    CSVStreamer robot_logger;

    /**
     * Pointer to the robot interface.
     */
    RobotInterface *robot;

    /**
     * Start time of the robot manager.
     */
    std::chrono::system_clock::time_point start_time;

public:
    /**
     * Constructor to initialize the RobotManager with a robot interface.
     * @param robot Pointer to the robot interface.
     */
    explicit RobotManager(RobotInterface *robot);

    /**
     * Destructor to clean up resources.
     */
    ~RobotManager();

    /**
     * Configures the robot manager with command-line arguments.
     * @param argc Argument count.
     * @param argv Argument vector.
     */
    void configure(int argc, char **argv);

    /**
     * Starts the interactive mode of the robot manager.
     */
    void interactive();

private:
    /**
     * Initializes the thread.
     * @return True if initialization is successful, false otherwise.
     */
    bool thread_init();

    /**
     * Processes the input command.
     * @param input Input command as a string.
     */
    void process(const std::string &input);

    /**
     * Sets functions based on the input commands.
     * @param input Vector of input commands.
     * @return True if functions are set successfully, false otherwise.
     */
    bool set_functions(const std::vector<std::string> &input);

    /**
     * Gets functions based on the input commands.
     * @param input Vector of input commands.
     * @return True if functions are retrieved successfully, false otherwise.
     */
    bool get_functions(const std::vector<std::string> &input);

    /**
     * Main loop for self operations.
     */
    void self_loop();

    /**
     * Main loop for input operations.
     */
    void input_loop();
};

#endif // HRI_PHYSIO_ROBOT_MANAGER_H
