#ifndef HITPARTICLE_HPP
#define HITPARTICLE_HPP

#include "Particles.hpp"

class HitParticle : public Particle
{
private:
	int m_damage;
	bool m_dir;

public:
	HitParticle(sf::Vector2f _position, int _damage, bool _dir = true);
	~HitParticle();

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderWindow& _window);

	float GetRenderedY();
	float GetRenderedX();
};

#endif