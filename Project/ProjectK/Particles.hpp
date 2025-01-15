#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include <vector>
#include "Common.hpp"

class Particle
{
protected:
	sf::Vector2f m_position;
	float m_lifeTime;
	float m_maxLifeTime;

public:
	Particle(sf::Vector2f _position, float _maxLifeTime);
	~Particle();

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderWindow& _window);

	float GetLifeTime() { return m_lifeTime; }
	float GetMaxLifeTime() { return m_maxLifeTime; }
};

class ParticleManager
{
private:
	std::vector<Particle*> m_particles;

public:
	ParticleManager();
	~ParticleManager();

	void Update(float _dt);
	void Draw(sf::RenderWindow& _window);

	void AddParticle(Particle* _particle);
};

#endif