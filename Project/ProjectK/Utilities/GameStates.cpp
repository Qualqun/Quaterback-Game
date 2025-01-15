#include "GameStates.hpp"

void GameStates::LoadGameStates(void)
{

	//Add Base list of State
	const char* stateList[NB_STATES] =
	{
		"MENU",
		"GAME",
		"PAUSE"
	};

	//Push them into the vector of gameState
	for (auto stateID = 0; stateID < NB_STATES; stateID++)
	{
		gameState->push_back(stateList[stateID]);
	}


	//Temp to load and init gameState text
	font.loadFromFile("assets/fonts/StateFont.ttf");
	auto initializeText = [&](sf::Text& _text, int _characterSize, const sf::Color& _color, const sf::Vector2f& _position, const std::string& _string = "")
	{
		_text.setFont(font);
		_text.setCharacterSize(_characterSize);
		_text.setFillColor(_color);
		_text.setPosition(_position);
		_text.setString(_string);
	};

	initializeText(text, 50, sf::Color::Yellow, sf::Vector2f(SCREEN_WIDTH/2.f - 50.f, 0.f), gameState->front());
}
std::string GameStates::GetCurrentState(void) const
{
	//Return first index of gameState <-- currentGameState
	return gameState->front();
}
void GameStates::DisplayGameStateList(void) const
{
	for (const auto& list : *gameState)
	{
		std::cout << list << std::endl;
	}
}
void GameStates::SetCurrentState(const std::string& _state)
{
	std::vector<std::string>::iterator itr;
	//find _state in arugement trough the gameState vector and assign it to itr
	itr = std::find(gameState->begin(), gameState->end(), _state);

	if (itr != gameState->end())
	{
		//swap value to put _state at the beginning of the vector
		std::swap(gameState->front(), *itr);
	}
}
void GameStates::AddState(const std::string& _state)
{
	//Add State into the vector
	gameState->push_back(_state);
}
void GameStates::RemoveState(const std::string& _state)
{
	std::vector<std::string>::iterator itr;
	//find _state in arugement trough the gameState vector and assign it to itr
	itr = std::find(gameState->begin(), gameState->end(), _state);

	if (itr != gameState->end())
	{
		//remove from vector
		std::cout << "Size before ERASE :" << sizeof(gameState) + gameState->capacity() * sizeof(int) << std::endl;
		gameState->erase(itr);
		std::cout << "Size after ERASE :" << sizeof(gameState) + gameState->capacity() * sizeof(int) << std::endl;
		gameState->shrink_to_fit();
		std::cout << "Size after SHRINK :" << sizeof(gameState) + gameState->capacity() * sizeof(int) << std::endl;

	}
}
#pragma region constructors
GameStates::GameStates()
	: gameState{ nullptr }
{
	gameState = new std::vector<std::string>;
	std::cout << "\033[6;1;31mDefault\033[0m constructor for GameStates called !!" << std::endl;
}
GameStates::~GameStates()
{
	if (gameState != nullptr)
	{
		delete gameState;
		gameState = nullptr;
	}

	std::cout << "\033[6;1;34mDeconstructor\033[0m for GameStates called !!" << std::endl;
}
#pragma endregion