#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class Settings
{
public:
    Settings();
    void init(int argc, char* argv[]);
    std::string avatar_image;
    std::string hat_image;
    std::string output;
    void dump();
};

#endif // SETTINGS_H
