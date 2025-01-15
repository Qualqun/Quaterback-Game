#ifndef DUSTPARTICLE_HPP
#define DUSTPARTICLE_HPP

#include "Particles.hpp"

class DustParticle : public Particle
{
public:
	DustParticle(sf::Vector2f _position, float _maxLifeTime, sf::Color _color);
	~DustParticle();

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderWindow& _window);

	float GetRenderedY();
	float GetRenderedX();

private:
	sf::Color m_color;
};

#endif