//
// Created by jakub on 3/29/16.
//

#include <infinity_cad/rendering/render_objects/cloud.h>

#include "infinity_cad/math/math.h"

using namespace std;
using namespace glm;

//-----------------------//
//  CONSTRUCTORS
//-----------------------//

Cloud::Cloud(SceneID id, std::vector<glm::vec4>& points) :
        RenderObject(id){
    vertices = points;
    initVertices();
    initEdges();

    worldVertices.resize(vertices.size());
}
Cloud::Cloud(SceneID id, std::string name,
             std::vector<glm::vec4>& points) :
        RenderObject(id, name){
    vertices = points;
    initVertices();
    initEdges();

    worldVertices.resize(vertices.size());
}

Cloud::~Cloud() {

}


//-----------------------//
//  PROTECTED
//-----------------------//


void Cloud::initVertices(){

}

void Cloud::initEdges() {

}

void Cloud::drawLines(bool costumColor) {
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for(unsigned int i = 0; i < vertices.size(); i++){
        if(NDCVertices[i].w < 0) continue;

        glVertex2f(NDCVertices[i].x, NDCVertices[i].y);
    }
    glEnd();
}

//-----------------------//
//  PUBLIC
//-----------------------//

const std::vector<glm::vec4>& Cloud::getWorldVertices(){
    const mat4& ModelMatrix = getModelMatrix();

    for(unsigned int i = 0; i < vertices.size(); i++){
        worldVertices[i] = ModelMatrix * vertices[i];
    }

    return this->worldVertices;
}

void Cloud::transform(const glm::mat4 &VP) {
    const mat4& ModelMatrix = getModelMatrix();
    mat4 MVP = VP * ModelMatrix;
    transformPosition(VP);

    unsigned int verticesSize = vertices.size();
    if (NDCVertices == NULL)
        NDCVertices = (vec4 *) malloc(vertices.size() * sizeof(vec4));

    for(unsigned int i = 0; i < verticesSize ; i++){
        worldVertices[i] = ModelMatrix * vertices[i];

        NDCVertices[i] = MVP * vertices[i];

        NDCVertices[i].x /= NDCVertices[i].w;
        NDCVertices[i].y /= NDCVertices[i].w;
        NDCVertices[i].z /= NDCVertices[i].w;

    }
}

glm::vec3 Cloud::getNormalAt(int i){
    if(i < 0 || i >= worldVertices.size())
        return vec3(-999, -999, -999);

    vec4 point4 = worldVertices[i];
    vec3 point = vec3(point4.x, point4.y, point4.z);
    std::vector<vec3> closestPoints = getClosestPoints(point, 2, i);

    vec3 tangent1 = closestPoints[0] - point;
    vec3 tangent2 = closestPoints[1] - point;

    glm::vec3 normal = glm::normalize(glm::cross(tangent1, tangent2));

    return normal;
}

std::vector<vec3> Cloud::getClosestPoints(const vec3& point, int count, int ignore){
    std::vector<vec3> closestVertices;
    std::vector<vec3> tmpWorldVertices;
    for(unsigned int i = 0; i < worldVertices.size(); i++){
        vec4 p4 = worldVertices[i];
        vec3 p = vec3(p4.x, p4.y, p4.z);
        if(i == ignore) continue;

        tmpWorldVertices.push_back(p);
    }

    //vec3 closest = vec3(closest4.x, closest4.y, closest4.z);

    int counter = 0;
    while(counter++ < count){
        int closestIndex = 0;
        vec3 closest = tmpWorldVertices[closestIndex];

        for(unsigned int i = 0; i < tmpWorldVertices.size(); i++){
            if(ifc::euclideanDistance(point, tmpWorldVertices[i]) < ifc::euclideanDistance(point, closest)){
                closest = tmpWorldVertices[i];
                closestIndex = i;
            }
        }
        closestVertices.push_back(closest);
        tmpWorldVertices.erase(tmpWorldVertices.begin() + closestIndex);
    }
    return closestVertices;
}
