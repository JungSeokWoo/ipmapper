#ifndef VIEW_THREAD_H
#define VIEW_THREAD_H

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

class VIEW_THREAD : public QThread {
    Q_OBJECT
public:
    VIEW_THREAD(){}
    ~VIEW_THREAD(){}

private:
    void run();

private:
    bool pause_status = false;

signals:
    void SIG_VIEW_THREAD_2_MAIN();

};




#endif // VIEW_THREAD_H
