#include "cloud_fitting_thread.h"

CloudFittingThread::CloudFittingThread(){
    this->sphere = nullptr;
    this->cloud = nullptr;

    algorithm_type = CloudFittingAlgorithm::PSO;
}

void CloudFittingThread::setCloud(Cloud* cloud){
    this->cloud = cloud;
}

void CloudFittingThread::setSphere(Sphere* sphere){
    this->sphere = sphere;
}

void CloudFittingThread::setType(CloudFittingAlgorithm algorithm_type){
    this->algorithm_type = algorithm_type;
}

void CloudFittingThread::setGradientParams(GradientParams params){
    this->params = params;
}


void CloudFittingThread::run(){
    CloudFitter cloudFitter(cloud, sphere);
    cloudFitter.setGradientParams(params);

    cloudFitter.startFitting(algorithm_type);
}
