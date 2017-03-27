#include "view_thread.h"

void VIEW_THREAD::run()
{
    while(true)
    {
        emit SIG_VIEW_THREAD_2_MAIN();
        QThread::msleep(10);
    }
}
