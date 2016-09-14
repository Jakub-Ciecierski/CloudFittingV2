//
// Created by jakub on 3/29/16.
//

#ifndef MG1_FITTING_WORKSHOP_H
#define MG1_FITTING_WORKSHOP_H

#include <infinity_cad/rendering/scene/scene.h>
#include <infinity_cad/rendering/render_objects/primitivies/sphere.h>

class FittingWorkshop {
private:
    Scene* scene;

    Sphere* sphere;
    std::vector<Cloud*> clouds;

    void createSphere();
    void createClouds();

public:

    FittingWorkshop(Scene* scene);

    ~FittingWorkshop();

    void startExperiment(unsigned int i);
};


#endif //MG1_FITTING_WORKSHOP_H
