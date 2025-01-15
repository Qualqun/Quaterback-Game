#include "WindParticle.hpp"
#include "Game/Grid.hpp"

WindParticle::WindParticle(sf::Vector2f _position, float _maxLifeTime) : Particle(_position, _maxLifeTime)
{

}

WindParticle::~WindParticle()
{

}

void WindParticle::Update(float _dt)
{
	Particle::Update(_dt);
}

void WindParticle::Draw(sf::RenderWindow& _window)
{
	Particle::Draw(_window);

	sf::ConvexShape shape;
	shape.setPointCount(4);

	//shape must be a square rotated to look isometric
	shape.setPoint(0, sf::Vector2f(-3, 0));
	shape.setPoint(1, sf::Vector2f(0, -3));
	shape.setPoint(2, sf::Vector2f(3, 0));
	shape.setPoint(3, sf::Vector2f(0, 3));

	shape.setFillColor(sf::Color(255, 255, 255, 175 * (1 - (m_lifeTime / m_maxLifeTime))));
	shape.setPosition(GetRenderedX(), GetRenderedY());

	float scale = (std::sin(m_lifeTime) + 1) / 6 + .2f;
	shape.setScale(scale + .3f, scale + .3f);

	sf::Vector2f pos = GridData::World2Screen(shape.getPosition().x, shape.getPosition().y, 0);
	pos -= sf::Vector2f(OFFSET_X / 2, OFFSET_Y);
	shape.setPosition(pos);
	_window.draw(shape);
}

float WindParticle::GetRenderedY()
{
	return m_position.y + (std::sin(m_lifeTime) - std::sin(m_lifeTime / 4) * 2 + std::sin(m_lifeTime / 8) * 4) / 6;
}

float WindParticle::GetRenderedX()
{
	return m_position.x + m_lifeTime * 1.4f;
}