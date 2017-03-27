#ifndef CAM_THREAD_H
#define CAM_THREAD_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Qt header
#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QtGui>
#include <QThread>
#include <QMetaType>
#include <QStandardItemModel>
#include <QProcess>

#include <iostream>

using namespace std;

class CAM_THREAD : public QThread {
    Q_OBJECT
public:
    CAM_THREAD(){}
    ~CAM_THREAD(){}

private:
    void run();
    bool CamStreaming();

private:
    bool pause_status = false;

    cv::VideoCapture vc;

    cv::Mat ori_img;

signals:
    void SIG_CAM_THREAD_2_MAIN(cv::Mat);

public slots:
    void SLOT_MAIN_2_CAM_THREAD(bool _pause_status);
};



#endif // CAM_THREAD_H
