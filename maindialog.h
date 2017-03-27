#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

#include "custom_widget/custom_scene.h"
#include "thread/cam_thread.h"
#include "thread/view_thread.h"
#include "imgproc/CCAMCalib.h"
#include "imgproc/utils.hpp"

// Qt header
#include <QWidget>
#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QtGui>
#include <QThread>
#include <QPixmap>
#include <QGraphicsScene>
#include <QMutex>


// opencv header ----------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/video/video.hpp>
// ------------------------

// stl
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <algorithm>
#include <fstream>
#include <sys/time.h>
#include <ctime>
#include <cstdlib>


using namespace std;

namespace Ui {
class MAINDIALOG;
}

class MAINDIALOG : public QDialog
{
    Q_OBJECT

public:
    explicit MAINDIALOG(QWidget *parent = 0);
    ~MAINDIALOG();

private:
    Ui::MAINDIALOG *ui;

    QImage Mat2QImage(cv::Mat _src);

    // streaming puase
    bool pause_status = true;

    // member variables
    cv::Mat ori_img;
    cv::Mat resize_img;
    cv::Mat calibration_img;
    cv::Mat ipm_img;
    cv::Mat disp_img_left;
    cv::Mat disp_img_right;

    QImage disp_img_left_q;
    QPixmap disp_img_left_p;
    CUSTOM_SCENE *disp_img_left_scene = new CUSTOM_SCENE;

    QImage disp_img_right_q;
    QPixmap disp_img_right_p;
    CUSTOM_SCENE *disp_img_right_scene = new CUSTOM_SCENE;

    CCAMCalib calib_obj;
    // widget & scene


    // thread
    CAM_THREAD *cam_thread;
    VIEW_THREAD *view_thread;


    // Display_mutex
    QMutex mtx_disp;

signals:
    void SIG_MAIN_2_CAM_THREAD(bool);

public slots:
    void SLOT_CAM_THREAD_2_MAIN(cv::Mat _ori_img);
    void SLOT_VIEW_THREAD_2_MAIN();

private slots:
    void on_pushButton_stream_clicked();
    void on_pushButton_cal_ipm_clicked();
};

#endif // MAINDIALOG_H
