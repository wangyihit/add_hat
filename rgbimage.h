#ifndef RGBIMAGE_H
#define RGBIMAGE_H
#include <string>
// OpenCV Headers
#include <opencv2/opencv.hpp>

class RgbImage
{
public:
    RgbImage(std::string& impage_path);
    int loadImage();
    int loadGrayImage();
    int loadRgbImage();
    void show(const char* title="");
    void save(const char* file_path);
    cv::Size getSize();
    cv::Mat img;

protected:
    int _loadImage(int color);

private:
    std::string image_path;
};

#endif // RGBIMAGE_H
