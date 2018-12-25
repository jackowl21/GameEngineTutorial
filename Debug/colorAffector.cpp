#include "colorAffector.h"

ColorAffector::ColorAffector()
{

}

ColorAffector::ColorAffector(Color start, Color end)
{
	m_color_start = start;
	m_color_end = end;
	m_color_mode = C_INTERPOLATE;
}

ColorAffector::ColorAffector(float range_r, float range_g, float range_b)
{
	m_color_max_r = range_r;
	m_color_max_g = range_g;
	m_color_max_b = range_b;
	m_color_mode = C_RANDOM;
}

ColorAffector::~ColorAffector()
{
}

void ColorAffector::affectParticle(ParticleObject * particle)
{
	if (m_color_mode == C_INTERPOLATE)
	{
		particle->SetParticleColor(interpolateColor(particle->lifespan, particle->baseLifespan));
	}
	else if(m_color_mode == C_RANDOM)
	{
		particle->SetParticleColor(randomColor(particle->lifespan, particle->baseLifespan));
	}
	
}

Color ColorAffector::interpolateColor(float lifespan, float baseLifeSpan)
{
	float r = interpolate(m_color_start.r, m_color_end.r, lifespan, baseLifeSpan);
	float g = interpolate(m_color_start.g, m_color_end.g, lifespan, baseLifeSpan);
	float b = interpolate(m_color_start.b, m_color_end.b, lifespan, baseLifeSpan);
	float a = interpolate(m_color_start.a, 0.0f, lifespan, baseLifeSpan);
	
	return Color(r, g, b, a);
}


Color ColorAffector::randomColor(float lifespan, float baseLifespan)
{
	float r = Random::randf(0.0f, m_color_max_r);
	float g = Random::randf(0.0f, m_color_max_g);
	float b = Random::randf(0.0f, m_color_max_b);

	return Color(r, g, b, 1.0f);
}

float ColorAffector::interpolate(float start, float end, float curLife, float baseLife)
{
	return ((start - end) * curLife / baseLife) + end;
}
