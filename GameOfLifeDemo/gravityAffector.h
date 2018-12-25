#ifndef GRAVITY_AFFECTOR_H
#define GRAVITY_AFFECTOR_H

#include "particleAffector.h"

//! Types of Gravity modes.
enum GravityMode
{
	G_OVERLIFE = 0, //! Gravity over life mode.
	G_ORBIT, //! Orbit around gravity mode.
};

//! Types of Gravity orbit.
enum GravityOrbitType
{
	G_TYPE_NONE = 0, //! No orbit type.
	G_TYPE_1, //! Orbit type 1, the type which particle attracts to the gravity point and orbit.
	G_TYPE_2 //! Orbit type 2. the type which partcle orbit around the gravity point.
};

class GravityAffector : public ParticleAffector
{
private:

	int m_gravity_dirction_y = -1; //Y direction of the gravity.
	float m_gravity_scale; //Strength of the gravity.
	Vector3 m_gravity_position; //Position of the gravity origin.
	GravityMode m_gravity_mode = G_OVERLIFE; //The mode of the Gravity Affector.
	GravityOrbitType m_gravity_orbit_type = G_TYPE_NONE; //The type of Gravity Orbit the affector uses.

public:
	GravityAffector();
	//! Constructor of Gravity Affector with gravity scale, and gravity direction y settings, the mode of this affector is set as G_OVERLIFE.
	GravityAffector(float gravityScale, int gravityDirection_y);
	//! Constructor of Gravity Affector with gravity scale, gravity point and gravity orbit type settings, the mode of this affector is set as G_ORBIT.
	GravityAffector(float gravityScale, Vector3 gravityPoint, GravityOrbitType gravityOrbitType);
	~GravityAffector();

	void affectParticle(ParticleObject* particle);
	//! Return gravitational acceleration based on the life time of the particle.
	Vector3 gravityOverLife(float curLifespan, float baseLifespan, int gDir);
	//! Return gravitational acceleration around a gravity point.
	Vector3 gravityOrbit(ParticleObject* particle);
	//! Return gravitational attraction point.
	Vector3 gravityAttractor(ParticleObject* particle);
};


#endif