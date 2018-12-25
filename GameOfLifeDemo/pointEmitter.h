#ifndef POINT_EMITTER_H
#define POINT_EMITTER_H

#include "particleEmitter.h"

class PointEmitter : public ParticleEmitter
{
private:


public:

	PointEmitter();
	//! Constructor of Point Emitter with velocity (minimum and maximum for x and y directions) and acceleration (minimum and maximum for x and y directions).
	PointEmitter(float v_min_x, float v_max_x, float v_min_y, float v_max_y, float a_min_x, float a_max_x, float a_min_y, float a_max_y);
	~PointEmitter();

	void emitParticle(std::list<ParticleObject*> &particleList, Sprite* sprite, float lifespan, float particleScale_min, float particleScale_max, Vector3 position, float emissionLevel);

};

#endif