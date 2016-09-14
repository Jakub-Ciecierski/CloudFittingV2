//
// Created by jakub on 3/29/16.
//

#include <fitting/cloud_fitter.h>

#include <pso/pso.h>
#include <fitting/pso/pso_factory.h>
#include <threading/thread_util.h>
#include <fitting/pso/transform_vector.h>

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


//-----------------------//
//  PUBLIC 
//-----------------------//

void CloudFitter::startFitting(){
    int swarmSize = 150;
    double maxVelocity = 2.0f;
    int maximumIterations = 1000;
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