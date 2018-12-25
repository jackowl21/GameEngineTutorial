#ifndef SIZE_AFFECTOR_H
#define SIZE_AFFECTOR_H

#include "particleAffector.h"

//! Types of Scaling modes.
enum ScaleMode
{
	S_INTERPOLATE = 0, //! Affect the scale of the particles through interpolation mode.
	S_PULSATE //! Affect the scale of the particles in a pulsate motion.
};

class ScaleAffector : public ParticleAffector
{
private:

	//! Mode of the Scale Affector.
	ScaleMode m_scale_mode = S_INTERPOLATE;
	
	//! Initial size of the object.
	float m_size_start;
	//! Final size of the object.
	float m_size_end;

public:

	// Constructor of Scale Affector.
	ScaleAffector();
	//! Constructor of Scale Affector with scale type, scale start size and scale end size settings.
	ScaleAffector(ScaleMode scaleType, float startSize, float endSize);
	// Destructor of Scale Affector.
	~ScaleAffector();

	void affectParticle(ParticleObject* particle);
	//! Return scale in float which is interpolated between start size and end size over life time of the particle.
	float interpolateScaleOverLife(float startSize, float endSize, float curLifespan, float baseLifespan);
	//! Return scale in float which has the pulsate behavior between minimum and maximum sizes which is represented by m_size_start and m_size_end respectively.
	float pulsateScale(ParticleObject * particle);
};


#endif
