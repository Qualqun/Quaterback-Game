#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Common.hpp"

enum Role
{
	MIDDLE,
	CORNERBACK,
	DEFENSIVE,
	QUARTERBACK,
	NOTHING,
};

class Token
{
private:
	Role role;
	sf::Vector3f pos;

public:
	Token();
	Token(const Token& _token);
	Token(Role _role, sf::Vector2f _pos);
	~Token() {};

	void SetPos(sf::Vector3f _pos) { pos = _pos; }

	void TokenDraw(sf::RenderWindow& _window, sf::Sprite _sprite);
	sf::Vector3f GetPos() { return pos; }
	Role GetRole() { return role; }
};

#endif