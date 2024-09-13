#ifndef HRI_PHYSIO_ROBOT_INTERFACE_H
#define HRI_PHYSIO_ROBOT_INTERFACE_H

#include <string>
#include <iostream>

/**
 * @enum Peripheral
 * @brief Enumeration for robot peripherals.
 */
enum Peripheral
{
    HEAD,      ///< Head peripheral
    RIGHT_ARM, ///< Right arm peripheral
    LEFT_ARM,  ///< Left arm peripheral
    RIGHT_LEG, ///< Right leg peripheral
    LEFT_LEG   ///< Left leg peripheral
};

/**
 * @class RobotInterface
 * @brief Abstract base class for robot interfaces.
 */
class RobotInterface
{
protected:
    /**
     * @brief Name of the robot.
     */
    std::string name;

public:
    /**
     * @brief Constructor for RobotInterface.
     */
    RobotInterface();

    /**
     * @brief Configures the robot with command-line arguments.
     * @param argc Argument count.
     * @param argv Argument vector.
     * @return True if configuration is successful, false otherwise.
     */
    virtual bool configure(int argc, char **argv) = 0;

    /**
     * @brief Main loop for robot operations.
     */
    virtual void robot_loop() = 0;

    /**
     * @brief Retrieves the robot command.
     * @param command Reference to a string where the command will be stored.
     * @return True if a command is retrieved, false otherwise.
     */
    virtual bool get_robot_command(std::string &command) = 0;

    /**
     * @brief Adds an audio file to the robot.
     * @param filename Name of the audio file.
     * @param channel Channel to add the audio file to (default is -1).
     * @return True if the audio file is added successfully, false otherwise.
     */
    virtual bool add_audio_file(std::string filename, size_t channel = -1) = 0;

    /**
     * @brief Adds a video file to the robot.
     * @param filename Name of the video file.
     * @return True if the video file is added successfully, false otherwise.
     */
    virtual bool add_video_file(std::string filename) = 0;

    /**
     * @brief Sets the state of a peripheral.
     * @param perph Peripheral to set the state for.
     * @param position Vector of positions for the peripheral.
     * @return True if the state is set successfully, false otherwise.
     */
    virtual bool set_periph_state(Peripheral perph, std::vector<double> &position) = 0;

    /**
     * @brief Adds a gesture to the robot.
     * @param gesture Name of the gesture.
     * @param speed Speed of the gesture (default is 1.0).
     * @return True if the gesture is added successfully, false otherwise.
     */
    virtual bool add_gesture(std::string gesture, double speed = 1.0) = 0;

    /**
     * @brief Sets the emotion state of the robot.
     * @param emotion Name of the emotion.
     * @return True if the emotion state is set successfully, false otherwise.
     */
    virtual bool set_emotion_state(std::string emotion) = 0;

    /**
     * @brief Adds a speech phrase to the robot.
     * @param phrase Speech phrase to add.
     * @return True if the speech phrase is added successfully, false otherwise.
     */
    virtual bool add_speech(std::string phrase) = 0;

    /**
     * @brief Sets the speech configuration for the robot.
     * @param config Speech configuration.
     * @return True if the configuration is set successfully, false otherwise.
     */
    virtual bool set_speech_config(std::string config) = 0;

    /**
     * @brief Sets the volume of the robot.
     * @param percent Volume percentage to set.
     * @return True if the volume is set successfully, false otherwise.
     */
    virtual bool set_volume(double percent) = 0;
};

#endif // HRI_PHYSIO_ROBOT_INTERFACE_H