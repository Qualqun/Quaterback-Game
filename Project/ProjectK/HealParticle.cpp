#include "HealParticle.hpp"
#include "FontManager.hpp"

HealParticle::HealParticle(sf::Vector2f _position, int _damage) : Particle(_position, 1.2f), m_value(_damage)
{
}

HealParticle::~HealParticle()
{
}

void HealParticle::Update(float _dt)
{
	Particle::Update(_dt);
}

void HealParticle::Draw(sf::RenderWindow& _window)
{
	Particle::Draw(_window);
	sf::Text text("+" + std::to_string(this->m_value), *FontManager::GetFont("Hyper Super Regular"), 45);

	text.setPosition(m_position.x, this->GetRenderedY());
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);

	_window.draw(text);
}

float HealParticle::GetRenderedY()
{
	return this->m_position.y - this->m_lifeTime * 120;
}