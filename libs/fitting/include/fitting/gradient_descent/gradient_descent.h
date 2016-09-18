#ifndef CLOUD_FITTING_GRADIENT_DESCENT_H
#define CLOUD_FITTING_GRADIENT_DESCENT_H


#include <infinity_cad/rendering/render_objects/cloud.h>

/**
 * Used to pass to contructor for Gradient parameters
 */
struct GradientParams{
    int max_iterations;
    float tolerance;
    float learning_rate;

    float translation_weight;
    float rotation_weight;

    // Should be (0,0,0) by default
    glm::vec3 origins;
};

/**
 * The 6-dimensional input vector for the Gradient Function
 */
struct GradientTheta{
    glm::vec3 translation;
    glm::vec3 rotation;
};


/**
 * Gradient Descent for 6-dimensional problem of translating/rotating
 * a cloud of points to fit a given Rigid Object.
 */
class GradientDescent {
public:

    GradientDescent(Cloud* cloud,
                    RigidObject* rigid_object, GradientParams params);

    ~GradientDescent();

    /**
     * Returns the resulting theta.
     */
    GradientTheta RunGradient();

private:

    /**
     * Returns false if should converged
     */
    bool RunIteration();

    /**
     * Updates the cloud with current theta
     */
    void UpdateCloud();

    /**
     * Computes the next gradient.
     */
    void ComputeAndUpdateGradient();

    /**
     * Computes gradient for specific dimension of the input vector.
     */
    float ComputeGradientTranslationX(const GradientTheta& theta);
    float ComputeGradientTranslationY(const GradientTheta& theta);
    float ComputeGradientTranslationZ(const GradientTheta& theta);
    float ComputeGradientRotationX(const GradientTheta& theta);
    float ComputeGradientRotationY(const GradientTheta& theta);
    float ComputeGradientRotationZ(const GradientTheta& theta);

    float ComputeGoalFunction();

    Cloud* cloud_;
    RigidObject* rigid_object_;

    /**
     * Current theta value.
     */
    GradientTheta theta_;

    GradientTheta last_theta_;
    float last_value_;

    GradientParams params_;
};


#endif //CLOUD_FITTING_GRADIENT_DESCENT_H
