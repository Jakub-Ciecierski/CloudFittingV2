#include "scm_cloud_fitting.h"
#include "scene_cmenu_handlers.h"

SCMCloudFitting::SCMCloudFitting() : SceneContextMenu()
{
    init();
    runForOneSelectedItem = true;
}

void SCMCloudFitting::init(){
    this->addHandlerAndAction(SCM_CLOUD_FITTING_PSO_HANDLER);
    this->addHandlerAndAction(SCM_CLOUD_FITTING_GRADIENT_HANDLER);
}
