#include "settings.h"
#include <fstream>
#include <iostream>
#include <gflags/gflags.h>
#include "common.h"

using namespace std;

static bool validate_file(const char* flagname, const string& file_path)
{
    UNUSED(flagname);

    ifstream file(file_path);
    if(!file.good()){
        return false;
    }
    return true;
}


DEFINE_string(avatar_image, "", "avatar image path");
DEFINE_validator(avatar_image, &validate_file);
DEFINE_string(hat_image, "", "hat image path");
DEFINE_validator(hat_image, &validate_file);
DEFINE_string(output, "output.jpg", "output image path");

Settings::Settings()
{

}

void Settings::init(int argc, char *argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    this->avatar_image = FLAGS_avatar_image;
    this->hat_image = FLAGS_hat_image;
    this->output = FLAGS_output;
}

#define dump_item(item) do {                 \
    cout << #item << ": " << item << endl;   \
}while(0);                                   \

void Settings::dump()
{
    dump_item(avatar_image);
    dump_item(hat_image);
}
