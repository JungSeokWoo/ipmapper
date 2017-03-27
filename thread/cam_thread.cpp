#include "cam_thread.h"

bool CAM_THREAD::CamStreaming()
{
    vc>>ori_img;
    if(ori_img.empty())
        return false;

    return true;
}

void CAM_THREAD::SLOT_MAIN_2_CAM_THREAD(bool _pause_status)
{
    pause_status = _pause_status;

    if(pause_status)
    {
        while(this->isRunning()){};
        this->exit();
    }
    else
    {
        this->start();
    }
}

void CAM_THREAD::run()
{
    vc.open("rtsp://192.168.0.26/unicast/mjpeg:video_stream_2.ini");

    while(!pause_status)
    {
        if(!CamStreaming())
            continue;
        emit SIG_CAM_THREAD_2_MAIN(ori_img);
        QThread::usleep(10);
    }

    return;
}
