#ifndef MENU_HPP
#define MENU_HPP

#include "Common.hpp"
#include "Utilities/Utilities.hpp"
#include "Utilities/GameStates.hpp"
#include "Camera.hpp"
#include "Sound.hpp"

#define OFFSET_SELECTION 5.f
#define SLIDER_SIZE 690.f

enum MenuState
{
	MAIN,
	TUTORIAL,
	CREDIT,
	OPTION
};

enum TutoInfoType
{
	IMANA,
	IDEPLACEMENT,
	ITIME,
	IUNIT,
	IZONE,
	IATTACK,
	ITOTAL
};

enum ButtonType
{
	BPLAY,
	BTUTORIAL,
	BCREDIT,
	BOPTION,
	BQUIT,
	BBACK
};

struct MenuData
{
	sf::Sprite background;
	sf::Sprite titleName;
	sf::Sprite studioLogo;
	sf::Sprite credit;
	sf::Sprite tutorial;
	sf::Sprite soundSliderInfo;
	sf::Sprite soundSlider;
	sf::Sprite soundSliderCursor;
	std::vector<std::pair<sf::Sprite, bool>> button; //Sprite du boutton et condition de séléction

	int state;
};


void InitMenu(MenuData& _menu);
void UpdateMenu(MenuData& _menu);
void DrawMenu(MenuData& _menu, sf::RenderWindow& _window);
void CleanupMenu(MenuData& _menu);

void KeyPressedMenu(MenuData& _menu, sf::RenderWindow& _window, sf::Event& _event, GameStates& _gameState, Sound& _sound);
void MousePressedMenu(MenuData& _menu, sf::RenderWindow& _window, sf::Event& _event, GameStates& _gameState, CameraData& _cameraData, Sound& _sound);
void MouseMovedMenu(MenuData& _menu, sf::RenderWindow& _window, sf::Event& _event, Sound& _sound);

#endif