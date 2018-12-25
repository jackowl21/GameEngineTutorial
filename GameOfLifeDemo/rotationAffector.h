#ifndef ROTATION_AFFECTOR_H
#define ROTATION_AFFECTOR_H

#include "particleAffector.h"

//! Rotation modes.
enum RotationMode
{
	R_NORMAL = 0, //! Normal Rotation Mode
	R_RANDOM //! Random Rotation Mode
};

class RotationAffector : public ParticleAffector
{
private:

	//! Mode of the Rotation Affector.
	RotationMode m_rotation_mode = R_NORMAL;

	float m_rotation;
	// Minimum rotation value.
	float m_rotation_min;
	// Maximum rotation value.
	float m_rotation_max;

public:

	RotationAffector();
	//! Constructor of Rotation Affector with rotation setting, the mode of this affector is set as R_NORMAL.
	RotationAffector(float rotation);
	//! Constructor of Rotation Affector with minimum and maximum rotation setting, the mode of this affector is set as R_RANDOM.
	RotationAffector(float rotation_min, float rotation_max);
	~RotationAffector();

	void affectParticle(ParticleObject* particle);

	//! Return randomized rotaion value in float between m_rotation_min and m_rotation_max.
	float randomizeRotation();
	//! Return  rotaion value based on the lifetime of the particle.
	float rotationOverLife(float curLifespan, float baseLifespan);

};

#endif // !ROTATION_AFFECTOR_H

