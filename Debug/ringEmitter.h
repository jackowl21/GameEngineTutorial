#ifndef RING_EMITTER_H
#define RING_EMITTER_H

#include "particleEmitter.h"

class RingEmitter : public ParticleEmitter
{
private:

	float m_radius = 10.0f; //! Radius of the emitter.

public:

	RingEmitter();
	//! Constructor of Ring Emitter with radius setting.
	RingEmitter(float radius);
	//! Constructor of Ring Emitter with radius, velocity (minimum and maximum values for x and y directions) and accceleration (minimum and maximum values for x and y directions) settings.
	RingEmitter(float radius, float v_min_x, float v_max_x, float v_min_y, float v_max_y, float a_min_x, float a_max_x, float a_min_y, float a_max_y);
	~RingEmitter();

	void emitParticle(std::list<ParticleObject*> &particleList, Sprite* sprite, float lifespan, float particleScale_min, float particleScale_max, Vector3 position, float emissionLevel);

};
	

#endif // !RING_EMITTER_H

