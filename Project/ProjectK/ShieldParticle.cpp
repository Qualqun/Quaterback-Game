#include "ShieldParticle.hpp"
#include "Translator.hpp"
#include "FontManager.hpp"

void ShieldParticle::Update(float _dt)
{
	Particle::Update(_dt);
}

void ShieldParticle::Draw(sf::RenderWindow& _window)
{
	Particle::Draw(_window);

	sf::Text apply(Translator::GetTranslation("shield.effect.apply"), *FontManager::GetFont("Hyper Super Regular"), 45);
	apply.setFillColor(sf::Color(51, 153, 255));
	apply.setOutlineColor(sf::Color::Black);
	apply.setOutlineThickness(2);
	apply.setPosition(this->m_position.x, this->m_position.y - 50 * m_lifeTime);
	_window.draw(apply);
}

void BlockedParticle::Update(float _dt)
{
	Particle::Update(_dt);
}

void BlockedParticle::Draw(sf::RenderWindow& _window)
{
	Particle::Draw(_window);

	sf::Text apply(Translator::GetTranslation("shield.effect.blocked"), *FontManager::GetFont("Hyper Super Regular"), 45);
	apply.setFillColor(sf::Color(51, 153, 255));
	apply.setOutlineColor(sf::Color::Black);
	apply.setOutlineThickness(2);
	apply.setPosition(this->m_position.x, this->m_position.y - 50 * m_lifeTime);
	_window.draw(apply);
}