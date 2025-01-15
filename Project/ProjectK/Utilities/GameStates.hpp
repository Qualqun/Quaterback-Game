#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Common.hpp"
#include "Utilities.hpp"
#include <string>

#define NB_STATES 3
class GameStates
{
private:
	std::vector<std::string>* gameState{nullptr};
protected:

public:
	
	sf::Font font;
	sf::Text text;
#pragma region constructors 
	GameStates();
	~GameStates();
#pragma endregion

	void LoadGameStates(void);

#pragma region getters
	std::string GetCurrentState(void) const;
	void DisplayGameStateList(void) const;
#pragma endregion

#pragma region setters
	void SetCurrentState(const std::string& _state);
	void AddState(const std::string& _state);
	void RemoveState(const std::string& _state);
#pragma endregion
};
#endif // !GRID_HPP

