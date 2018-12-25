#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <iostream>
#include <list>

#include "particleObject.h"

#include "colorAffector.h"
#include "scaleAffector.h"
#include "velocityAffector.h"
#include "gravityAffector.h"
#include "rotationAffector.h"

#include "pointEmitter.h"
#include "circleEmitter.h"
#include "ringEmitter.h"
#include "squareEmitter.h"

#include "Vector3.h"
#include "Random.h"

//! Type of emission modes.
enum EmissionMode
{
	E_NONE = 0,
	E_OVERTIME, //! Emit particle overtime mode.
	E_BURST //! Emit particle through a single burst mode.
};

class ParticleSystem
{
private:
	
	float timer; // Emission timer
	float m_emissionRate;  //! the emission rate of the particle system.
	float m_emissionLevel; //! the speed of newly emitted particle.
	 
	float m_particleLifespan;  // Lifespan of the particle objects.
	float m_particleScale_min; //! Minimum scale of the particle objects.
	float m_particleScale_max; //! Maximum scale of the particle objects.

	int m_particleCount; //! the amount of particle spawn in a single frame.

	Vector3 m_position; // Position of the particle system.
	Sprite* m_sprite; // Sprite of the particle objects.
	

public:
	//! A list for storing particle objects.
	std::list<ParticleObject*>m_particleList;
	//! A list for storing particle affectors.
	std::list<ParticleAffector*>m_particleAffectorList;
	//A list for storing particle emitters.
	//std::list<ParticleEmitter*>m_particleEmitterList;

	ParticleEmitter* m_particleEmitter;

	//! Emission mode of the particle system.
	EmissionMode m_emissionMode = E_OVERTIME;

	// Constructor of Particle System.
	ParticleSystem();
	//! Constrcutor of Particle System with sprite, position, particle count, minimum particle scale, maximum particle scale, lifespan of particle, emmission rate and emission level settings.
	ParticleSystem(Sprite* sprite, Vector3 position, int particleCount, 
		float particleScale_min, float particleScale_max, float particleLifespan, float emissionRate, float emissionLevel);
	// Destructor of Particle System.
	~ParticleSystem();

	Random* random;

	// Update the particle system with deltaTime.
	void update(float deltaTime);
	// Draw particle system.
	void draw();
	// Move the particle system.
	void move(Vector3 position);
	//! Rotate the particle system around a origin point. Root is the pivot point of the rotation, radius is the distance between the particle system and the pivot point.
	void rotateAround(Vector3 root, float radius, float deltaTime);

	//! Insert new affector for the particle system.
	void addAffector(ParticleAffector* particleAffecor);
	//! Insert new emitter for the particle system.
	void addEmitter(ParticleEmitter* particleEmitter);
	//! Clear out all the affectors in the affector list.
	void clearAllAffector();

	// Set the position of the particle system.
	void SetPosition(Vector3 position);
	// Return the current position of the particle system.
	Vector3 GetPosition();

};
#endif // !PARTICLE_SYSTEM_H



