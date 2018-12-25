#ifndef VELOCITY_AFFECTOR_H
#define VELOCITY_AFFECTOR_H

#include "particleAffector.h"

//! Velocity modes.
enum VelocityMode
{
	V_OVER_LIFE = 0, //! Affect velocity over life time of the particles mode.
	V_RANDOM, //! Affect the velocity of the particles randomly mode.
	V_SPIRAL_MOTION //! Affect the velocity of the particles in a spiral motion mode.
};

class VelocityAffector : public ParticleAffector
{
private:

	VelocityMode m_velocity_mode = V_OVER_LIFE; //! Mode of the Velocity Affector.

	Vector3 m_velocity_start; //! Initial velocity of the affector.
	Vector3 m_velocity_end; //! Final velocity of the affector.

	float m_velocity_scale_x; //! Strength of the velocity in x direction.
	float m_velocity_scale_y; //! Strength of the velocity in y direction.

	float m_velocity_x_max;  // Maximum velocity in x direction.
	float m_velocity_y_max; // Maximum velocity in y direction.

	float m_velocity_x_min; // Minimum velocity in x direction.
	float m_velocity_y_min; // Minimum velocity in y direction.

	float m_spiral_value; //! Spiral intensity.


public:
	// Constructor of Velocity Affector.
	VelocityAffector();
	//! Constructor of Velocity Affector with start and end velocity settings, the mode of this affector is set as V_OVER_LIFE.
	VelocityAffector(Vector3 start, Vector3 end);
	//! Constructor of Velocity Affector with spiral intensity and velocity (x and y directions) settings, the mode of this affector is set as V_SPIRAL_MOTION.
	VelocityAffector(float spiralIntensity, float velocity_x, float velocity_y);
	//! Constructor of Velocity Affector with minimum and maximum value for x and y velocity directions settings, the mode of this affector is set as V_RANDOM.
	VelocityAffector(float maxX, float minX, float maxY, float minY);
	~VelocityAffector();

	void affectParticle(ParticleObject* particle);
	//! Return velocity over life time of the particle object.
	Vector3 velocityOverLife(float curLifespan, float baseLifespan);
	//! Return velocity from the randomized values between the maximum and minimun values of velocity in x direction as well as between the maximum and minimun values of velocity.
	Vector3 randomizeVelocity();
	//! Return velocity from the randomized values between the maximum and minimun values of velocity in x direction as well as between the maximum and minimun values of velocity in y direction over life time of the particle object.
	Vector3 randomizeVelocityOverLife(float curLifespan, float baseLifespan);
	//! Return the spiral velocity.
	Vector3 spiralMotion(float curLifespan, float baseLifespan);

};


#endif //! VELOCITY_AFFECTOR_H
