//
// Created by jakub on 3/29/16.
//

#ifndef MG1_CLOUDFITTER_H
#define MG1_CLOUDFITTER_H

#include <infinity_cad/rendering/render_objects/cloud.h>

class CloudFitter {
private:
    RigidObject* rigidBody;
    Cloud* cloud;

public:

    CloudFitter(Cloud* cloud, RigidObject* rigidBody);

    ~CloudFitter();

    void startFitting();

};


#endif //MG1_CLOUDFITTER_H
