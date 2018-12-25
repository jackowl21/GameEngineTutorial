#ifndef CIRCLE_EMITTER_H
#define CIRCLR_EMITTER_H

#include "particleEmitter.h"


class CircleEmitter : public ParticleEmitter
{
private:
	
	float m_radius = 0; //! Radius of the Circle Emitter.

public:
	//! Constuctor of Circle Emitter.
	CircleEmitter();
	//! Constructor of Circle Emitter with radius, velocity (min & max values for x & y directions), acceleration (min & max values for x & y directions) settings.
	CircleEmitter(float radius, float v_min_x, float v_max_x, float v_min_y, float v_max_y, float a_min_x, float a_max_x, float a_min_y, float a_max_y);
	//! Destructor of Circle Emitter
	~CircleEmitter();

	void emitParticle(std::list<ParticleObject*> &particleList, Sprite* sprite, float lifespan, float particleScale_min, float particleScale_max, Vector3 position, float emissionLevel);
	
};

#endif
