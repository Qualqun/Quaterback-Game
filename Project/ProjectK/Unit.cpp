#include "Unit.hpp"

Unit::Unit(Role _role, sf::Vector2i _pos, sf::Vector2i _stats, GridData& _grid)
{

	role = _role;
	pos = _pos;
	statsAttHp = _stats;
	token = Token();
	shield = false;
	
	sf::Vector2i screenPos = static_cast<sf::Vector2i>(_grid.World2Screen(_pos.x, _pos.y, 0));

	_grid.SetIsOccupied(_pos.x, _pos.y, true);
}

Unit::Unit(const Unit& _unit, GridData& _grid)
{
	role = _unit.GetRole();
	pos = _unit.GetPos();
	statsAttHp = _unit.GetStats();
	shield = false;
}

void Unit::Move(sf::Vector2i& _newPos, GridData& _grid)
{

	_grid.SetIsOccupied(pos.x, pos.y, false);
	_grid.SetIsOccupied(_newPos.x, _newPos.y, true);
	_grid.SetIsClicked(false);
	pos = _newPos;
}

void Unit::Hurt(int _damage)
{
	if (shield)
	{
		shield = false;
	}
	else
	{
		statsAttHp.y -= _damage;
	}
}