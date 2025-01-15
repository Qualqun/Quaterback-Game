#include "Particles.hpp"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::Update(float _dt)
{
	for (auto& particle : m_particles)
	{
		particle->Update(_dt);
	}

	for (int i = 0; i < m_particles.size(); i++)
	{
		if (m_particles[i]->GetLifeTime() >= m_particles[i]->GetMaxLifeTime())
		{
			delete m_particles[i];
			m_particles.erase(m_particles.begin() + i);
		}
	}
}

void ParticleManager::Draw(sf::RenderWindow& _window)
{
	for (auto& particle : m_particles)
	{
		particle->Draw(_window);
	}
}

void ParticleManager::AddParticle(Particle* _particle)
{
	m_particles.push_back(_particle);
}

Particle::Particle(sf::Vector2f _position, float _maxLifeTime)
{
	m_position = _position;
	m_lifeTime = 0.0f;
	m_maxLifeTime = _maxLifeTime;
}

Particle::~Particle()
{
}

void Particle::Update(float _dt)
{
	m_lifeTime += _dt;
}

void Particle::Draw(sf::RenderWindow& _window)
{
	
}