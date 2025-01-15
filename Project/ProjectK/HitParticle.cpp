#include "HitParticle.hpp"
#include "FontManager.hpp"

#define CLIMBUP 0.5f

HitParticle::HitParticle(sf::Vector2f _position, int _damage, bool _dir) : Particle(_position, 1.2f), m_damage(_damage), m_dir(_dir)
{
}

HitParticle::~HitParticle()
{
}

void HitParticle::Update(float _dt)
{
	Particle::Update(_dt);
}

void HitParticle::Draw(sf::RenderWindow& _window)
{
	Particle::Draw(_window);
	sf::Text text("-" + std::to_string(this->m_damage), *FontManager::GetFont("Hyper Super Regular"), 45);

	text.setPosition(this->GetRenderedX(), this->GetRenderedY());
	text.setFillColor(sf::Color::Red);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);

	_window.draw(text);
}

float HitParticle::GetRenderedY()
{
	float deltaY = ((this->m_lifeTime - CLIMBUP) * (this->m_lifeTime - CLIMBUP)) * 120;
	return this->m_position.y + deltaY;
}

float HitParticle::GetRenderedX()
{
	float deltaX = (std::log10(1 + this->m_lifeTime * 100)) * 30;
	return m_position.x + (m_dir ? deltaX : -deltaX);
}