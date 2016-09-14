#include "cloud_fitting_thread.h"

#include <fitting/cloud_fitter.h>

CloudFittingThread::CloudFittingThread(){
    this->sphere = nullptr;
    this->cloud = nullptr;
}

void CloudFittingThread::setCloud(Cloud* cloud){
    this->cloud = cloud;
}

void CloudFittingThread::setSphere(Sphere* sphere){
    this->sphere = sphere;
}

void CloudFittingThread::run(){
    CloudFitter cloudFitter(cloud, sphere);
    cloudFitter.startFitting();
}
