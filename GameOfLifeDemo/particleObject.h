#ifndef PARTICLE_OBJECT_H
#define PARTICLE_OBJECT_H

#include "gameobject.h"

class ParticleObject : public GameObject
{
private:

public:
	
	float lifespan; // Lifespan of the gameobject.
	float baseLifespan; // The base lifespan of the gameobject

	float p_rotation; // Rotation of the particle object.
	float p_gravity; // Gravity of the particle object.
	float p_scale_start; // Initial scale of the particle object.

	Vector3 p_acceleration; // Acceleration on the particle object.
	

	ParticleObject();
	//! Constructor fo Particle Object with sprite, lifespan, scale, position, velocity and acceleration settings.
	ParticleObject(Sprite* sprite, float life, float scale,Vector3 pos, Vector3 velocity, Vector3 acceleration);
	~ParticleObject();

	void update(float deltaTime);

	void SetParticleColor(const Color& color); // Set the color of the particle object.
	void SetParticleSize(float size); // Set the scale of the particle object.
	void SetParticleMotion(); //! Set the motion of particle object which is the sum of velocity and acceleration.
	void SetParticleVelocity(Vector3 velocity); // Set the velocity of particle object.
	void SetParticleRotation(float rotation); // Set the rotation of particle object.

	Vector3 GetParticlePos(); // Return the position of the particle object.
	Vector3 GetParticleVelocity(); // Return the velocity of the particle object.
	float GetParticleRotation(); // Return the rotation of the particle object.

};

#endif
