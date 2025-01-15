#include "Token.hpp"
#include "Game/Game.hpp"


Token::Token(Role _role, sf::Vector2f _pos)
{
	role = _role;
	pos = { _pos.x, _pos.y, 0 };

}

Token::Token(const Token& _token)
{
	role = _token.role;
	pos = {_token.pos.x, _token.pos.y, _token.pos.z };
}


Token::Token()
{
	role = NOTHING;
}

void Token::TokenDraw(sf::RenderWindow& _window, sf::Sprite _sprite)
{
	sf::Vector2f posSprite = { GridData::World2Screen(pos.x, pos.y, pos.z)};
	_sprite.setPosition(posSprite);
	_window.draw(_sprite);
}

