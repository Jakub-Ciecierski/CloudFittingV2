#ifndef CLOUD_FITTING_GRADIENT_DESCENT_H
#define CLOUD_FITTING_GRADIENT_DESCENT_H


#include <infinity_cad/rendering/render_objects/cloud.h>

/**
 * Used to pass to contructor for Gradient parameters
 */
struct GradientParams{
    int max_iterations;
    double learning_rate;

    double translation_weight;
    double rotation_weight;

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
    void UpdateCloud(const GradientTheta& theta);

    /**
     * Computes the next gradient.
     */
    void ComputeAndUpdateGradient();

    /**
     * Computes gradient for specific dimension of the input vector.
     */
    double ComputeGradientTranslationX(const GradientTheta& theta);
    double ComputeGradientTranslationY(const GradientTheta& theta);
    double ComputeGradientTranslationZ(const GradientTheta& theta);
    double ComputeGradientRotationX(const GradientTheta& theta);
    double ComputeGradientRotationY(const GradientTheta& theta);
    double ComputeGradientRotationZ(const GradientTheta& theta);

    double ComputeGoalFunction(const GradientTheta& theta);

    Cloud* cloud_;
    RigidObject* rigid_object_;

    /**
     * Current theta value.
     */
    GradientTheta theta_;

    GradientTheta last_theta_;
    double last_value_;

    GradientParams params_;
};


#endif //CLOUD_FITTING_GRADIENT_DESCENT_H
