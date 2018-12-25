#ifndef SQUARE_EMITTER_H
#define SQUARE_EMITTER_H

#include "particleEmitter.h"

class SquareEmitter : public ParticleEmitter
{
private:

	float m_width = 0; // Width of the emitter.
	float m_height = 0; // Height of the emitter.

public:
	// Constructor of Square Emitter
	SquareEmitter();
	//! Constructor of Square Emitter with width, height, velocity (min and max for x and y directions), acceleration (min and max for x and y directions).
	SquareEmitter(float width, float height, 
		float v_min_x, float v_max_x, float v_min_y, float v_max_y,
		float a_min_x, float a_max_x, float a_min_y, float a_max_y);
	// Destructor of Square Emitter
	~SquareEmitter();

	void emitParticle(std::list<ParticleObject*> &particleList, Sprite* sprite, 
		float lifespan, float particleScale_min, float particleScale_max, Vector3 position, float emissionLevel);

};

#endif // !SQUARE_EMITTER_H
