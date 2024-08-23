#ifndef HRI_PHYSIO_ROBOT_INTERFACE_H
#define HRI_PHYSIO_ROBOT_INTERFACE_H

#include <string>
#include <iostream>
#include <vector>

enum Peripheral {
    HEAD, RIGHT_ARM, LEFT_ARM, RIGHT_LEG, LEFT_LEG
};

class RobotInterface {
protected:
    std::string name;

public:
    RobotInterface();

    virtual bool configure(int argc, char **argv) = 0;

    virtual void robot_loop() = 0;

    virtual bool get_robot_command(std::string &command) = 0;

    virtual bool add_audio_file(std::string filename, size_t channel = -1) = 0;

    virtual bool add_video_file(std::string filename) = 0;

    virtual bool set_periph_state(Peripheral perph, std::vector<double> &position) = 0;

    virtual bool add_gesture(std::string gesture, double speed = 1.0) = 0;

    virtual bool set_emotion_state(std::string emotion) = 0;

    virtual bool add_speech(std::string phrase) = 0;

    virtual bool set_speech_config(std::string config) = 0;

    virtual bool set_volume(double percent) = 0;
};


#endif //HRI_PHYSIO_ROBOT_INTERFACE_H
