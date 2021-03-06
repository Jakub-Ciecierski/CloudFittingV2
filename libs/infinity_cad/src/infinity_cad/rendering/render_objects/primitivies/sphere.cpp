//
// Created by jakub on 3/29/16.
//


#include <math/random.h>
#include <infinity_cad/rendering/render_objects/primitivies/sphere.h>
#include <infinity_cad/rendering/scene/object_factory.h>


using namespace glm;
using namespace std;

//-----------------------//
//  CONSTRUCTORS
//-----------------------//

Sphere::Sphere(SceneID id, std::string name,
               float radius, int ringsCount, int sectionCount) :
        RenderObject(id, name),
        radius(radius), ringsCount(ringsCount), sectionCount(sectionCount) {
    initVertices();
    initEdges();

    //drawingMode = GL_TRIANGLE_FAN;
}

Sphere::Sphere(SceneID id,
               float radius, int ringsCount, int sectionCount) :
        RenderObject(id),
        radius(radius), ringsCount(ringsCount), sectionCount(sectionCount) {
    initVertices();
    initEdges();

    //drawingMode = GL_TRIANGLE_FAN;
}

Sphere::~Sphere() {

}

//-----------------------//
//  PRIVATE
//-----------------------//

float Sphere::getX(float s, float r){
    float x = cos(s) * sin(r);
    x *= radius;

    return x;
}
float Sphere::getY(float s, float r){
    float y = cos((r));
    y *= radius;

    return y;
}
float Sphere::getZ(float s, float r){
    float z = sin(s) * sin(r);
    z *=radius;

    return z;
}

//-----------------------//
//  PROTECTED
//-----------------------//

void Sphere::initVertices() {
    float R = 1.0 / (float) (ringsCount -1);
    float S = 1.0 / (float) (sectionCount -1);

    for(int r = 0; r < ringsCount; r++){
        for(int s = 0; s < sectionCount; s++){

            float x = getX(2*M_PI * s * S, M_PI * r * R);
            float y = getY(0, M_PI * r * R);
            float z = getZ(2*M_PI * s * S, M_PI * r * R);

            vertices.push_back(vec4(x,y,z,1));
        }
    }
}

void Sphere::initEdges() {
    for(int r = 0; r < ringsCount - 1; r++){
        for(int s = 0; s < sectionCount - 1; s++){
            int i = r * sectionCount + s;
            int j = r * sectionCount + (s+1);

            int k = (r + 1) * sectionCount + (s+1);
            int l = (r + 1) * sectionCount + (s);

            edges.push_back(Edge(i,j));
            edges.push_back(Edge(j,k));
            edges.push_back(Edge(k,l));
        }
    }
}

//-----------------------//
//  PUBLIC
//-----------------------//

Cloud* Sphere::extractRandomCloud(int verticesCount,
                                  float sDivider, float rDivider,
                                  float distortion){
    rnd::seed();

    vector<vec4> points(verticesCount);

    float min = 0.0f;
    float maxS = (float)2*M_PI / sDivider;
    float maxR = (float)M_PI / rDivider;

    for(int i = 0; i < verticesCount; i++){
        float s = rnd::generateRandomNumber(min, maxS);
        float r = rnd::generateRandomNumber(min, maxR);

        float x = getX(s,r);
        float y = getY(s,r);
        float z = getZ(s,r);

        float minDistortion = 0.0;
        float maxDistortion = distortion;
        float xDist = rnd::generateRandomNumber(minDistortion, maxDistortion);
        float yDist = rnd::generateRandomNumber(minDistortion, maxDistortion);
        float zDist = rnd::generateRandomNumber(minDistortion, maxDistortion);

        points[i] = vec4(x + xDist, y + yDist, z + zDist, 1);
    }
    ObjectFactory& objectFactory = ObjectFactory::getInstance();
    Cloud* cloud = objectFactory.createCloud("Cloud", points);

    return cloud;
}

glm::vec3 Sphere::getClosestPoint(const glm::vec3& point) {
    const vec3& c = getPosition();

    vec3 diff = point - c;
    vec3 v = diff;
    float length = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    float m = radius / length;

    vec3 closestPoint = c + m*diff;

    return closestPoint;
}

glm::vec3 Sphere::computeNormal(const glm::vec3& v) {
    return glm::normalize(getPosition() - v);
}
