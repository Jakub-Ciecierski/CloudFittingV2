//
// Created by jakub on 3/29/16.
//

#ifndef MG1_CLOUDFITTER_H
#define MG1_CLOUDFITTER_H

#include <infinity_cad/rendering/render_objects/cloud.h>
#include <fitting/gradient_descent/gradient_descent.h>

enum class CloudFittingAlgorithm{
    PSO, GRADIENT_DESCENT
};

class CloudFitter {
private:
    RigidObject* rigidBody;
    Cloud* cloud;

    void startPSO();
    void startGradientDescent();

    GradientParams gradient_params;

public:

    CloudFitter(Cloud* cloud, RigidObject* rigidBody);

    ~CloudFitter();

    void startFitting(CloudFittingAlgorithm type = CloudFittingAlgorithm::PSO);

    void setGradientParams(GradientParams params){this->gradient_params =
                                                          params;}
};


#endif //MG1_CLOUDFITTER_H
