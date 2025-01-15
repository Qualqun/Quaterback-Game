#ifndef WINDPARTICLE_HPP
#define WINDPARTICLE_HPP

#include "Particles.hpp"

class WindParticle : public Particle
{
public:
	WindParticle(sf::Vector2f _position, float _maxLifeTime);
	~WindParticle();

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderWindow& _window);

	float GetRenderedY();
	float GetRenderedX();
};

#endif