#include "HUD.hpp"
#include "Game.hpp"
#include "Grid.hpp"
#include "../Camera.hpp"
#include "../Unit.hpp"
#include "../Utilities/GameStates.hpp"
void LoadHud(HudData& _hud)
{
	_hud.nameBackplate = LoadSprite("Sprite/Hud/RectangleName.png", false);
	_hud.paBackplate = LoadSprite("Sprite/Hud/RectanglePA.png", false);
	_hud.unitBackplate = LoadSprite("Sprite/Hud/RectangleUnit.png", false);
	_hud.scoreBackplate = LoadSprite("Sprite/Hud/RectangleScore.png", false);
	_hud.unitFrames[NORMAL] = LoadSprite("Sprite/Hud/UnitInfo/unitFramesNormal.png", false);
	_hud.unitFrames[TANK] = LoadSprite("Sprite/Hud/UnitInfo/unitFramesTank.png", false);
	_hud.unitFrames[AILLIER] = LoadSprite("Sprite/Hud/UnitInfo/unitFramesWinger.png", false);
	_hud.unitFrames[QUATTERBACK] = LoadSprite("Sprite/Hud/UnitInfo/unitFramesQuatterback.png", false);
	_hud.changeTurnSprite = LoadSprite("Sprite/Hud/NextPlayerTurn.png", false);
	_hud.paPlaceHolder = LoadSprite("Sprite/Hud/branche.png", false);
	_hud.unitFramesInfo[NORMAL] = LoadSprite("Sprite/Hud/RectangleUnitInfo.png", false);
	_hud.unitFramesInfo[TANK] = LoadSprite("Sprite/Hud/RectangleUnitInfo.png", false);
	_hud.unitFramesInfo[AILLIER] = LoadSprite("Sprite/Hud/RectangleUnitInfo.png", false);
	_hud.unitFramesInfo[QUATTERBACK] = LoadSprite("Sprite/Hud/RectangleUnitInfo.png", false);
	_hud.timerFrames[BACK] = LoadSprite("Sprite/Hud/timerBack.png", false);
	_hud.timerFrames[FRONT] = LoadSprite("Sprite/Hud/timerFront.png", false);
	_hud.spriteOverUnit[0] = LoadSprite("Sprite/Hud/card_player_allie.png", false);
	_hud.spriteOverUnit[1] = LoadSprite("Sprite/Hud/card_player_enemi.png", false);
	_hud.textNumberTurn;
	_hud.textBoxName;

	//"unit.regular.name": "Regular",
	//	"unit.regular.summary" : "Just a normal zombie.",
	//	"unit.winger.name" : "winger",
	//	"unit.winger.summary" : " Once per turn : you can move two cell for 1 mana.",
	//	"unit.tank.name" : "Tank",
	//	"unit.tank.summary" : "Inflict 1 damage whenever this unit take damage.",
	//	"unit.boss.name" : "Boss",
	//	"unit.boss.summary" : "The best"

	_hud.stringTextBoxSummary[0] = "unit.regular.summary";
	_hud.stringTextBoxSummary[1] = "unit.winger.summary";
	_hud.stringTextBoxSummary[2] = "unit.tank.summary";
	_hud.stringTextBoxSummary[3] = "unit.boss.summary";
	_hud.stringTextBoxName[0] = "unit.regular.name";
	_hud.stringTextBoxName[1] = "unit.winger.name";
	_hud.stringTextBoxName[2] = "unit.tank.name";
	_hud.stringTextBoxName[3] = "unit.boss.name";
	_hud.showInfoUnit = true;
	_hud.changeTurnOpacity = LoadSprite("Sprite/Hud/changeTurnOpacity.png", false);
	_hud.numberTurn = -1;
	_hud.VictorySprite = LoadSprite("Sprite/Hud/Victory.png", false);
	_hud.tabStats[0].x = MIDDLEATTACK;
	_hud.tabStats[0].y = MIDDLEHP;
	_hud.tabStats[1].x = CORNERBACKATTACK;
	_hud.tabStats[1].y = CORNERBACKHP;
	_hud.tabStats[2].x = DEFENSIVEATTACK;
	_hud.tabStats[2].y = DEFENSIVEHP;
	_hud.tabStats[3].x = QUARTERBACKATTACK;
	_hud.tabStats[3].y = QUARTERBACKHP;
	_hud.cardUnitBack = LoadSprite("Sprite/Hud/UnitInfo/card_player.png", false);
	_hud.cardUnit[NORMAL] = LoadSprite("Sprite/Hud/UnitInfo/card_normal.png", false);
	_hud.cardUnit[AILLIER] = LoadSprite("Sprite/Hud/UnitInfo/card_winger.png", false);
	_hud.cardUnit[TANK] = LoadSprite("Sprite/Hud/UnitInfo/card_tank.png", false);
	_hud.cardUnit[QUATTERBACK] = LoadSprite("Sprite/Hud/UnitInfo/card_boss.png", false);
	_hud.hudNameBackPlate = LoadSprite("Sprite/Hud/score.png", false);


	_hud.timer.restart();
	_hud.NumberPlayerMana = 3;
	_hud.targetUnit = 6;
	_hud.NumberMaxMana = 5;
	_hud.scorePlayer[0] = 0;
	_hud.scorePlayer[1] = 0;
	_hud.pauseChangeTurn = false;
	_hud.timerChangeTurn = 0;
	_hud.numberOfUnitAtStart[0] = 6;
	_hud.numberOfUnitAtStart[1] = 3;
	_hud.numberOfUnitAtStart[2] = 2;
	_hud.numberOfUnitAtStart[3] = 1;
	_hud.timeSpendForTurn = 1200;
	_hud.spriteX = -800;
	_hud.timeLeftForTurn;
	_hud.changingTurn = false;
	for (int i = 0; i < NUMBER_UNITS; i++)
	{
		_hud.TextnumberUnitRemained[i].setFont(_hud.font);
		_hud.TextnumberUnitRemained[i].setCharacterSize(20);
		_hud.TextnumberUnitRemained[i].setFillColor(sf::Color::Red);
		_hud.TextnumberUnitRemained[i].setPosition(55 + (float(i) * float(52)), 890);
	}


	auto initializeText = [&](sf::Text& _text, int _characterSize, const sf::Color& _color, const sf::Vector2f& _position, float _angle = 0, const std::string& _string = "")
	{
		_text.setFont(_hud.font);
		_text.setCharacterSize(_characterSize);
		_text.setFillColor(_color);
		_text.setPosition(_position);
		_text.setString(_string);
		_text.setRotation(_angle);
	};

	auto initializeTextBox = [&](TextBox& _textBox, int _characterSize, const sf::Color& _color, const sf::Vector2f& _position, float _angle = 0, std::string _key = "")
	{
		_textBox = TextBox(Translator::GetTranslation(_key), sf::IntRect(0, 0, _position.x, _position.y), _characterSize);
		_textBox.SetFont(&_hud.font);
		_textBox.SetColor(_color);
		_textBox.SplitTextIntoLines();

		//_text.setFont(_hud.font);
		//_text.setCharacterSize(_characterSize);
		//_text.setFillColor(_color);
		//_text.setPosition(_position);
		//_text.setString(_string);
		//_text.setRotation(_angle);
	};

	initializeText(_hud.textNumberTurn, 60, sf::Color::White, sf::Vector2f(50, 50));
	for (int i = 0; i < 4; i++)
	{
		initializeTextBox(_hud.textBoxSummary[i], 20, sf::Color::Cyan, sf::Vector2f(200, 150), 0, _hud.stringTextBoxSummary[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		initializeTextBox(_hud.textBoxName[i], 40, sf::Color::Cyan, sf::Vector2f(300, 150), 0, _hud.stringTextBoxName[i]);
	}

	initializeText(_hud.textNumberTurn, 60, sf::Color::White, sf::Vector2f(50, 50));
	initializeText(_hud.timerText[MINUTES], 60, sf::Color::White, sf::Vector2f(1750, 44), 6);
	initializeText(_hud.scoreTextPlayer1, 100, sf::Color::White, sf::Vector2f(800, 0));
	initializeText(_hud.scoreTextPlayer2, 100, sf::Color::White, sf::Vector2f(1050, 0));
	initializeText(_hud.playerName1, 100, sf::Color::White, sf::Vector2f(700 - (40 * static_cast<int>(_hud.playerName1.getString().getSize())), 0));
	initializeText(_hud.playerName2, 100, sf::Color::White, sf::Vector2f(1200, 0));
	initializeText(_hud.textInfoStatUnit[0], 50, sf::Color::White, sf::Vector2f(1700, 200));
	initializeText(_hud.textInfoStatUnit[1], 50, sf::Color::White, sf::Vector2f(1750, 200));
	initializeText(_hud.limitUnitSetUp, 60, sf::Color::White, sf::Vector2f(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100));


	initializeText(_hud.HPOverlay, 40, sf::Color::Green, sf::Vector2f(50, 50));
	initializeText(_hud.AttackOverlay, 40, sf::Color::Red, sf::Vector2f(150, 50));

	_hud.font.loadFromFile("assets/fonts/HyperSuperRegular.ttf");
	_hud.scoreTextPlayer2.setFont(_hud.font);
	_hud.playerName1.setFont(_hud.font);
	_hud.playerName2.setFont(_hud.font);

	_hud.playerMana[0] = LoadSprite("Sprite/Hud/on/paon1.png", false);
	_hud.playerManaEmpty[0] = LoadSprite("Sprite/Hud/Off/paoff1.png", false);
	_hud.playerMana[1] = LoadSprite("Sprite/Hud/on/paon2.png", false);
	_hud.playerManaEmpty[1] = LoadSprite("Sprite/Hud/Off/paoff2.png", false);
	_hud.playerMana[2] = LoadSprite("Sprite/Hud/on/paon3.png", false);
	_hud.playerManaEmpty[2] = LoadSprite("Sprite/Hud/Off/paoff3.png", false);
	_hud.playerMana[3] = LoadSprite("Sprite/Hud/on/paon4.png", false);
	_hud.playerManaEmpty[3] = LoadSprite("Sprite/Hud/Off/paoff4.png", false);
	_hud.playerMana[4] = LoadSprite("Sprite/Hud/on/paon5.png", false);
	_hud.playerManaEmpty[4] = LoadSprite("Sprite/Hud/Off/paoff5.png", false);
	_hud.playerMana[5] = LoadSprite("Sprite/Hud/on/paon6.png", false);
	_hud.playerManaEmpty[5] = LoadSprite("Sprite/Hud/Off/paoff6.png", false);

	_hud.unitFramesInfo[0].setColor(sf::Color::Red);
	_hud.unitFramesInfo[1].setColor(sf::Color::Blue);
	_hud.unitFramesInfo[2].setColor(sf::Color::Yellow);
	_hud.unitFramesInfo[3].setColor(sf::Color::Magenta);
	for (int i = 0; i < 5; i++)
	{
		_hud.unitFrames[i].setPosition(sf::Vector2f{ (40 + (float(i) * float(50))), 835 });
	}
	changePlayerName(_hud.playerName1, "Leo");


	_hud.playerName1.setCharacterSize(100);
	_hud.playerName1.setFillColor(sf::Color::Blue);
	_hud.playerName1.setPosition(700 - (40 * static_cast<int>(_hud.playerName1.getString().getSize())), 0);
	changePlayerName(_hud.playerName2, "Swann");
	_hud.playerName2.setCharacterSize(100);
	_hud.playerName2.setFillColor(sf::Color::Red);
	_hud.playerName2.setPosition(1200, 0);
	_hud.playerName2.setStyle(sf::Text::Underlined);

}
void reloadTurn(HudData& _hud, Player& _playerActive, Player& _playerPassive, int _nbTurn)
{
	if (_nbTurn % 2 == 0)
	{

		_hud.playerName1.setStyle(sf::Text::Underlined);
		_hud.playerName2.setStyle(sf::Text::Regular);
	}
	else
	{
		_hud.playerName1.setStyle(sf::Text::Regular);
		_hud.playerName2.setStyle(sf::Text::Underlined);
		_hud.playerName2.setStyle(sf::Text::Underlined);
	}
	_hud.timeSpendForTurn = 1200;
	_hud.playerName1.setPosition(700 - (40 * static_cast<int>(_hud.playerName1.getString().getSize())), 0);
	_hud.numberTurn = _nbTurn;
	_hud.spriteX = -800;
	_hud.pauseChangeTurn = false;
	_hud.timerChangeTurn = 0;
	_hud.changingTurn = true;
	}
	void SwapPlayerName(sf::Text & _text1, sf::Text & _text2)
	{
		//sf::Text tempName = _text1;
		//_text1 = _text2;
		//_text2 = tempName;
	}
	float animationChangeTurn(HudData & _hud, sf::Vector2f _camOffset, sf::Vector2f _camScale, sf::RenderWindow & _window, float _X = 0)
	{
		sf::Vector2f posTurnSprite = { _X ,SCREEN_HEIGHT / 3 };
		BlitSprite(_hud.changeTurnOpacity, sf::Vector2f{ 0, 0 } + _camOffset, 0, _window, _camScale);
		if (_hud.pauseChangeTurn != true)
		{
			posTurnSprite.x += 80;

			if (posTurnSprite.x >= SCREEN_WIDTH / 3 && _hud.timerChangeTurn < 2.5)
			{
				_hud.pauseChangeTurn = true;
			}
		}
		else
		{
			if (_hud.timerChangeTurn <= 3)
			{
				_hud.timerChangeTurn += 0.140;
				std::cout << _hud.timerChangeTurn << std::endl;
			}
			else
			{
				_hud.pauseChangeTurn = false;

			}
		}
		if (posTurnSprite.x >= SCREEN_WIDTH)
		{
			_hud.changingTurn = false;
		}
		return posTurnSprite.x;
	}
	void changePlayerName(sf::Text & _namePlayer, const char* _char)
	{
		_namePlayer.setString(_char);
	}
	void SetManaPlayer(HudData & _hud, int _number)
	{
		_hud.NumberPlayerMana += _number;
	}
	void UpdateHud(HudData & _hud, sf::RenderWindow & _window, float _dt, Player & _playerActive, Player & _playerPassive, CameraData & _cameraData)
	{

		sf::Vector2f camCenter = _cameraData.GetCamera().getCenter();
		sf::Vector2f camSize = _cameraData.GetCamera().getSize();
		sf::Vector2f camOffset = camCenter - sf::Vector2f{ camSize.x / 2, camSize.y / 2 };
		sf::Vector2f camScale = { camSize.x / SCREEN_WIDTH , camSize.y / SCREEN_HEIGHT };

		for (int i = 0; i < 4; i++)
		{
			_hud.numberOfUnitAtStart[i] = _playerActive.GetNumberOfUnitAtStart(i);
		}
		_hud.timeSpendForTurn -= _dt;

		if ((int)_hud.timeSpendForTurn % 60 < 10)
		{
			_hud.timerText[MINUTES].setString(std::to_string(static_cast<int>(_hud.timeSpendForTurn / 60)) + ":0" + std::to_string(static_cast<int>((int)_hud.timeSpendForTurn % 60)));
		}
		else
		{
			_hud.timerText[MINUTES].setString(std::to_string(static_cast<int>(_hud.timeSpendForTurn / 60)) + ":" + std::to_string(static_cast<int>((int)_hud.timeSpendForTurn % 60)));
		}
		//Changer le getPosition pour qu'il soit relatif à la window plutôt que le desktop
		for (int i = 0; i < NUMBER_UNITS; i++)
		{
			if (CheckCollisionMouseSprite(sf::Mouse::getPosition(_window), _hud.unitFrames[i], camOffset, camScale))
			{
				if (_hud.numberOfUnitAtStart[i] != 0)
				{

					for (int j = 0; j < 4; j++)
					{
						if (i != j)
						{
							_hud.moveFramesInfo[j] = 0;
						}
					}
				}
			}
			if (_playerActive.GetUnitSelected() == i && _hud.moveFramesInfo[i] <= 130)
			{
				_hud.moveFramesInfo[i] += 6;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && _playerActive.GetMana() < 5)
		{
			_playerActive.SetMana(_playerActive.GetMana() + 1);

		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && _playerActive.GetMana() > 0))
		{
			_playerActive.SetMana(_playerActive.GetMana() - 1);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			_playerActive.SetScore(_playerActive.GetScore() + 1);

			_hud.scorePlayer[0]++;
		}
		_hud.scoreTextPlayer1.setString(std::to_string(_playerActive.GetScore()));
		_hud.scoreTextPlayer2.setString(std::to_string(_playerPassive.GetScore()));

		std::string numberTurn = std::to_string(_hud.numberTurn);
		_hud.textNumberTurn.setString(("Turn : " + numberTurn));
		for (int i = 0; i < 4; i++)
		{
			std::string stringOfScore = std::to_string(_playerActive.GetNumberOfUnitAtStart(i));
			_hud.TextnumberUnitRemained[i].setString("x" + stringOfScore);
		}
		_hud.timer.restart();
		_hud.NumberPlayerMana = _playerActive.GetMana();
		_hud.overUnit = 6;
		for (int i = 0; i < 4; i++)
		{
			if (CheckCollisionMouseSprite(sf::Mouse::getPosition(_window), _hud.unitFrames[i], camOffset, camScale))
			{
				_hud.overUnit = i;
			}
		}
		_hud.unitOver = DisplayMonsterInfo(_hud, sf::Mouse::getPosition(_window), camOffset, camScale);
	}

	Unit DisplayMonsterInfo(HudData & _hud, sf::Vector2i _mousePos, sf::Vector2f _camOffset, sf::Vector2f _camScale)
	{
		Player playerTemp1 = *GameData::GetInstance()->GetPlayer1();
		Player playerTemp2 = *GameData::GetInstance()->GetPlayer2();
		sf::Vector2f mousePos = sf::Vector2f{ _mousePos.x * _camScale.x , _mousePos.y * _camScale.y } + _camOffset;
		sf::Vector2f worldPos;
		sf::Vector2i casePos;
		worldPos = GameData::GetInstance()->GetGridData()->Screen2World(mousePos);
		casePos = { (int)worldPos.x ,(int)worldPos.y };

		for (int i = 0; i < playerTemp1.GetUnit().size(); i++)
		{
			if (playerTemp1.SearchUnit(casePos) != -1)
			{
				Unit tempUnit;
				int iUnit = playerTemp1.SearchUnit(casePos);
				_hud.overUnitTeam = 1;
				playerTemp1.GetUnit()[iUnit].GetPos();
				tempUnit = playerTemp1.GetUnit()[iUnit];
				return tempUnit;
			}
		}
		for (int i = 0; i < playerTemp2.GetUnit().size(); i++)
		{
			if (playerTemp2.SearchUnit(casePos) != -1)
			{
				Unit tempUnit;

				int iUnit = playerTemp2.SearchUnit(casePos);
				_hud.overUnitTeam = 2;
				playerTemp2.GetUnit()[iUnit].GetPos();
				tempUnit = playerTemp2.GetUnit()[iUnit];
				return tempUnit;
			}
		}
		_hud.unitOver.SetRole(NOTHING);
		Unit tempUnit;
		tempUnit.SetRole(NOTHING);
		_hud.overUnitTeam = NULL;
		return tempUnit;
	}
	void PlayerUsedMana(HudData & _hud)
	{

	}
	void MousePressedHUD(HudData * &_hud, sf::RenderWindow & _window, sf::Event & _event, Player & _playerActive, Player & _playerPassive, sf::Vector2f _camOffset, sf::Vector2f _camScale)
	{
		for (int i = 0; i < NUMBER_UNITS; i++)
		{
			if (CheckCollisionMouseSprite(sf::Mouse::getPosition(_window), _hud->unitFrames[i], _camOffset, _camScale))
			{

				for (int j = 0; j < 4; j++)
				{
					if (i != j)
					{
						_hud->moveFramesInfo[j] = 0;
					}
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _hud->targetUnit == 6 && _hud->numberOfUnitAtStart[i] != 0)
				{
					GameData::GetInstance()->SetRole((Role)i);
					_hud->targetUnit = i;

				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && _hud->targetUnit != 6 && i == _hud->targetUnit)
				{

					GameData::GetInstance()->SetRole(NOTHING);
					_hud->targetUnit = 6;
				}
			}
			if (_hud->targetUnit == i && _hud->moveFramesInfo[i] <= 130)
			{
				_hud->moveFramesInfo[i] += 6;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			_hud->scorePlayer[0]++;
			_playerActive.SetScore(_playerActive.GetScore() + 1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt))
		{
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			_hud->scorePlayer[1]++;
			_playerActive.SetScore(_playerPassive.GetScore() + 1);
		}
	}
	void DrawHud(HudData & _hud, sf::RenderWindow & _window, sf::Vector2f camOffSet, sf::Vector2f camScale)
	{

		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		for (int i = 0; i < 4; i++)
		{
			if (_hud.whichFramesClicked == i)
			{
				BlitSprite(_hud.unitFramesInfo[i], sf::Vector2f{ 10, 835 - _hud.moveFramesInfo[i] } + camOffSet, 0, _window, camScale);
			}
		}
		BlitSprite(_hud.paPlaceHolder, sf::Vector2f{ 0, 0 } + camOffSet, 0, _window, camScale);
		BlitSprite(_hud.hudNameBackPlate, sf::Vector2f{ 0, 0 } + camOffSet, 0, _window, camScale);
		for (int i = 0; i < _hud.NumberMaxMana; i++)
		{
			if (i < _hud.NumberPlayerMana)
			{
				BlitSprite(_hud.playerMana[i], sf::Vector2f{ 0, 0 } + camOffSet, 0, _window, camScale);
			}
			else if (i >= _hud.NumberPlayerMana)
			{
				BlitSprite(_hud.playerManaEmpty[i], sf::Vector2f{ 0, 0 } + camOffSet, 0, _window, camScale);
			}
		}

		BlitSprite(_hud.timerFrames[0], sf::Vector2f{ 0, 0 * camScale.y } + camOffSet, 0, _window, camScale);
		BlitSprite(_hud.timerFrames[0], sf::Vector2f{ 0, 0 * camScale.y } + camOffSet, 0, _window, camScale);
		_hud.timerText[MINUTES].setPosition(sf::Vector2f{ 1750 * camScale.x, 44 * camScale.y } + camOffSet);
		_hud.timerText[MINUTES].setScale(camScale);
		_window.draw(_hud.timerText[MINUTES]);

		_hud.textNumberTurn.setPosition(sf::Vector2f{ 50 * camScale.x, 50 * camScale.y } + camOffSet);
		_hud.textNumberTurn.setScale(camScale);
		_window.draw(_hud.textNumberTurn);

		BlitSprite(_hud.timerFrames[1], sf::Vector2f{ 0, 0 } + camOffSet, 0, _window, camScale);

		_hud.scoreTextPlayer1.setPosition(sf::Vector2f{ 800 * camScale.x, 0 * camScale.y } + camOffSet);
		_hud.scoreTextPlayer1.setScale(camScale);
		_window.draw(_hud.scoreTextPlayer1);

		_hud.scoreTextPlayer2.setPosition(sf::Vector2f{ 1050 * camScale.x, 0 * camScale.y } + camOffSet);
		_hud.scoreTextPlayer2.setScale(camScale);

		_window.draw(_hud.scoreTextPlayer2);
		_hud.playerName1.setPosition(sf::Vector2f{ (float)(700 - (40 * static_cast<int>(_hud.playerName1.getString().getSize())))* camScale.x, 0 } + camOffSet);
		_hud.playerName1.setScale(camScale);

		_window.draw(_hud.playerName1);

		_hud.playerName2.setPosition(sf::Vector2f{ 1200 * camScale.x, 0 } + camOffSet);
		_hud.playerName2.setScale(camScale);

		_window.draw(_hud.playerName2);

		if (_hud.unitOver.GetRole() != NOTHING)
		{
			_hud.textInfoStatUnit[0].setString(std::to_string(_hud.unitOver.GetHp()));
			_hud.textInfoStatUnit[1].setString(std::to_string(_hud.unitOver.GetAtk()));
			_hud.textInfoStatUnit[0].setScale(camScale);
			_hud.textInfoStatUnit[1].setScale(camScale);
			_hud.textInfoStatUnit[0].setPosition(sf::Vector2f{ 85 * camScale.x, 610 * camScale.y } + camOffSet);
			_hud.textInfoStatUnit[1].setPosition(sf::Vector2f{ 85 * camScale.x, 670 * camScale.y } + camOffSet);
			BlitSprite(_hud.spriteOverUnit[_hud.overUnitTeam % 2], sf::Vector2f{ 0 * camScale.x, ((SCREEN_HEIGHT) / 5)* camScale.y } + camOffSet, 0, _window, camScale);
			BlitSprite(_hud.cardUnit[_hud.unitOver.GetRole()], sf::Vector2f{ 25 * camScale.x, ((SCREEN_HEIGHT + 100) / 5)* camScale.y } + camOffSet, 0, _window, camScale);

			_window.draw(_hud.textInfoStatUnit[0]);
			_window.draw(_hud.textInfoStatUnit[1]);
			sf::Vector2i sumPos = sf::Vector2i(120 * camScale.x, ((SCREEN_HEIGHT / 2) + 85) * camScale.y) + (sf::Vector2i)camOffSet;
			_hud.textBoxSummary[_hud.unitOver.GetRole()].SplitTextIntoLines();
			_hud.textBoxSummary[_hud.unitOver.GetRole()].RenderText(_window, sumPos);
			sf::Vector2i namePos = sf::Vector2i(80 * camScale.x, ((SCREEN_HEIGHT / 2) + 25) * camScale.y) + (sf::Vector2i)camOffSet;
			_hud.textBoxName[_hud.unitOver.GetRole()].SplitTextIntoLines();
			_hud.textBoxName[_hud.unitOver.GetRole()].RenderText(_window, namePos);
		}

		Player playerTemp1 = *GameData::GetInstance()->GetPlayer1();
		Player playerTemp2 = *GameData::GetInstance()->GetPlayer2();

		if (_hud.numberTurn % 2 == 0)
		{
			if (_hud.numberTurn <= 0)
			{
				_hud.limitUnitSetUp.setString((std::to_string(playerTemp1.GetUnit().size())) + "/ 5 Units ");
			}
			else
			{
				_hud.limitUnitSetUp.setString((std::to_string(playerTemp1.GetUnit().size())) + "/ 12 Units");
			}
			_hud.limitUnitSetUp.setPosition(sf::Vector2f{ 200 * camScale.x, 200 * camScale.y } + camOffSet);
			_hud.limitUnitSetUp.setScale(camScale);
		}
		else
		{
			if (_hud.numberTurn <= 0)
			{
				_hud.limitUnitSetUp.setString((std::to_string(playerTemp2.GetUnit().size())) + "/ 5 Units ");
			}
			else
			{
				_hud.limitUnitSetUp.setString((std::to_string(playerTemp2.GetUnit().size())) + "/ 12 Units ");
			}
			_hud.limitUnitSetUp.setPosition(sf::Vector2f{ 200 * camScale.x, 200 * camScale.y } + camOffSet);
			_hud.limitUnitSetUp.setScale(camScale);
		}
		_window.draw(_hud.limitUnitSetUp);

		for (int i = 0; i < playerTemp1.GetUnit().size(); i++)
		{
			sf::Vector2f pos = { GridData::World2Screen(playerTemp1.GetUnit()[i].GetPos().x,  playerTemp1.GetUnit()[i].GetPos().y, 0) };
			_hud.HPOverlay.setOutlineColor(sf::Color::Black);
			_hud.HPOverlay.setOutlineThickness(2);
			_hud.AttackOverlay.setOutlineColor(sf::Color::Black);
			_hud.AttackOverlay.setOutlineThickness(2);
			_hud.HPOverlay.setString(std::to_string(playerTemp1.GetUnit()[i].GetHp()));
			_hud.AttackOverlay.setString(std::to_string(playerTemp1.GetUnit()[i].GetAtk()));
			_hud.HPOverlay.setScale(camScale);
			_hud.AttackOverlay.setScale(camScale);
			_hud.HPOverlay.setPosition(sf::Vector2f{ pos.x + 20, pos.y });
			_hud.AttackOverlay.setPosition(sf::Vector2f{ pos.x - 20, pos.y });
			if (_hud.showInfoUnit == true)
			{
				_window.draw(_hud.HPOverlay);
				_window.draw(_hud.AttackOverlay);
			}
		}
		if (_hud.numberTurn <= 0)
		{

		}
		for (int i = 0; i < playerTemp2.GetUnit().size(); i++)
		{
			sf::Vector2f pos = { GridData::World2Screen(playerTemp2.GetUnit()[i].GetPos().x,  playerTemp2.GetUnit()[i].GetPos().y, 0) };

			_hud.HPOverlay.setOutlineColor(sf::Color::Black);
			_hud.HPOverlay.setOutlineThickness(2);
			_hud.AttackOverlay.setOutlineColor(sf::Color::Black);
			_hud.AttackOverlay.setOutlineThickness(2);
			_hud.HPOverlay.setString(std::to_string(playerTemp2.GetUnit()[i].GetHp()));
			_hud.AttackOverlay.setString(std::to_string(playerTemp2.GetUnit()[i].GetAtk()));
			_hud.HPOverlay.setScale(camScale);
			_hud.AttackOverlay.setScale(camScale);
			_hud.HPOverlay.setPosition(sf::Vector2f{ pos.x + 20, pos.y });
			_hud.AttackOverlay.setPosition(sf::Vector2f{ pos.x - 20, pos.y });
			if (_hud.showInfoUnit == true)
			{
				_window.draw(_hud.HPOverlay);
				_window.draw(_hud.AttackOverlay);
			}
		}

		BlitSprite(_hud.unitBackplate, sf::Vector2f{ 0, -70 * camScale.y } + camOffSet, 0, _window, camScale);

		for (int i = 0; i < 4; i++)
		{
			_hud.TextnumberUnitRemained[i].setPosition(sf::Vector2f{ (55 + (float(i) * float(52)))* camScale.x, 890 * camScale.y } + camOffSet);
			_hud.TextnumberUnitRemained[i].setScale(camScale);
			_window.draw(_hud.TextnumberUnitRemained[i]);

			BlitSprite(_hud.unitFrames[i], sf::Vector2f{ (40 + (float(i) * float(50)))* camScale.x, 835 * camScale.y } + camOffSet, 0, _window, camScale);
			if (_hud.targetUnit == i)
			{
				mousePos.x -= 20;
				mousePos.y -= 30;
				//_hud.unitFrames[i].setPosition(sf::Vector2f{ mousePos.x * camScale.x , mousePos.y * camScale.y } + camOffSet);
				BlitSprite(_hud.unitFrames[i], sf::Vector2f{ mousePos.x* camScale.x, mousePos.y* camScale.y } + camOffSet, 0, _window);
			}
			if (_hud.overUnit == i)
			{
				_hud.textInfoStatUnit[0].setString(std::to_string(_hud.tabStats[i].x));
				_hud.textInfoStatUnit[1].setString(std::to_string(_hud.tabStats[i].y));
				_hud.textInfoStatUnit[0].setScale(camScale);
				_hud.textInfoStatUnit[1].setScale(camScale);
				_hud.textInfoStatUnit[0].setPosition(sf::Vector2f{ 65 * camScale.x, 640 * camScale.y } + camOffSet);
				_hud.textInfoStatUnit[1].setPosition(sf::Vector2f{ 65 * camScale.x, 590 * camScale.y } + camOffSet);
				BlitSprite(_hud.cardUnitBack, sf::Vector2f{ 0, (SCREEN_HEIGHT / 5)* camScale.y } + camOffSet, 0, _window, camScale);
				BlitSprite(_hud.cardUnit[i], sf::Vector2f{ 0, ((SCREEN_HEIGHT) / 5)* camScale.y } + camOffSet, 0, _window, camScale);
				_window.draw(_hud.textInfoStatUnit[0]);
				_window.draw(_hud.textInfoStatUnit[1]);
			}

		}
		if (_hud.changingTurn == true)
		{
			_hud.spriteX = animationChangeTurn(_hud, camOffSet, camScale, _window, _hud.spriteX);
			BlitSprite(_hud.changeTurnSprite, sf::Vector2f{ _hud.spriteX* camScale.x, (80 + (SCREEN_HEIGHT / 3))* camScale.y } + camOffSet, 0, _window, camScale);
		}
		if (playerTemp1.GetScore() >= 1)
		{
			BlitSprite(_hud.VictorySprite, sf::Vector2f{ 0, 0 } + camOffSet, 0, _window, camScale);
		}
		else if (playerTemp2.GetScore() >= 1)
		{
			BlitSprite(_hud.VictorySprite, sf::Vector2f{ 0, 0 } + camOffSet, 0, _window, camScale);
		}
	}

	void CleanupHud(HudData & _hud)
	{

	}

	bool CheckCollisionMouseSprite(sf::Vector2i _mousePos, sf::Sprite _sprite)
	{
		sf::FloatRect spriteHitbox = _sprite.getGlobalBounds();


		if (_mousePos.x >= spriteHitbox.left &&
			_mousePos.x <= spriteHitbox.left + spriteHitbox.width &&
			_mousePos.y >= spriteHitbox.top &&
			_mousePos.y <= spriteHitbox.top + spriteHitbox.height)
		{
			return true;
		}
		return false;
	}
	bool CheckCollisionMouseSprite(sf::Vector2i _mousePos, sf::Sprite _sprite, sf::Vector2f camOffset, sf::Vector2f camScale)
	{
		sf::FloatRect spriteHitbox = _sprite.getGlobalBounds();

		spriteHitbox.left -= camOffset.x;
		spriteHitbox.top -= camOffset.y;

		spriteHitbox.left /= camScale.x;
		spriteHitbox.top /= camScale.y;
		if (_mousePos.x >= spriteHitbox.left &&
			_mousePos.x <= spriteHitbox.left + spriteHitbox.width &&
			_mousePos.y >= spriteHitbox.top &&
			_mousePos.y <= spriteHitbox.top + spriteHitbox.height)
		{
			return true;
		}
		return false;
	}