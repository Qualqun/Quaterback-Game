#ifndef UNIT_HPP
#define UNIT_HPP

#include "Common.hpp"
#include "Game/Grid.hpp"
#include "Token.hpp"
#include "CardStack.hpp"



class Unit
{
private:
	Role role;
	sf::Vector2i pos;
	sf::Vector2i statsAttHp;
	Token token;

	bool shield;

public:

	Unit() { ; }
	Unit(Role, sf::Vector2i, sf::Vector2i, GridData& _grid);
	Unit(const Unit&, GridData& _grid); //copiteur construct

	void Hurt(int _damage);
	void Heal(int _heal) { statsAttHp.y += _heal; }
	Role GetRole() const { return role; }
	sf::Vector2i GetStats() const { return statsAttHp; }
	sf::Vector2i GetPos() const { return pos; }
	inline int GetHp() { return statsAttHp.y; }
	inline int GetAtk() { return statsAttHp.x; }
	Token GetToken() {return token;}
	void AddShield() { shield = true; }
	bool HasShield() { return shield; }

	void SetRole(Role _role) { role = _role; }
	void SetTokenPos(sf::Vector3f _pos) { token.SetPos(_pos); }
	void SetToken(Token _token) { token = _token; }

	void Move(sf::Vector2i& _pos, GridData& _grid);

};



#endif