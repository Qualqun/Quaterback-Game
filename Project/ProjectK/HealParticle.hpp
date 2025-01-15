#ifndef HEALPARTICLE_HPP
#define HEALPARTICLE_HPP

#include "Particles.hpp"

class HealParticle : public Particle
{
private:
	int m_value;

public:
	HealParticle(sf::Vector2f _position, int _damage);
	~HealParticle();

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderWindow& _window);

	float GetRenderedY();
};

#endif