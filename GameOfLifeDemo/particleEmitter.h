#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <iostream>
#include <list>
#include "particleObject.h"
#include "Random.h"


class ParticleEmitter
{
protected:
	

public:

	float m_velocity_min_x = 0.0f; // minimum initial velocity of the particle in x direction.
	float m_velocity_max_x = 0.0f; // maximum initial velocity of the particle in x direction.

	float m_velocity_min_y = 0.0f; // minimum initial velocity of the particle in y direction.
	float m_velocity_max_y = 0.0f; // maximum initial velocity of the particle in y direction.

	float m_acceleration_min_x = 0.0f; // minimum initial acceleration of the particle in x direction.
	float m_acceleration_max_x = 0.0f; // maximum initial acceleration of the particle in x direction.

	float m_acceleration_min_y = 0.0f; // minimum initial acceleration of the particle in y direction.
	float m_acceleration_max_y = 0.0f; // maximum initial acceleration of the particle in y direction.

	Vector3 m_velocity_start; //! Initial velocity of the particle.
	Vector3 m_acceleration_start; //! Initial acceleration of the particle.

	// Constructor of Particle Emitter.
	ParticleEmitter();
	// Destructor of Particle Emitter.
	~ParticleEmitter();

	//! Emit particle.
	virtual void emitParticle(std::list<ParticleObject*> &particleList, Sprite* sprite, float lifespan, float particleScale_min, float particleScale_max, Vector3 position, float emissionLevel) = 0;

	//! Set minimum and maximum values for the particle velocity in both x and y direction.
	void SetVelocity(float v_min_x, float v_max_x, float v_min_y, float v_max_y);
	//! Set minimum and maximum values for the particle acceleration in both x and y direction.
	void SetAcceleration(float a_min_x, float a_max_x, float a_min_y, float a_max_y);
	//! Set the randomized start motion of the particle.
	void SetStartMotion();
	//! Set the randomized scale of the particle.
	float SetStartScale(float scale_min, float scale_max);

};

#endif // !PARTICLE_EMITTER_H
