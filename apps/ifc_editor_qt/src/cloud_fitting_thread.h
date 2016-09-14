#ifndef CLOUDFITTINGTHREAD_H
#define CLOUDFITTINGTHREAD_H

#include <QtCore>

#include <infinity_cad/rendering/render_objects/cloud.h>
#include <infinity_cad/rendering/render_objects/primitivies/sphere.h>

class CloudFittingThread : public QThread
{
public:
    CloudFittingThread();

    void run();

    void setCloud(Cloud* cloud);
    void setSphere(Sphere* sphere);

private:
    Cloud* cloud;
    Sphere* sphere;
};

#endif // CLOUDFITTINGTHREAD_H
