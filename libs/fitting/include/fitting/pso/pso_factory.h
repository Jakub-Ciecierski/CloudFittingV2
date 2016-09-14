//
// Created by jakub on 3/29/16.
//

#ifndef MG1_PSO_FACTORY_H
#define MG1_PSO_FACTORY_H


#include <pso/pso.h>
#include <pso/particle_factory.h>
#include <infinity_cad/rendering/render_objects/cloud.h>

class PSOFactory {
private:
    Cloud* cloud;
    RigidObject* rigidBody;

    int swarmSize;
    double maxVelocity;

    int particleDimension;

    double posIntervalMin;
    double posIntervalMax;

    double velIntervalMin;
    double velIntervalMax;

    double learningFactor;
    double particleVelocityWeight;

    int maximumIterations;
    int threadCount;

    pso::ParticleFactory createParticleFactory(int swarmSize,
                                              int particleDimension,
                                              double posIntervalMin,
                                              double posIntervalMax,
                                              double velIntervalMin,
                                              double velIntervalMax,
                                              double maxVelocity );

    pso::ParticleDecoder* createParticleDecoder();

    pso::FitnessUpdater* createFitnessUpdater(
            pso::ParticleShPtr_ConstVectorShPtr particles,
            pso::ParticleDecoder * particleDecoder);

    pso::NeighbourhoodUpdater* createNeighbourhoodUpdater(
            pso::ParticleShPtr_ConstVectorShPtr particles);

    pso::ParticleUpdater* createPaticleUpdater(
            pso::ParticleShPtr_ConstVectorShPtr particles,
            double learningFactor, double velocityWeight);

public:
    PSOFactory(Cloud* cloud, RigidObject* rigidBody,
               int swarmSize, double maxVelocity,
               int maximumIterations, int threadCount);

    ~PSOFactory();

    pso::PSO* createPSO();
};


#endif //MG1_PSO_FACTORY_H
