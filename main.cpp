#include <stdio.h>
#include <vector>
#include "settings.h"
#include "rgbimage.h"

void drawCircle(cv::Mat& mat, cv::Rect& rect)
{
    cv::Point center(rect.x + rect.width/2, rect.y + rect.height/2);
    cv::ellipse(mat, center, cv::Size(rect.width/2, rect.height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
}

void drawRect(cv::Mat& mat, cv::Rect& rect)
{
    cv::Point center(rect.x + rect.width/2, rect.y + rect.height/2);
    // cv::ellipse(mat, center, cv::Size(rect.width/2, rect.height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
    cv::rectangle(mat, rect, cv::Scalar(255, 0, 255));
}

std::vector<cv::Rect> detectAndDisplay(cv::Mat& frame)
{
    cv::CascadeClassifier face_cascade;
    std::string face = "./haarcascades/haarcascade_frontalface_alt.xml";
    face = "./haarcascades/haarcascade_frontalface_default.xml";
    std::vector<cv::Rect> faces;
    std::vector<cv::Rect> hats;
    if(!face_cascade.load(face))
    {
        printf("Load cascade failed.\n");
        return hats;
    }
    cv::Mat frame_gray;
    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    face_cascade.detectMultiScale(frame, faces, 1.01, 20, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(60, 60));
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        if(faces[i].y == 0){
            // no place for the hat
            continue;
        }
        // drawCircle(frame, faces[i]);
        // drawRect(frame, faces[i]);
        cv::Rect& f = faces[i];
        int hat_with = f.width * 0.8;
        int hat_x = f.x + f.width * 0.1;
        int hat_y = f.y - f.height * 0.5;
        hat_y = hat_y > 0 ? hat_y : 0;
        int hat_height = f.y - hat_y;
        cv::Rect h(hat_x, hat_y, hat_with, hat_height);
        // drawRect(frame, h);
        hats.push_back(h);
    }
    //-- Show what you got
    // imshow("show", frame);
    return hats;
}

int main(int argc, char* argv[])
{
    Settings settings;
    settings.init(argc, argv);
    settings.dump();
    RgbImage avatar_img(settings.avatar_image);
    RgbImage hat_img(settings.hat_image);
    RgbImage mask(settings.hat_image);
    if(avatar_img.loadRgbImage()!= 0 ||
            hat_img.loadRgbImage() != 0)
    {
        printf("Load image failed.\n");
    }
    mask.loadGrayImage();
    threshold(mask.img, mask.img, 254, 255, CV_THRESH_BINARY);
    cv::Mat mask1 = 255 - mask.img;
    // cv::Mat imageROI;
    // imageROI = avatar_img.img(cv::Rect(110, 110, hat_img.img.cols, hat_img.img.rows));
    std::vector<cv::Rect> hat_rects = detectAndDisplay(avatar_img.img);
    for(size_t i = 0; i < hat_rects.size(); i++)
    {
        const cv::Mat& imageROI = avatar_img.img(hat_rects[i]);
        // resize hat image
        cv::Mat patch;
        cv::Mat patch_mask;
        cv::resize(hat_img.img, patch, cv::Size(imageROI.cols, imageROI.rows));
        cv::resize(mask1, patch_mask, cv::Size(imageROI.cols, imageROI.rows));
        patch.copyTo(imageROI, patch_mask);
    }

    avatar_img.save(settings.output.c_str());
    // avatar_img.show("patched");
    // cv::waitKey(0);
    return 0;
}
