#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Common.hpp"
#include "Game/Grid.hpp"
#include "CardStack.hpp"
#include "Unit.hpp"
#include "Duel.hpp"
#include "Animation.hpp"
#include "Sound.hpp"

struct Limit
{
	int xMin;
	int xMax;
	int yMin;
	int yMax;
};

struct Smoke
{
	Anim anim;
	sf::Vector2f pos;
};

class Player
{
private:

	int mana;
	int score;

	int maxUnit;
	int unitSelect;
	int numberOfUnitAtStart[4];

	CardStack* cardStack;
	std::vector<Token> token;
	std::vector<Unit> unit;

	sf::Sprite spriteSheetTentacles;
	sf::Sprite spriteSheetSmoke;
	Anim animTentacle;

	std::vector<Smoke> smoke;

	bool isApplyingCard = false;
	Card* cardApplying = nullptr;

	// à effacer
	sf::Vector2i unitStats[4];
public:
	sf::Text name;
	Player();
	~Player() {};

	int GetMana() { return mana; }
	int GetUnitSelected() { return unitSelect; }
	int GetNumberOfUnitAtStart(int _nb) { return numberOfUnitAtStart[_nb]; }
	int GetScore() { return score; }
	std::vector<Unit> GetUnit() { return unit; }

	void SetMana(int _nb) { mana = _nb; }
	void SetUnitSelected(int _nb) { unitSelect = _nb; }
	void SetNumberOfUnitAtStart(int _nb) { numberOfUnitAtStart[_nb]--; }
	void SetScore(int _nb) { score = _nb; }

	void MousePressed(int _playerTurn, GridData& _grid, sf::Vector2f _mousePos, Limit _limit, Sound& _sound);
	void Update(float _dt);

	void CreateSmoke(sf::Vector2f& _pos);


	void UsePathing(GridData& _grid, sf::Vector2i _casePos);
	bool DeletUnitAtStart(sf::Vector2i _casePos, GridData& _grid);
	void StartCombat(GridData& _grid, Unit& _enemieUnit, int _iEnemieUnit, Sound& _sound);
	void UnitTakeToken();
	void UnitGoOtherSide(GridData& _grid, Sound& _sound);
	void DrawUnit(sf::RenderWindow& _window, sf::Sprite _unit[5]);

	bool CreateUnit(sf::Vector2i _casePos, GridData& _gridData, int _playerTurn, Limit _limit);

	int SearchUnit(sf::Vector2i _pos);

	void ApplyCard(Card* _card);
	void AppliedCard(bool applied);

	CardStack* GetCardStack() { return cardStack; }
};



#endif