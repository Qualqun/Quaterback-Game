#ifndef HUD_HPP
#define HUD_HPP

#include "../Utilities/Utilities.hpp"
#include "../Unit.hpp"
#include "../Translator.hpp"
#include "../TextBox.hpp"
#define TIMING_TURN 1200

#define MIDDLEATTACK 3
#define MIDDLEHP 5
#define DEFENSIVEATTACK 1
#define DEFENSIVEHP 9
#define CORNERBACKATTACK 2
#define CORNERBACKHP 3
#define QUARTERBACKATTACK 5
#define QUARTERBACKHP 9

class Player;
class GameStates;
class CameraData;
struct HudData
{
	sf::Sprite nameBackplate;
	sf::Sprite paBackplate;
	sf::Sprite hudNameBackPlate;
	sf::Sprite unitBackplate;
	sf::Sprite scoreBackplate;
	sf::Sprite cardBackplate;
	sf::Sprite unitFrames[4];
	sf::Sprite unitFramesInfo[4];
	sf::Sprite playerMana[6];
	sf::Sprite playerManaEmpty[6];
	sf::Sprite timerFrames[2];
	sf::Sprite changeTurnOpacity;
	sf::Sprite spriteOverUnit[2];
	sf::Sprite VictorySprite;
	sf::Sprite changeTurnSprite;
	sf::Sprite paPlaceHolder;
	sf::Sprite cardUnitBack;
	sf::Sprite cardUnit[4];
	TextBox textBoxSummary[4];
	TextBox textBoxName[4];
	sf::Text scoreTextPlayer1;
	sf::Text scoreTextPlayer2;
	sf::Text playerName1;
	sf::Text textNumberTurn;
	sf::Text textInfoStatUnit[2];
	sf::Text limitUnitSetUp;
	sf::Text playerName2;
	sf::Font font;
	sf::Text timerText[2];
	std::string stringTextBoxSummary[4];
	std::string stringTextBoxName[4];

	sf::Vector2i tabStats[4];
	Unit unitOver;
	bool changingTurn;
	bool showInfoUnit;
	int scorePlayer[2];
	int overUnit;
	int NumberMaxMana;
	int overUnitTeam;
	int numberTurn;
	int targetUnit;
	bool pauseChangeTurn;
	float timerChangeTurn;
	int NumberPlayerMana;
	float  timeSpendForTurn;
	float spriteX;
	float timeLeftForTurn;
	float moveFramesInfo[4];
	int whichFramesClicked;
	int numberOfUnitAtStart[4];
	sf::Text TextnumberUnitRemained[4];
	sf::Clock timer;



	sf::Text HPOverlay;
	sf::Text AttackOverlay;
};
void changePlayerName(sf::Text& _namePlayer, const char* _char);
void LoadHud(HudData& _hud);
void UpdateHud(HudData& _hud, sf::RenderWindow& _window, float _dt, Player& _playerActive, Player& _playerPassive, CameraData& _cameraData);
void reloadTurn(HudData& _hud, Player& _playerActive, Player& _playerPassive, int _nbTurn);
void SwapPlayerName(sf::Text& _text1, sf::Text& _text2);
void MousePressedHUD(HudData*& _hud, sf::RenderWindow& _window, sf::Event& _event, Player& _playerActive, Player& _playerPassive, sf::Vector2f _camOffset, sf::Vector2f _camScale);
void DrawHud(HudData& _hud, sf::RenderWindow& _window, sf::Vector2f _camOffSet, sf::Vector2f _camScale);
void CleanupHud(HudData& _hud);
float animationChangeTurn(HudData& _hud, sf::Vector2f _camOffset, sf::Vector2f _camScale, sf::RenderWindow& _window, float _X);
bool CheckCollisionMouseSprite(sf::Vector2i _mousePos, sf::Sprite _sprite);
Unit DisplayMonsterInfo(HudData& _hud, sf::Vector2i _mousePos, sf::Vector2f _camOffset, sf::Vector2f _camScale);
bool CheckCollisionMouseSprite(sf::Vector2i _mousePos, sf::Sprite _sprite, sf::Vector2f camOffset, sf::Vector2f camScale);
#endif // !HUD_HPP

