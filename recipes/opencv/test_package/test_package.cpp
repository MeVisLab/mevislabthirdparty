#include <opencv2/calib.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/features.hpp>
#include <opencv2/geometry.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/photo.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/registry.hpp>

#include <cmath>
#include <iostream>

int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        std::cerr << "missing image path" << std::endl;
        return 1;
    }

    cv::Mat frame = cv::imread(argv[1]);
    if (frame.empty())
    {
        std::cerr << "failed to read image" << std::endl;
        return 1;
    }

    cv::Mat frame_gray;
    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(frame_gray, frame_gray, cv::Size(5, 5), 0.0);
    if (!cv::imwrite("out.jpg", frame_gray))
    {
        std::cerr << "failed to write output image" << std::endl;
        return 1;
    }

    const cv::aruco::Dictionary dictionary =
        cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    cv::Mat marker;
    cv::aruco::generateImageMarker(dictionary, 23, 200, marker);
    cv::copyMakeBorder(marker, marker, 40, 40, 40, 40, cv::BORDER_CONSTANT, cv::Scalar(255));
    std::vector<std::vector<cv::Point2f>> corners;
    std::vector<int> ids;
    cv::aruco::ArucoDetector(dictionary).detectMarkers(marker, corners, ids);
    if (ids.size() != 1 || ids[0] != 23)
    {
        std::cerr << "aruco marker detection failed" << std::endl;
        return 1;
    }

    std::vector<cv::KeyPoint> keypoints;
    cv::ORB::create()->detect(frame_gray, keypoints);
    if (keypoints.empty())
    {
        std::cerr << "ORB found no keypoints" << std::endl;
        return 1;
    }

    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(32, 32));
    if (blob.dims != 4 || blob.size[0] != 1 || blob.size[1] != 3 || blob.size[2] != 32 ||
        blob.size[3] != 32)
    {
        std::cerr << "unexpected blob shape" << std::endl;
        return 1;
    }

    cv::Mat denoised;
    cv::fastNlMeansDenoising(frame_gray, denoised, 3.0f);
    if (denoised.size() != frame_gray.size())
    {
        std::cerr << "denoising failed" << std::endl;
        return 1;
    }

    cv::Ptr<cv::BackgroundSubtractorMOG2> subtractor = cv::createBackgroundSubtractorMOG2();
    cv::Mat foreground;
    subtractor->apply(frame_gray, foreground);
    subtractor->apply(frame_gray, foreground);
    if (foreground.size() != frame_gray.size() || foreground.type() != CV_8UC1)
    {
        std::cerr << "background subtraction failed" << std::endl;
        return 1;
    }

    std::vector<cv::Point2f> source{{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    std::vector<cv::Point2f> target{{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    cv::Mat homography = cv::findHomography(source, target);
    if (homography.empty() ||
        std::abs(homography.at<double>(0, 0) / homography.at<double>(2, 2) - 2.0) > 1e-6)
    {
        std::cerr << "unexpected homography" << std::endl;
        return 1;
    }

#ifndef _WIN32
    if (cv::videoio_registry::getBackends().empty())
    {
        std::cerr << "no videoio backends" << std::endl;
        return 1;
    }
    cv::VideoWriter writer("out.avi", cv::CAP_OPENCV_MJPEG,
                           cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10.0, frame.size());
    if (!writer.isOpened())
    {
        std::cerr << "failed to open MJPEG video writer" << std::endl;
        return 1;
    }
    writer.write(frame);
    writer.write(frame);
    writer.release();
    cv::VideoCapture capture("out.avi", cv::CAP_OPENCV_MJPEG);
    cv::Mat decoded;
    if (!capture.isOpened() || !capture.read(decoded) || decoded.size() != frame.size())
    {
        std::cerr << "failed to read back MJPEG video" << std::endl;
        return 1;
    }
#endif

    std::cout << "success" << std::endl;
    return 0;
}
