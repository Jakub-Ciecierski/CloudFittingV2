#ifndef CLOUDFITTINGTHREAD_H
#define CLOUDFITTINGTHREAD_H

#include <QtCore>

#include <infinity_cad/rendering/render_objects/cloud.h>
#include <infinity_cad/rendering/render_objects/primitivies/sphere.h>

#include <fitting/cloud_fitter.h>

class CloudFittingThread : public QThread
{
public:
    CloudFittingThread();

    void run();

    void setCloud(Cloud* cloud);
    void setSphere(Sphere* sphere);

    void setType(CloudFittingAlgorithm algorithm_type);
    void setGradientParams(GradientParams params);

private:
    Cloud* cloud;
    Sphere* sphere;

    GradientParams params;

    CloudFittingAlgorithm algorithm_type;
};

#endif // CLOUDFITTINGTHREAD_H
