#include "scm_sphere.h"

#include "scene_cmenu_handlers.h"

SCMSphere::SCMSphere() : SceneContextMenu()
{
    init();
}

void SCMSphere::init(){
    this->addHandlerAndAction(SCENE_MENU_MOVE_CROSS_HANDLER);
    this->addHandlerAndAction(SCENE_MENU_MOVE_CAMERA_HANDLER);

    this->addSeparator();
    this->addHandlerAndAction(SCENE_MENU_CHANGE_NAME_HANDLER);

    this->addSeparator();
    this->addHandlerAndAction(SCM_CLOUD_HANDLER);

    this->addSeparator();
    this->addHandlerAndAction(SCENE_MENU_DELETE_HANDLER);
}
