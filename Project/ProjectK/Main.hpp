#ifndef MAIN_H
#define MAIN_H


#include "Common.hpp"
#include "Game/Game.hpp"
#include "Utilities/GameStates.hpp"

struct MainData
{
	sf::RenderWindow* window{ nullptr };
	sf::Event* event{ nullptr };
	sf::Clock* gameClock{ nullptr };
	GameData* game{ nullptr };
	GameStates* gameState{ nullptr };
	MenuData* menuData{ nullptr };
};

void Load(MainData& _main);
void Update(MainData& _main);
void Draw(MainData& _main, sf::RenderWindow& _window);
void Cleanup(MainData& _main);

void PollEvent(MainData& _main);
void KeyPressedMain(MainData& _main);


#endif // !MAIN_H
