#include "rgbimage.h"

RgbImage::RgbImage(std::string& img_path):image_path(img_path)
{

}
int RgbImage::_loadImage(int color)
{
    this->img = cv::imread(this->image_path, color);
    if(this->image_path.empty()){
        return -1;
    }
    return 0;
}
int RgbImage::loadImage()
{
    return this->_loadImage(cv::IMREAD_UNCHANGED);
}

int RgbImage::loadGrayImage()
{
    return this->_loadImage(cv::IMREAD_GRAYSCALE);
}
void RgbImage::show(const char *title)
{
    cv::imshow(title, this->img);
}

cv::Size RgbImage::getSize()
{
    return cv::Size(this->img.cols, this->img.rows);
}

void RgbImage::save(const char *file_path)
{
     cv::imwrite(file_path, this->img);
}

int RgbImage::loadRgbImage()
{
    return this->_loadImage(cv::IMREAD_COLOR);
}
