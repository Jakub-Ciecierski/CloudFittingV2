//
// Created by jakub on 3/29/16.
//

#include <pso/particle_decoder.h>
#include <pso/entities/particle.h>
#include <fitting/pso/cloud_fitness.h>
#include <fitting/pso/transform_vector.h>
#include <threading/thread_util.h>
#include <infinity_cad/rendering/render_objects/cloud.h>
#include "infinity_cad/math/math.h"

using namespace pso;
using namespace std;
using namespace glm;

//-----------------------//
//  CONSTRUCTORS
//-----------------------//

CloudFitness::CloudFitness(ParticleShPtr_ConstVectorShPtr particles,
                           const ParticleDecoder * particleDecoder,
                           Cloud* cloud, RigidObject* rigidBody) :
    FitnessUpdater(particles, particleDecoder),
    cloud(cloud), rigidBody(rigidBody){
    distancesWeight = 1;
    normalAnglesWeight = 1;
}

CloudFitness::~CloudFitness() {

}

//-----------------------//
//  PRIVATE
//-----------------------//

double CloudFitness::computeGoalFunction(Cloud* cloud, RigidObject* rigidBody){
    float sumOfDistances = 0;
    float sumOfNormals = 0;

    const vector<vec4>& worldVertices = cloud->getWorldVertices();
    for(auto worldVertex : worldVertices){
        vec3 vertex(worldVertex.x, worldVertex.y, worldVertex.z);
        vec3 clostestPoint = rigidBody->getClosestPoint(vertex);

        double distance = euclideanDistance(clostestPoint, vertex);
        sumOfDistances += distance;
    }

    for(unsigned int i = 0; i < worldVertices.size(); i++){
        vec4 v4 = worldVertices[i];
        vec3 v = vec3(v4.x, v4.y, v4.z);
        vec3 clostestPoint = rigidBody->getClosestPoint(v);

        vec3 cloudNormal = cloud->getNormalAt(i);
        vec3 sphereNormal = rigidBody->computeNormal(clostestPoint);

        float value = 1 - ifc::dot(cloudNormal, sphereNormal);
        sumOfNormals += value;
    }

    double goalValue = (distancesWeight * sumOfDistances) +
            (normalAnglesWeight * sumOfNormals);

    return goalValue;
}

float CloudFitness::euclideanDistance(const vec3& v1, const vec3& v2){
    float distance = 0;

    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;
    distance = dx*dx + dy*dy + dz*dz;

    distance = sqrt(distance);

    return distance;
}

//-----------------------//
//  PROTECTED
//-----------------------//

double CloudFitness::fitnessValue(const pso::Particle &p) {
    TransformVector* tv =
            (TransformVector*)this->particleDecoder->decodeCurrent(p);

    //std::vector<glm::vec4> points = this->cloud->getWorldVertices();
    //Cloud* tmpCloud = new Cloud(SceneID(), points);
    Cloud tmpCloud = *this->cloud;

    tmpCloud.moveTo(tv->x, tv->y, tv->z);
    tmpCloud.rotateTo(tv->xAngle, tv->yAngle, tv->zAngle);
    tmpCloud.update();

    double fitness = computeGoalFunction(&tmpCloud, rigidBody);

    //delete tmpCloud;
    delete tv;
    return fitness;
}

//-----------------------//
//  PUBLIC
//-----------------------//


void CloudFitness::actOn(Particle& particle){
    TransformVector* tv =
            (TransformVector*)this->particleDecoder->decodeCurrent(particle);
    tv->transform(cloud);
    threading::threadSleep(1);
}
