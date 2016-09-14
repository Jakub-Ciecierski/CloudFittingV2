//
// Created by jakub on 3/29/16.
//

#ifndef MG1_CLOUD_FITNESS_H
#define MG1_CLOUD_FITNESS_H

#include <pso/pso_common.h>
#include <pso/fitness_updater.h>
#include <infinity_cad/rendering/render_objects/cloud.h>


class CloudFitness : public pso::FitnessUpdater{
private:
    float distancesWeight;
    float normalAnglesWeight;

    Cloud* cloud;
    RigidObject* rigidBody;

    double computeGoalFunction(Cloud* cloud, RigidObject* rigidBody);
    float euclideanDistance(const glm::vec3& v1, const glm::vec3& v2);
protected:

    virtual double fitnessValue(const pso::Particle& p) override;


public:

    CloudFitness(pso::ParticleShPtr_ConstVectorShPtr particles,
                 const pso::ParticleDecoder * particleDecoder,
                 Cloud* cloud, RigidObject* rigidBody);

    virtual ~CloudFitness();

    void actOn(pso::Particle& particle) override;
};


#endif //MG1_CLOUD_FITNESS_H
