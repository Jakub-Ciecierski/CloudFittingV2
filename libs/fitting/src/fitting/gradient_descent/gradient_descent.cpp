#include <fitting/gradient_descent/gradient_descent.h>
#include <iostream>

#include "infinity_cad/math/math.h"

GradientDescent::GradientDescent(Cloud* cloud,
                                 RigidObject* rigid_object,
                                 GradientParams params) :
    cloud_(cloud),
    rigid_object_(rigid_object),
    params_(params),
    last_value_(99999){

}

GradientDescent::~GradientDescent(){

}

GradientTheta GradientDescent::RunGradient(){
    for(int i = 0; i < params_.max_iterations; i++){
        if(!RunIteration()){
            std::cout << "Converged" << std::endl;
            break;
        }
    }

    return theta_;
}

bool GradientDescent::RunIteration(){
    UpdateCloud();
    ComputeAndUpdateGradient();

    float goal_value = ComputeGoalFunction();
    std::cout << goal_value << std::endl;

    if(goal_value >= last_value_) {
        std::cout << "Reseting Iteration" << std::endl;
        params_.learning_rate /= 2;
        theta_ = last_theta_;
        if(params_.learning_rate < 0.001)
            return false;
    }else{
        last_value_ = goal_value;
        last_theta_ = theta_;
    }

    return true;
}

void GradientDescent::UpdateCloud(){
    cloud_->moveTo(theta_.translation);
    cloud_->rotateTo(theta_.rotation);
}

void GradientDescent::ComputeAndUpdateGradient(){
    // Simultaneous theta update.
    GradientTheta tmp_theta = theta_;

    theta_.translation.x = tmp_theta.translation.x -
            (params_.learning_rate * ComputeGradientTranslationX(tmp_theta));
    theta_.translation.y = tmp_theta.translation.y -
            (params_.learning_rate * ComputeGradientTranslationY(tmp_theta));
    theta_.translation.z = tmp_theta.translation.z -
            (params_.learning_rate * ComputeGradientTranslationZ(tmp_theta));

    theta_.rotation.x = theta_.rotation.x -
            (params_.learning_rate * ComputeGradientRotationX(tmp_theta));
    theta_.rotation.y = theta_.rotation.y -
            (params_.learning_rate * ComputeGradientRotationY(tmp_theta));
    theta_.rotation.z = theta_.rotation.z -
            (params_.learning_rate * ComputeGradientRotationZ(tmp_theta));
}

float GradientDescent::ComputeGradientTranslationX(const GradientTheta& theta){
    const std::vector<glm::vec4>& points
            = cloud_->getWorldVertices();
    float translation_sum = 0;
    float rotation_sum = 0;

    for(unsigned int i = 0; i < points.size(); i++){
        glm::vec3 point = ifc::toVec3(points[i]);

        glm::vec3 clostest_point = rigid_object_->getClosestPoint(point);
        glm::vec3 rigid_normal = rigid_object_->computeNormal(clostest_point);

        glm::vec3 origin_diff = point - params_.origins;
        glm::vec3 distance_diff = point - clostest_point;
        glm::vec3 point_derivative = glm::vec3(theta.translation.x, 0, 0);

        translation_sum +=
                ifc::dot(distance_diff, point_derivative - rigid_normal);
    }
    translation_sum *= 2*params_.translation_weight;

    return translation_sum + rotation_sum;
}

float GradientDescent::ComputeGradientTranslationY(const GradientTheta& theta){
    const std::vector<glm::vec4>& points
            = cloud_->getWorldVertices();
    float translation_sum = 0;
    float rotation_sum = 0;

    for(unsigned int i = 0; i < points.size(); i++){
        glm::vec3 point = ifc::toVec3(points[i]);

        glm::vec3 clostest_point = rigid_object_->getClosestPoint(point);
        glm::vec3 rigid_normal = rigid_object_->computeNormal(clostest_point);

        glm::vec3 origin_diff = point - params_.origins;
        glm::vec3 distance_diff = point - clostest_point;
        glm::vec3 point_derivative = glm::vec3(0, theta.translation.y, 0);

        translation_sum +=
                ifc::dot(distance_diff, point_derivative - rigid_normal);
    }
    translation_sum *= 2*params_.translation_weight;

    return translation_sum + rotation_sum;
}

float GradientDescent::ComputeGradientTranslationZ(const GradientTheta& theta){
    const std::vector<glm::vec4>& points
            = cloud_->getWorldVertices();
    float translation_sum = 0;
    float rotation_sum = 0;

    for(unsigned int i = 0; i < points.size(); i++){
        glm::vec3 point = ifc::toVec3(points[i]);

        glm::vec3 clostest_point = rigid_object_->getClosestPoint(point);
        glm::vec3 rigid_normal = rigid_object_->computeNormal(clostest_point);

        glm::vec3 origin_diff = point - params_.origins;
        glm::vec3 distance_diff = point - clostest_point;
        glm::vec3 point_derivative = glm::vec3(0, 0, theta.translation.z);

        translation_sum +=
                ifc::dot(distance_diff, point_derivative - rigid_normal);
    }
    translation_sum *= 2*params_.translation_weight;

    return translation_sum + rotation_sum;
}

float GradientDescent::ComputeGradientRotationX(const GradientTheta& theta){
    const std::vector<glm::vec4>& points
            = cloud_->getWorldVertices();
    float translation_sum = 0;
    float rotation_sum = 0;

    for(unsigned int i = 0; i < points.size(); i++){
        // Translation
        glm::vec3 point = ifc::toVec3(points[i]);

        glm::vec3 clostest_point = rigid_object_->getClosestPoint(point);
        glm::vec3 rigid_normal = rigid_object_->computeNormal(clostest_point);

        glm::vec3 origin_diff = point - params_.origins;
        glm::vec3 distance_diff = point - clostest_point;
        glm::vec3 point_derivative
                = glm::vec3(0,
                            -(theta.rotation.x * origin_diff.z),
                            theta.rotation.x * origin_diff.y);

        translation_sum +=
                ifc::dot(distance_diff, point_derivative - rigid_normal);

        // Rotation
        glm::vec3 normal_derivative
                = glm::vec3(0,
                            -(theta.rotation.x * origin_diff.z),
                            theta.rotation.x * origin_diff.y);
        rotation_sum += -ifc::dot(normal_derivative, rigid_normal);
    }
    translation_sum *= 2*params_.translation_weight;
    rotation_sum *= params_.rotation_weight;

    return translation_sum + rotation_sum;
}

float GradientDescent::ComputeGradientRotationY(const GradientTheta& theta){
    const std::vector<glm::vec4>& points
            = cloud_->getWorldVertices();
    float translation_sum = 0;
    float rotation_sum = 0;

    for(unsigned int i = 0; i < points.size(); i++){
        // Translation
        glm::vec3 point = ifc::toVec3(points[i]);

        glm::vec3 clostest_point = rigid_object_->getClosestPoint(point);
        glm::vec3 rigid_normal = rigid_object_->computeNormal(clostest_point);

        glm::vec3 origin_diff = point - params_.origins;
        glm::vec3 distance_diff = point - clostest_point;
        glm::vec3 point_derivative
                = glm::vec3(theta.rotation.y * origin_diff.z,
                            0,
                            -(theta.rotation.y * origin_diff .x));

        translation_sum +=
                ifc::dot(distance_diff, point_derivative - rigid_normal);

        // Rotation
        glm::vec3 normal_derivative
                = glm::vec3(theta.rotation.y * origin_diff.z,
                            0,
                            -(theta.rotation.y * origin_diff.x));
        rotation_sum += -ifc::dot(normal_derivative, rigid_normal);
    }
    translation_sum *= 2*params_.translation_weight;
    rotation_sum *= params_.rotation_weight;

    return translation_sum + rotation_sum;
}

float GradientDescent::ComputeGradientRotationZ(const GradientTheta& theta){
    const std::vector<glm::vec4>& points
            = cloud_->getWorldVertices();
    float translation_sum = 0;
    float rotation_sum = 0;

    for(unsigned int i = 0; i < points.size(); i++){
        // Translation
        glm::vec3 point = ifc::toVec3(points[i]);

        glm::vec3 clostest_point = rigid_object_->getClosestPoint(point);
        glm::vec3 rigid_normal = rigid_object_->computeNormal(clostest_point);

        glm::vec3 origin_diff = point - params_.origins;
        glm::vec3 distance_diff = point - clostest_point;
        glm::vec3 point_derivative
                = glm::vec3(theta.rotation.z * origin_diff.y,
                            theta.rotation.z * origin_diff.x, 0);

        translation_sum +=
                ifc::dot(distance_diff, point_derivative - rigid_normal);

        // Rotation
        glm::vec3 normal_derivative
                = glm::vec3(theta.rotation.z * origin_diff.y,
                            theta.rotation.z * origin_diff.x,
                            0);
        rotation_sum += -ifc::dot(normal_derivative, rigid_normal);
    }
    translation_sum *= 2*params_.translation_weight;
    rotation_sum *= params_.rotation_weight;

    return translation_sum + rotation_sum;
}

float GradientDescent::ComputeGoalFunction(){
    float sumOfDistances = 0;
    float sumOfNormals = 0;

    const std::vector<glm::vec4>& points = cloud_->getWorldVertices();
    for(auto worldVertex : points){
        glm::vec3 vertex(worldVertex.x, worldVertex.y, worldVertex.z);
        glm::vec3 clostestPoint = rigid_object_->getClosestPoint(vertex);

        double distance = ifc::euclideanDistance(clostestPoint, vertex);
        sumOfDistances += distance;
    }

    for(unsigned int i = 0; i < points.size(); i++){
        glm::vec4 v4 = points[i];
        glm::vec3 v = glm::vec3(v4.x, v4.y, v4.z);
        glm::vec3 clostestPoint = rigid_object_->getClosestPoint(v);

        glm::vec3 cloudNormal = cloud_->getNormalAt(i);
        glm::vec3 sphereNormal = rigid_object_->computeNormal(clostestPoint);

        float value = 1 - ifc::dot(cloudNormal, sphereNormal);
        sumOfNormals += value;
    }

    float goalValue = (params_.translation_weight * sumOfDistances) +
            (params_.rotation_weight * sumOfNormals);

    return goalValue;
}