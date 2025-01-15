#include "DustParticle.hpp"
#include "Game/Grid.hpp"
#include "Game/Game.hpp"

DustParticle::DustParticle(sf::Vector2f _position, float _maxLifeTime, sf::Color _color) : Particle(_position, _maxLifeTime), m_color(_color)
{
	
}

DustParticle::~DustParticle()
{

}

void DustParticle::Update(float _dt)
{
	Particle::Update(_dt);
}

void DustParticle::Draw(sf::RenderWindow& _window)
{
	Particle::Draw(_window);

	sf::ConvexShape shape;
	shape.setPointCount(4);

	//shape must be a square rotated to look isometric
	shape.setPoint(0, sf::Vector2f(-3, 0));
	shape.setPoint(1, sf::Vector2f(0, -3));
	shape.setPoint(2, sf::Vector2f(3, 0));
	shape.setPoint(3, sf::Vector2f(0, 3));

	m_color.a = 175 * (1 - (m_lifeTime / m_maxLifeTime));
	shape.setFillColor(m_color);
	shape.setPosition(GetRenderedX(), GetRenderedY());

	sf::Vector2f pos = GridData::World2Screen(shape.getPosition().x, shape.getPosition().y, m_lifeTime * 2.f);
	shape.setPosition(pos);
	_window.draw(shape);
}

float DustParticle::GetRenderedY()
{
	return m_position.y;
}

float DustParticle::GetRenderedX()
{
	return m_position.x + (std::sin(m_lifeTime) - std::sin(m_lifeTime / 4) * 2 + std::sin(m_lifeTime / 8) * 4) / 6;;
}