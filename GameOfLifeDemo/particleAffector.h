#ifndef PARTICLE_AFFECTOR_H
#define PARTICLE_AFFECTOR_H

#include "particleObject.h"
#include "Random.h"

class ParticleAffector
{
protected:
public:

	ParticleAffector();
	~ParticleAffector();

	//! Affect the behavior of the particle.
	virtual void affectParticle(ParticleObject* particle) = 0;
};

#endif
