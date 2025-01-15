#ifndef SHIELD_PARTICLE_HPP
#define SHIELD_PARTICLE_HPP

#include "Particles.hpp"

class ShieldParticle : public Particle
{
public:
	ShieldParticle(sf::Vector2f _position) : Particle(_position, 1.2f) { }
	~ShieldParticle() { }

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderWindow& _window);
};

class BlockedParticle : public Particle
{
public:
	BlockedParticle(sf::Vector2f _position) : Particle(_position, 1.2f) { }
	~BlockedParticle() { }

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderWindow& _window);
};

#endif