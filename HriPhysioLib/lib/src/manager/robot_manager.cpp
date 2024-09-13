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
#include "robot_manager.h"
#include "../utilities/arg_parser.h"
#include "../utilities/helpers.h"

RobotManager::RobotManager(RobotInterface *robot) : log_data(false), robot(robot)
{
}

RobotManager::~RobotManager() = default;

void RobotManager::configure(int argc, char **argv)
{
    robot->configure(argc, argv);

    ArgParser args(argc, argv);

    const std::string &yaml_file = args.get_cmd_option("--conf");
    YAML::Node config = YAML::LoadFile(yaml_file);

    log_data = config["log_data"].as<bool>(false);
    log_name = config["log_name"].as<std::string>("");

    if (log_data && log_name.empty())
    {
        this->close();
        return;
    }

    if (log_data)
    {
        robot_logger.set_name(log_name);
        robot_logger.set_data_type("STRING");
        robot_logger.set_num_channels(1);

        if (!robot_logger.open_output_stream())
        {
            std::cerr << "Could not open logger stream.\n";
            this->close();
            return;
        }
    }

    this->thread_init();
    start_time = std::chrono::system_clock::now();
}

void RobotManager::interactive()
{
    std::string input;
    while (this->get_manager_running())
    {
        std::cout << ">>> ";
        getline(std::cin, input);

        this->process(input);
    }
}

bool RobotManager::thread_init()
{
    add_loop_thread([this]
                    { self_loop(); });
    add_loop_thread([this]
                    { input_loop(); });
    return true;
}

void RobotManager::process(const std::string &input)
{
    if (this->log_data)
    {
        std::chrono::duration<double> now = std::chrono::system_clock::now() - start_time;
        double time = now.count();
        this->robot_logger.publish(input, &time);
    }

    std::vector<std::string> input_vector = parse_string(input);
    if (input_vector.empty())
    {
        return;
    }

    std::string command = input_vector[0];
    command = to_uppercase(command);
    if (command == "exit")
    {
        robot->add_audio_file("exit");
        robot->add_video_file("exit");

        this->close();
    }
    else if (command == "set")
    {
        if (!this->set_functions(input_vector))
        {
            auto set_input = combine_string(input_vector, 1);
            std::cerr << "[ERROR] Unrecognized set input: "
                      << set_input
                      << std::endl;
        }
    }
    else if (command == "get")
    {
        if (!this->get_functions(input_vector))
        {
            auto get_input = combine_string(input_vector, 1);
            std::cerr << "[ERROR] Unrecognized input get: "
                      << get_input
                      << std::endl;
        }
    }
    else if (command == "help")
    {
        // TODO: help is undefined
        std::cerr << "[ERROR] HELP!" << std::endl;
    }
    else
    {
        std::cerr << "[ERROR] Unrecognized command: "
                  << command
                  << std::endl;
    }
}

bool RobotManager::set_functions(const std::vector<std::string> &input)
{
    if (input.size() < 2)
    {
        return false;
    }

    std::string function = input[1];
    function = to_lowercase(function);

    if (function == "state")
    {
        if (input.size() < 4)
        {
            return false;
        }

        std::string perph = input[2];
        perph = to_lowercase(perph);

        std::vector<double> pos = to_vec_double(input, 3);
        if (perph == "head")
        {
            return robot->set_periph_state(Peripheral::HEAD, pos);
        }
        else if (perph == "rightarm")
        {
            return robot->set_periph_state(Peripheral::RIGHT_ARM, pos);
        }
        else if (perph == "leftarm")
        {
            return robot->set_periph_state(Peripheral::LEFT_ARM, pos);
        }
        else if (perph == "rightleg")
        {
            return robot->set_periph_state(Peripheral::RIGHT_LEG, pos);
        }
        else if (perph == "leftleg")
        {
            return robot->set_periph_state(Peripheral::LEFT_LEG, pos);
        }
    }
    else if (function == "velocity")
    {
        // setPerphVelocity(const peripheral perph, const std::vector<double>& speed);
    }
    else if (function == "gesture")
    {
        if (input.size() == 3)
        {
            return robot->add_gesture(input[2]);
        }
        else if (input.size() == 4)
        {
            return robot->add_gesture(input[2], std::stod(input[3]));
        }
        else
        {
            return false;
        }
    }
    else if (function == "emotion")
    {
        if (input.size() != 3)
        {
            return false;
        }

        return robot->set_emotion_state(input[2]);
    }
    else if (function == "speech")
    {
        if (input.size() < 3)
        {
            return false;
        }

        std::string phrase = combine_string(input, 2);
        return robot->add_speech(phrase);
    }
    else if (function == "speechConfig")
    {
        if (input.size() < 3)
        {
            return false;
        }

        std::string config = combine_string(input, 2);
        return robot->set_speech_config(config);
    }
    else if (function == "volume")
    {
        if (input.size() != 3)
        {
            return false;
        }

        return robot->set_volume(std::stod(input[2]));
    }
    else if (function == "audio")
    {
        if (input.size() == 3)
        {
            return robot->add_audio_file(input[2]);
        }
        else if (input.size() == 4)
        {
            return robot->add_audio_file(input[2], std::stoi(input[3]));
        }
        else
        {
            return false;
        }
    }
    else if (function == "video")
    {
        if (input.size() != 3)
        {
            return false;
        }

        return robot->add_video_file(input[2]);
    }

    return false;
}

bool RobotManager::get_functions(const std::vector<std::string> &input)
{
    // TODO: this function does nothing
    return false;
}

void RobotManager::self_loop()
{
    robot->robot_loop();
};

void RobotManager::input_loop()
{
    std::string command;
    bool ret = robot->get_robot_command(command);

    if (ret)
    {
        this->process(command);
    }
}
