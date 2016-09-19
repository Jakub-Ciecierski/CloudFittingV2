//
// Created by jakub on 3/29/16.
//

#include <fitting/cloud_fitter.h>

#include <pso/pso.h>
#include <fitting/pso/pso_factory.h>
#include <threading/thread_util.h>
#include <fitting/pso/transform_vector.h>
#include <fitting/gradient_descent/gradient_descent.h>

using namespace pso;

//-----------------------//
//  CONSTRUCTORS
//-----------------------//

CloudFitter::CloudFitter(Cloud *cloud, RigidObject *rigidBody) :
    cloud(cloud), rigidBody(rigidBody){
}

CloudFitter::~CloudFitter() {

}

//-----------------------//
//  PRIVATE
//-----------------------//

void CloudFitter::startPSO(){
    int swarmSize = 150;
    double maxVelocity = 2.0f;
    int maximumIterations = 150;
    int threadCount = threading::getNumberOfCores();
    if (threadCount < 1) threadCount = 4;

    PSOFactory psoFactory(cloud, rigidBody,
                          swarmSize, maxVelocity,
                          maximumIterations, threadCount);
    PSO* pso = psoFactory.createPSO();
    pso->start();

    TransformVector* tv = (TransformVector*)pso->getBestPSOObject();
    tv->transform(cloud);
    cloud->update();

    delete pso;
    delete tv;
}

void CloudFitter::startGradientDescent(){
    GradientTheta theta =
            GradientDescent(cloud, rigidBody, gradient_params).RunGradient();
    cloud->moveTo(theta.translation.x,
                  theta.translation.y,
                  theta.translation.z);
    cloud->rotateTo(theta.rotation.x,
                    theta.rotation.y,
                    theta.rotation.z);
    cloud->update();
}

//-----------------------//
//  PUBLIC 
//-----------------------//

void CloudFitter::startFitting(CloudFittingAlgorithm type){
    if(type == CloudFittingAlgorithm::PSO)
        startPSO();
    else if(type == CloudFittingAlgorithm::GRADIENT_DESCENT)
        startGradientDescent();
}