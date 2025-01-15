#include "Player.hpp"
#include "Game/Game.hpp"

#define NO_UNIT -1

void Player::CreateSmoke(sf::Vector2f& _pos)
{
	smoke.push_back({ InitAnimation(sf::Vector2i(77, 135), 12, 8, 0, false), _pos});
	Animation(spriteSheetSmoke, &smoke[smoke.size() - 1].anim, 0, 0.001);
	spriteSheetSmoke.setOrigin(sf::Vector2f(smoke[smoke.size()- 1].anim.texRect / 2));
}
Player::Player()
{
	cardStack = new CardStack;
	mana = 5;
	maxUnit = 5;
	unitSelect = -1;
	score = 0;
	unitStats[MIDDLE] = { 3,5 };
	unitStats[DEFENSIVE] = { 1,9 };
	unitStats[CORNERBACK] = { 2,3 };
	unitStats[QUARTERBACK] = { 5,9 };
	numberOfUnitAtStart[0] = 6;
	numberOfUnitAtStart[1] = 3;
	numberOfUnitAtStart[2] = 2;
	numberOfUnitAtStart[3] = 1;

	spriteSheetTentacles = LoadSprite("Sprite/Units/HitAnimation.png", false);
	spriteSheetSmoke = LoadSprite("Sprite/Units/SmokeAnimation.png", false);
	animTentacle = InitAnimation(sf::Vector2i(159, 174), 15, 15, 0, false);


	
	Animation(spriteSheetTentacles, &animTentacle, 0, 0.001);
	spriteSheetTentacles.setOrigin(sf::Vector2f(animTentacle.texRect / 2));
}

void Player::MousePressed(int _playerTurn, GridData& _grid, sf::Vector2f _mousePos, Limit _limit, Sound& _sound)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = _mousePos;
		sf::Vector2f worldPos;
		sf::Vector2i casePos;

		worldPos = _grid.Screen2World(mousePos);
		casePos = { (int)worldPos.x,(int)worldPos.y };

		if (_playerTurn <= 0)
		{
			if (DeletUnitAtStart(casePos, _grid))
			{
				return;
			}
		}
		else
		{
			maxUnit = 12;

			_grid.SetIsClicked(false);
			UsePathing(_grid, casePos);
			_grid.MousePressedGrid(casePos);

			int pathSize = _grid.GetOldPath().size();


			if (unitSelect != NO_UNIT && unitSelect != SearchUnit(casePos))
			{
				Player* otherPlayer = GameData::GetInstance()->GetOtherPlayer(this);

				if (SearchUnit(casePos) != NO_UNIT)
				{
					unitSelect = SearchUnit(casePos);
					return;
				}

				if (_grid.IsCellOccupied(casePos.x, casePos.y) == true && mana >= pathSize && otherPlayer->SearchUnit(casePos) != NO_UNIT)
				{
					mana -= pathSize;

					StartCombat(_grid, otherPlayer->unit[otherPlayer->SearchUnit(casePos)], otherPlayer->SearchUnit(casePos), _sound);

					UnitTakeToken();
					UnitGoOtherSide(_grid, _sound);

					return;
				}
				else if (_grid.IsCellOccupied(casePos.x, casePos.y) == false && mana >= pathSize && casePos.x >= 0 && casePos.x < NB_LINE && casePos.y >= 0 && casePos.y < NB_COLUMN)
				{
					smoke.clear();
					for (int i = 0; i < pathSize - 1; i++)
					{
						sf::Vector2f pos = { GridData::World2Screen(_grid.GetOldPath()[i].x,_grid.GetOldPath()[i].y, 0) };
						CreateSmoke(pos);
					}
					mana -= pathSize;
					unit[unitSelect].Move(casePos, _grid);
					unitSelect = NO_UNIT;
					UnitTakeToken();
					UnitGoOtherSide(_grid, _sound);

					return;
				}
			}
		}

		if (this->isApplyingCard)
		{
			int tmpUnitSelect = SearchUnit(casePos);

			if (tmpUnitSelect != NO_UNIT)
			{
				this->cardApplying->OnActive(*this, unit[tmpUnitSelect]);
				this->AppliedCard(true);
			}
		}

		if (SearchUnit(casePos) != NO_UNIT)
		{
			unitSelect = SearchUnit(casePos);
			_sound.UseSound(CASESELECTION);
		}

		if (CreateUnit(casePos, _grid, _playerTurn, _limit))
		{
			return;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->AppliedCard(false);
	}
}

void Player::Update(float _dt)
{
	Animation(spriteSheetTentacles, &animTentacle, 0, _dt);

	for (auto& list : smoke)
	{
		spriteSheetSmoke.setPosition(list.pos);
		Animation(spriteSheetSmoke, &list.anim, 0, _dt);
	}
}

bool Player::DeletUnitAtStart(sf::Vector2i _casePos, GridData& _grid)
{
	if (unitSelect == SearchUnit(_casePos) && SearchUnit(_casePos) != NO_UNIT)
	{
		unit.erase(unit.begin() + unitSelect);
		_grid.SetIsOccupied(_casePos.x, _casePos.y, false);
		unitSelect = NO_UNIT;
		return true;
	}
	return false;
}

int Player::SearchUnit(sf::Vector2i _pos)
{
	for (int i = 0; i < unit.size(); i++)
	{
		if (unit[i].GetPos() == _pos)
		{
			return i;
		}
	}
	return NO_UNIT;
}

void Player::UsePathing(GridData& _grid, sf::Vector2i _casePos)
{
	if (SearchUnit(_casePos) != NO_UNIT)
	{
		_grid.SetIsPathfindingEnabled(true);
		_grid.SetIsClicked(true);

		if (unit[SearchUnit(_casePos)].GetRole() == CORNERBACK)
		{
			_grid.SetPathfindingMethod(true);
		}
		else
		{
			_grid.SetPathfindingMethod(false);
		}
	}
}

void Player::StartCombat(GridData& _grid, Unit& _enemieUnit, int _iEnemieUnit, Sound& _sound)
{
	Player* otherPlayer = GameData::GetInstance()->GetOtherPlayer(this);
	int turn = GameData::GetInstance()->GetTurn();
	int casePathIndice = _grid.GetOldPath().size() - 2;

	if (casePathIndice >= 0)
	{
		unit[unitSelect].Move(_grid.GetOldPath()[casePathIndice], _grid);
	}

	Duel duel(&unit[unitSelect], &_enemieUnit);
	duel.PerformDuel();
	sf::Vector2f pos = { GridData::World2Screen(_enemieUnit.GetPos().x, _enemieUnit.GetPos().y, 0) };
	otherPlayer->spriteSheetTentacles.setPosition(pos);
	otherPlayer->animTentacle.timeAnim = 0;
	_sound.UseSound(UNITATTACK);

	if (unit[unitSelect].GetHp() <= 0)
	{
		otherPlayer->cardStack->AddCardToStack(Card::GetRandomCard());
		_grid.SetIsOccupied(unit[unitSelect].GetPos().x, unit[unitSelect].GetPos().y, false);
		_sound.UseSound(UNITDIE);

		if (turn % 2)
		{
			Token tokenTemp = { unit[unitSelect].GetRole(), sf::Vector2f(rand() % NB_LINE, NB_COLUMN - 1) };
			token.push_back(tokenTemp);
		}
		else
		{
			Token tokenTemp = { unit[unitSelect].GetRole(), sf::Vector2f(rand() % NB_LINE, 0) };
			token.push_back(tokenTemp);
		}

		unit.erase(unit.begin() + unitSelect);
		unitSelect = NO_UNIT;
		otherPlayer->unitSelect = NO_UNIT;
		return;
	}

	if (_enemieUnit.GetHp() <= 0)
	{
		this->cardStack->AddCardToStack(Card::GetRandomCard());
		_grid.SetIsOccupied(_enemieUnit.GetPos().x, _enemieUnit.GetPos().y, false);
		_sound.UseSound(UNITDIE);

		if (turn % 2)
		{
			Token tokenTemp = { _enemieUnit.GetRole(), sf::Vector2f(rand() % NB_LINE, 0) };
			token.push_back(tokenTemp);
		}
		else
		{
			Token tokenTemp = { _enemieUnit.GetRole(), sf::Vector2f(rand() % NB_LINE, NB_COLUMN - 1) };
			token.push_back(tokenTemp);
		}
		otherPlayer->unit.erase(otherPlayer->unit.begin() + _iEnemieUnit);
		unitSelect = NO_UNIT;
		return;
	}

	unitSelect = NO_UNIT;
}

bool Player::CreateUnit(sf::Vector2i _casePos, GridData& _grid, int _playerTurn, Limit _limit)
{
	Role roleSelect = GameData::GetInstance()->GetRoleSelect();

	if (_casePos.x >= _limit.xMin && _casePos.x < _limit.xMax && _casePos.y >= _limit.yMin && _casePos.y < _limit.yMax && mana > 0)
	{
		if (_grid.IsCellOccupied(_casePos.x, _casePos.y) == false && roleSelect != NOTHING)
		{
			if (unit.size() < maxUnit && numberOfUnitAtStart[roleSelect] > 0)
			{
				numberOfUnitAtStart[roleSelect]--;
				mana--;
				unit.push_back(Unit(roleSelect, _casePos, unitStats[roleSelect], _grid));
				return true;
			}
		}
	}
	return false;
}

void Player::DrawUnit(sf::RenderWindow& _window, sf::Sprite _unitSprite[5])
{
	std::sort(unit.begin(), unit.end(), [](Unit& _unit1, Unit& _unit2)
		{
			sf::Vector2f unit1Pos = GridData::World2Screen(_unit1.GetPos().x, _unit1.GetPos().y, 0);
			sf::Vector2f unit2Pos = GridData::World2Screen(_unit2.GetPos().x, _unit2.GetPos().y, 0);
			return unit1Pos.y < unit2Pos.y;
		}
	);

	for (int i = 0; i < unit.size(); i++)
	{
		sf::Vector2f pos = { GridData::World2Screen(unit[i].GetPos().x, unit[i].GetPos().y, 0) };
		_unitSprite[unit[i].GetRole()].setPosition(pos);
		_window.draw(_unitSprite[unit[i].GetRole()]);

		if (unit[i].GetToken().GetRole() != NOTHING)
		{
			unit[i].SetTokenPos(sf::Vector3f(unit[i].GetPos().x, unit[i].GetPos().y, 1.15));
			unit[i].GetToken().TokenDraw(_window, _unitSprite[5]);
		}
	}

	for (int i = 0; i < token.size(); i++)
	{
		token[i].TokenDraw(_window, _unitSprite[4]);
	}

	_window.draw(spriteSheetTentacles);
	for (auto& list : smoke)
	{
		spriteSheetSmoke.setPosition(list.pos);
		_window.draw(spriteSheetSmoke);
	}
	//_window.draw(spriteSheetSmoke);	
}

void Player::UnitTakeToken()
{

	int turn = GameData::GetInstance()->GetTurn();

	if (turn % 2)
	{
		for (int i = 0; i < unit.size(); i++)
		{
			if (unit[i].GetPos().y == 0 && token.size() > 0 && unit[i].GetToken().GetRole() == NOTHING)
			{
				int iToken = rand() % token.size();
				unit[i].SetToken(token[iToken]);
				token.erase(token.begin() + iToken);
			}
		}
	}
	else
	{
		for (int i = 0; i < unit.size(); i++)
		{
			if (unit[i].GetPos().y == NB_COLUMN - 1 && token.size() > 0 && unit[i].GetToken().GetRole() == NOTHING)
			{
				int iToken = rand() % token.size();
				unit[i].SetToken(token[iToken]);
				token.erase(token.begin() + iToken);
				std::cout << unit[i].GetToken().GetRole() << std::endl;

			}
		}
	}

}

void Player::UnitGoOtherSide(GridData& _grid, Sound& _sound)
{
	int turn = GameData::GetInstance()->GetTurn();

	if (turn % 2)
	{
		for (int i = 0; i < unit.size(); i++)
		{
			if (unit[i].GetPos().y == NB_COLUMN - 1)
			{
				if (unit[i].GetToken().GetRole() != NOTHING)
				{
					score++;
					_sound.UseSound(GOALMARKED);
				}

				_grid.SetIsOccupied(unit[i].GetPos().x, unit[i].GetPos().y, false);
				unit.erase(unit.begin() + i);
				unitSelect = NO_UNIT;
			}
		}
	}
	else
	{
		for (int i = 0; i < unit.size(); i++)
		{
			if (unit[i].GetPos().y == 0)
			{
				if (unit[i].GetToken().GetRole() != NOTHING)
				{
					score++;
					_sound.UseSound(GOALMARKED);
				}

				_grid.SetIsOccupied(unit[i].GetPos().x, unit[i].GetPos().y, false);
				unit.erase(unit.begin() + i);
				unitSelect = NO_UNIT;
			}
		}
	}
}

void Player::ApplyCard(Card* _card)
{
	this->isApplyingCard = true;
	this->cardApplying = _card;
}

void Player::AppliedCard(bool applied)
{
	if (applied)
	{
		this->cardStack->RemoveCard(cardApplying);
	}

	isApplyingCard = false;
	cardApplying = nullptr;
}