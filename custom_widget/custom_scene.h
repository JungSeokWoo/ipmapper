#ifndef CUSTOM_SCENE_H
#define CUSTOM_SCENE_H

#include <QWidget>
#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QtGui>
#include <QThread>
#include <QPixmap>

#include <QMetaType>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMoveEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsLineItem>

#include <iostream>
#include <vector>

using namespace std;

struct scene_pt_struct{
    int x;
    int y;
};

class CUSTOM_SCENE : public QGraphicsScene
{

public:
    enum Mode {NoMode, SelectObject, DrawLine};
    CUSTOM_SCENE(QObject* parent = 0)
    {

    }
    void setMode(Mode mode);


    int mouse_click_x_loc = 0;
    int mouse_click_y_loc = 0;

    scene_pt_struct current_loc;


    int mouse_start_x_loc = 0;
    int mouse_start_y_loc = 0;
    int mouse_finish_x_loc = 0;
    int mouse_finish_y_loc = 0;

    int mouse_x_loc;
    int mouse_y_loc;

    int scroll_val = 0;

    int current_ind = 0;

    vector<scene_pt_struct> pt_list;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseWheelEvent(QGraphicsSceneWheelEvent *event);

//    void keyPressEvent(QKeyEvent *event);
private:
    Mode sceneMode = DrawLine;


    QPointF origPoint;
    QGraphicsLineItem* itemToDraw;
    void makeItemsControllable(bool areControllable);

};



#endif // CUSTOM_SCENE_H
