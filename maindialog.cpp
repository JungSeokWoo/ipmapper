#include "maindialog.h"
#include "ui_maindialog.h"

MAINDIALOG::MAINDIALOG(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MAINDIALOG)
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    ui->setupUi(this);

    cam_thread = new CAM_THREAD;
    view_thread = new VIEW_THREAD;

    connect(cam_thread,SIGNAL(SIG_CAM_THREAD_2_MAIN(cv::Mat)),this,SLOT(SLOT_CAM_THREAD_2_MAIN(cv::Mat)));
    connect(this,SIGNAL(SIG_MAIN_2_CAM_THREAD(bool)),cam_thread,SLOT(SLOT_MAIN_2_CAM_THREAD(bool)));
    connect(view_thread,SIGNAL(SIG_VIEW_THREAD_2_MAIN()),this,SLOT(SLOT_VIEW_THREAD_2_MAIN()));

    view_thread->start();
}

MAINDIALOG::~MAINDIALOG()
{
    delete ui;
}

void MAINDIALOG::SLOT_CAM_THREAD_2_MAIN(cv::Mat _ori_img)
{
    mtx_disp.lock();
    ori_img = _ori_img;

    calibration_img = calib_obj.ReMap(ori_img);

    cv::Size disp_size;
    disp_size.width = 640;
    disp_size.height = 360;
    cv::resize(calibration_img,disp_img_left,disp_size);
    disp_img_left_q = Mat2QImage(disp_img_left);
    disp_img_left_p.convertFromImage(disp_img_left_q);
    disp_img_left_scene->clear();
    disp_img_left_scene->addPixmap(disp_img_left_p);
    ui->graphicsView_stream->setScene(disp_img_left_scene);
    ui->graphicsView_stream->show();

    ui->lineEdit_img_width->setText(QString::number(ori_img.cols));
    ui->lineEdit_img_height->setText(QString::number(ori_img.rows));

    // Inverse Perspective Mapping
    if(ui->checkBox_ipm->isChecked())
    {
        cv::Mat ipm_lambda;
        FileStorage fs("ipm_param.xml",FileStorage::READ);
        fs["ipm_lambda"] >> ipm_lambda;
        fs.release();
        warpPerspective(calibration_img,ipm_img,ipm_lambda,calibration_img.size());
//        disp_img_right = ResizeRemainAR(ipm_img,cv::Size(280,432));

        cv::resize(ipm_img,disp_img_right,cv::Size(),0.3,0.3);
        disp_img_right_q = Mat2QImage(disp_img_right);
        disp_img_right_p.convertFromImage(disp_img_right_q);
        disp_img_right_scene->clear();
        disp_img_right_scene->addPixmap(disp_img_right_p);
        ui->graphicsView_ipm->setScene(disp_img_right_scene);
        ui->graphicsView_ipm->show();
    }

    mtx_disp.unlock();
}

void MAINDIALOG::SLOT_VIEW_THREAD_2_MAIN()
{
    if( disp_img_left_scene->pt_list.size() >= 1)
    {
        for(int i = 1; i <= disp_img_left_scene->pt_list.size();i++)
        {
            cv::Point circle_center;

            switch(i)
            {
            case 1:
                ui->lineEdit_pt_1_x->setText(QString::number(disp_img_left_scene->pt_list.at(i-1).x));
                ui->lineEdit_pt_1_y->setText(QString::number(disp_img_left_scene->pt_list.at(i-1).y));
                circle_center.x = disp_img_left_scene->pt_list.at(i-1).x*0.5;
                circle_center.y = disp_img_left_scene->pt_list.at(i-1).y*0.5;
                cv::circle(disp_img_left,circle_center,3,cv::Scalar(0,0,255),3,cv::FILLED);
                break;

            case 2:
                ui->lineEdit_pt_2_x->setText(QString::number(disp_img_left_scene->pt_list.at(i-1).x));
                ui->lineEdit_pt_2_y->setText(QString::number(disp_img_left_scene->pt_list.at(i-1).y));
                circle_center.x = disp_img_left_scene->pt_list.at(i-1).x*0.5;
                circle_center.y = disp_img_left_scene->pt_list.at(i-1).y*0.5;
                cv::circle(disp_img_left,circle_center,3,cv::Scalar(0,0,255),3,cv::FILLED);
                break;

            case 3:
                ui->lineEdit_pt_3_x->setText(QString::number(disp_img_left_scene->pt_list.at(i-1).x));
                ui->lineEdit_pt_3_y->setText(QString::number(disp_img_left_scene->pt_list.at(i-1).y));
                circle_center.x = disp_img_left_scene->pt_list.at(i-1).x*0.5;
                circle_center.y = disp_img_left_scene->pt_list.at(i-1).y*0.5;
                cv::circle(disp_img_left,circle_center,3,cv::Scalar(0,0,255),3,cv::FILLED);
                break;

            case 4:
                ui->lineEdit_pt_4_x->setText(QString::number(disp_img_left_scene->pt_list.at(i-1).x));
                ui->lineEdit_pt_4_y->setText(QString::number(disp_img_left_scene->pt_list.at(i-1).y));
                circle_center.x = disp_img_left_scene->pt_list.at(i-1).x*0.5;
                circle_center.y = disp_img_left_scene->pt_list.at(i-1).y*0.5;
                cv::circle(disp_img_left,circle_center,3,cv::Scalar(0,0,255),3,cv::FILLED);

                for(int j = 1; j <= 4;j++)
                {
                    if(j != 4)
                    {
                        cv::Point start_pt, end_pt;
                        start_pt.x = disp_img_left_scene->pt_list.at(j-1).x*0.5;
                        start_pt.y = disp_img_left_scene->pt_list.at(j-1).y*0.5;
                        end_pt.x = disp_img_left_scene->pt_list.at(j).x*0.5;
                        end_pt.y = disp_img_left_scene->pt_list.at(j).y*0.5;

                        cv::line(disp_img_left,start_pt,end_pt,cv::Scalar(0,0,255),1);

                    }
                    else
                    {
                        cv::Point start_pt, end_pt;
                        start_pt.x = disp_img_left_scene->pt_list.at(3).x*0.5;
                        start_pt.y = disp_img_left_scene->pt_list.at(3).y*0.5;
                        end_pt.x = disp_img_left_scene->pt_list.at(0).x*0.5;
                        end_pt.y = disp_img_left_scene->pt_list.at(0).y*0.5;

                        cv::line(disp_img_left,start_pt,end_pt,cv::Scalar(0,0,255),1);

                    }
                }

                break;
            }

            disp_img_left_q = Mat2QImage(disp_img_left);
            disp_img_left_p.convertFromImage(disp_img_left_q);
            disp_img_left_scene->clear();
            disp_img_left_scene->addPixmap(disp_img_left_p);
            ui->graphicsView_stream->setScene(disp_img_left_scene);
            ui->graphicsView_stream->show();

        }
    }
    else
    {
        if(!ori_img.empty())
        {
            cv::Size disp_size;
            disp_size.width = 640;
            disp_size.height = 360;
            cv::resize(calibration_img,disp_img_left,disp_size);
            disp_img_left_q = Mat2QImage(disp_img_left);
            disp_img_left_p.convertFromImage(disp_img_left_q);
            disp_img_left_scene->clear();
            disp_img_left_scene->addPixmap(disp_img_left_p);
            ui->graphicsView_stream->setScene(disp_img_left_scene);
            ui->graphicsView_stream->show();
        }
    }
}

QImage MAINDIALOG::Mat2QImage(cv::Mat _src)
{
    cv::Mat temp; // make the same cv::Mat
    cv::cvtColor(_src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits(); // enforce deep copy, see documentation
    // of QImage::QImage ( const uchar * data, int width, int height, Format format )
    return dest;
}

void MAINDIALOG::on_pushButton_stream_clicked()
{
    if(pause_status)
    {
        ui->pushButton_stream->setText("Stream Stop");
        pause_status = false;
        emit SIG_MAIN_2_CAM_THREAD(pause_status);
    }
    else
    {
        ui->pushButton_stream->setText("Stream Start");
        pause_status = true;
        emit SIG_MAIN_2_CAM_THREAD(pause_status);
    }
}

void MAINDIALOG::on_pushButton_cal_ipm_clicked()
{
    cv::Mat ipm_lambda(2,4,CV_32FC1);
    cv::Point2f inputQuad_pt[4];
    cv::Point2f outputQuad_pt[4];
    for(int i = 1; i <= 4; i++)
    {
        inputQuad_pt[i] = cv::Point2f(disp_img_left_scene->pt_list.at(i-1).x,disp_img_left_scene->pt_list.at(i-1).y);
    }

    ipm_lambda = cv::Mat::zeros(calibration_img.rows,calibration_img.cols,calibration_img.type());
    outputQuad_pt[0] = cv::Point2f(ui->lineEdit_lt_bias_x->text().toDouble(),ui->lineEdit_lt_bias_y->text().toDouble());
    outputQuad_pt[1] = cv::Point2f(ui->lineEdit_lt_bias_x->text().toDouble() + ui->lineEdit_rect_width->text().toDouble(),ui->lineEdit_lt_bias_y->text().toDouble());
    outputQuad_pt[2] = cv::Point2f(ui->lineEdit_lt_bias_x->text().toDouble() + ui->lineEdit_rect_width->text().toDouble(),ui->lineEdit_lt_bias_y->text().toDouble() + ui->lineEdit_rect_height->text().toDouble());
    outputQuad_pt[3] = cv::Point2f(ui->lineEdit_lt_bias_x->text().toDouble(),ui->lineEdit_lt_bias_y->text().toDouble() + ui->lineEdit_rect_height->text().toDouble());
    ipm_lambda = cv::getPerspectiveTransform(inputQuad_pt,outputQuad_pt);

    FileStorage fs("ipm_param.xml",FileStorage::WRITE);
    fs << "ipm_lambda" << ipm_lambda;
    fs.release();
}
