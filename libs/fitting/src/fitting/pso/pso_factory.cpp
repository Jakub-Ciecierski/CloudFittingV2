//
// Created by jakub on 3/29/16.
//


#include <fitting/pso/pso_factory.h>
#include <fitting/pso/cloud_decoder.h>
#include <pso/neighbourhood_updaters/nb_star_topology.h>
#include <pso/particle_updaters/particle_updater_spherical.h>
#include <fitting/pso/cloud_fitness.h>


using namespace pso;

//-----------------------//
//  CONSTRUCTORS
//-----------------------//

PSOFactory::PSOFactory(Cloud* cloud, RigidObject* rigidBody,
                       int swarmSize, double maxVelocity,
                       int maximumIterations, int threadCount){
    this->cloud = cloud;
    this->rigidBody = rigidBody;
    this->swarmSize = swarmSize;

    this->maxVelocity = maxVelocity;

    this->maximumIterations = maximumIterations;
    this->threadCount = threadCount;

    particleDimension = 6;

    posIntervalMin = -16;
    posIntervalMax = 16;

    velIntervalMin = -5;
    velIntervalMax = 5;

    learningFactor = 0.5 + log(2.0);
    particleVelocityWeight = 1.0 / (2.0 * log(2.0));
}

PSOFactory::~PSOFactory() {

}

//-----------------------//
//  PRIVATE
//-----------------------//

ParticleFactory PSOFactory::createParticleFactory(int swarmSize,
                                                  int particleDimension,
                                                  double posIntervalMin,
                                                  double posIntervalMax,
                                                  double velIntervalMin,
                                                  double velIntervalMax,
                                                  double maxVelocity ){

    ParticleFactory particleFactory(
            swarmSize, particleDimension,
            posIntervalMin, posIntervalMax,
            velIntervalMin, velIntervalMax,
            maxVelocity
    );

    return particleFactory;
}

ParticleDecoder* PSOFactory::createParticleDecoder(){
    ParticleDecoder * particleDecoder = new CloudDecoder();

    return particleDecoder;
}

FitnessUpdater* PSOFactory::createFitnessUpdater(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder * particleDecoder){

    FitnessUpdater* fitnessUpdater = new CloudFitness(particles,
                                                      particleDecoder,
                                                      cloud, rigidBody);

    return fitnessUpdater;
}

NeighbourhoodUpdater* PSOFactory::createNeighbourhoodUpdater(
        ParticleShPtr_ConstVectorShPtr particles){
    int numberOfParticlesToInform = 3;
    NeighbourhoodUpdater* neighbourhoodUpdater = new NBStarTopology(
            particles, numberOfParticlesToInform
    );

    return neighbourhoodUpdater;
}


ParticleUpdater* PSOFactory::createPaticleUpdater(
        ParticleShPtr_ConstVectorShPtr particles,
        double learningFactor, double velocityWeight){
    int timesToAttemptPointGenerationWithinHyperSphere = 1;
    ParticleUpdater* particleUpdater = new ParticleUpdaterSpherical(
            particles,
            learningFactor,velocityWeight,
            timesToAttemptPointGenerationWithinHyperSphere
    );

    return particleUpdater;
}

//-----------------------//
//  PUBLIC 
//-----------------------//


pso::PSO *PSOFactory::createPSO() {

    ParticleFactory particleFactory
            = createParticleFactory(swarmSize, particleDimension,
                                    posIntervalMin, posIntervalMax,
                                    velIntervalMin, velIntervalMax,
                                    maxVelocity );

    ParticleShPtr_ConstVectorShPtr particles =
            particleFactory.createUnifromParticles();

    ParticleDecoder* particleDecoder = createParticleDecoder();
    FitnessUpdater* fitnessUpdater
            = createFitnessUpdater(particles, particleDecoder);

    NeighbourhoodUpdater* neighbourhoodUpdater
            = createNeighbourhoodUpdater(particles);


    ParticleUpdater* particleUpdater
            = createPaticleUpdater(particles, learningFactor,
                                   particleVelocityWeight);

    PSO * pso = new PSO(particles,
                        fitnessUpdater,
                        neighbourhoodUpdater,
                        particleUpdater,
                        maximumIterations, threadCount);

    return pso;
}
