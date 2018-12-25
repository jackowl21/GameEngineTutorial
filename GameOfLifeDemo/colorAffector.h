#ifndef COLOR_AFFECTOR_H
#define COLOR_AFFECTOR_H

#include "particleAffector.h"

//! Color affector mode types.
enum ColorMode
{
	C_INTERPOLATE = 0, //! Affect the color in interpolation mode.
	C_RANDOM //! Affect the color in random mode.
};

class ColorAffector : public ParticleAffector
{
private:

	ColorMode m_color_mode; // The mode of color affector.

	Color m_color_start; //! Initial color.
	Color m_color_end; //! Final color.

	float m_color_max_r = 1.0f; // Maximum r value.
	float m_color_max_g = 1.0f; // Maximum g value.
	float m_color_max_b = 1.0f; // Maximum b value.

public:

	ColorAffector();
	//! Constructor of Color Affector, this will set the color affector mode to interpolate mode.
	ColorAffector(Color start, Color end);
	//! Constructor of Color Affector, this will set the color affector mode to random mode.
	ColorAffector(float range_r, float range_g, float range_b);
	
	~ColorAffector();

	void affectParticle(ParticleObject* particle);

	//! Interpolate color between two color based on life time of the particle object
	Color interpolateColor(float lifespan, float baseLifeSpan); 
	//! Randomize color based on life time of the particle object.
	Color randomColor(float lifespan, float baseLifespan); 
	//! Interpolate individual value within the color such as r, g, b based on the life time of the particle object.
	float interpolate(float start, float end, float curLife, float baseLife); 
	
};

#endif

