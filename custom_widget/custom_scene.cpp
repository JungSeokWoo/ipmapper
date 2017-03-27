#include "custom_scene.h"

void CUSTOM_SCENE::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode == DrawLine)
        origPoint = event->scenePos();

    mouse_click_x_loc = event->scenePos().x();
    mouse_click_y_loc = event->scenePos().y();

    if(current_ind != 4)
    {
        current_loc.x = mouse_click_x_loc*2;
        current_loc.y = mouse_click_y_loc*2;
        pt_list.push_back(current_loc);
        current_ind++;
    }
    else
    {
        pt_list.clear();
        current_ind = 0;
    }
    QGraphicsScene::mousePressEvent(event);
}

void CUSTOM_SCENE::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    mouse_x_loc = event->scenePos().x();
    mouse_y_loc = event->scenePos().y();
}

void CUSTOM_SCENE::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    itemToDraw = 0;

    mouse_finish_x_loc = event->scenePos().x();
    mouse_finish_y_loc = event->scenePos().y();

    QGraphicsScene::mouseReleaseEvent(event);
}

void CUSTOM_SCENE::mouseWheelEvent(QGraphicsSceneWheelEvent *event)
{
    scroll_val += event->delta()/120;
}

