#include "particleSystem.h"

ParticleSystem::ParticleSystem()
{
	m_emissionRate = 2.0f;
	m_emissionLevel = 1.0f;
	m_particleCount = 0.0f;
}

ParticleSystem::ParticleSystem(Sprite* sprite, Vector3 position, int particleCount, 
	float particleScale_min, float particleScale_max, float particleLifespan, float emissionRate, float emissionLevel)
{
	m_sprite = sprite;
	m_particleCount = particleCount;
	m_particleScale_min = particleScale_min;
	m_particleScale_max = particleScale_max;
	m_particleLifespan = particleLifespan;
	m_emissionRate = emissionRate;
	m_emissionLevel = emissionLevel;
	m_position = position;
	timer = 0;
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::update(float deltaTime)
{
	//check if it's needed to create a new particle
	if (m_emissionMode == E_OVERTIME)
	{
		timer += deltaTime;
		if (timer > m_emissionRate)
		{
			for (int i = 0; i < m_particleCount; i++)
			{
				
				m_particleEmitter->emitParticle(m_particleList, m_sprite, m_particleLifespan,
					m_particleScale_min, m_particleScale_max, m_position, m_emissionLevel);
				
			}

			timer = 0.0f;
		}
	}
	else if(m_emissionMode == E_BURST)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			
			m_particleEmitter->emitParticle(m_particleList, m_sprite, m_particleLifespan, 
				m_particleScale_min, m_particleScale_max, m_position, m_emissionLevel);
			
		}
		
		m_emissionMode = E_NONE;
	}
	
	
	if (m_particleList.empty() == false)
	{
		for (std::list<ParticleObject* >::iterator i = m_particleList.begin(); i != m_particleList.end(); /**/)
		{
			if ((*i)->lifespan <= 0)
			{
				delete (*i);
				m_particleList.erase(i++);
			}
			else
			{
				for (std::list<ParticleAffector*>::iterator j = m_particleAffectorList.begin(); j != m_particleAffectorList.end(); j++)
				{
					(*j)->affectParticle(*i);
				}

				(*i)->update(deltaTime);
				++i;
			}
		}
	}
}

void ParticleSystem::draw()
{

}

void ParticleSystem::move(Vector3 position)
{
	m_position = m_position + position;
}

void ParticleSystem::rotateAround(Vector3 root, float radius, float deltaTime)
{
	float new_x = radius * cos(deltaTime);
	float new_y = radius * sin(deltaTime);

	SetPosition(Vector3(root.m_x + new_x, root.m_y + new_y, 0));
}

void ParticleSystem::addAffector(ParticleAffector* particleAffecor)
{
	m_particleAffectorList.push_back(particleAffecor);
}

void ParticleSystem::addEmitter(ParticleEmitter * particleEmitter)
{
	m_particleEmitter = particleEmitter;
	//m_particleEmitterList.push_back(particleEmitter);
}

void ParticleSystem::clearAllAffector()
{
	m_particleAffectorList.clear();
}

void ParticleSystem::SetPosition(Vector3 position)
{
	m_position = position;
}

Vector3 ParticleSystem::GetPosition()
{
	return m_position;
}
