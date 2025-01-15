#include "Game.hpp"
#include "../HitParticle.hpp"
#include "../WindParticle.hpp"
#include "../DustParticle.hpp"

GameData* GameData::_SINGLETON = nullptr;

class GameStates;
GameData::GameData()
{
	FontManager::InitFonts();
	Translator::InitTranslator();

	m_hudData = new HudData;
	m_grid = new GridData;
	m_players = new Player[2];
	m_camera = new CameraData;
	m_sound = new Sound;

	m_particleManager = new ParticleManager();

	m_turn = -1;
	LoadHud(*m_hudData);

	m_units1[MIDDLE] = LoadSprite("Sprite/Units/Squad1/NormalVue1.png", true);
	m_units1[DEFENSIVE] = LoadSprite("Sprite/Units/Squad1/TankVue1.png", true);
	m_units1[CORNERBACK] = LoadSprite("Sprite/Units/Squad1/SpeedVue1.png", true);
	m_units1[QUARTERBACK] = LoadSprite("Sprite/Units/Squad1/SwanVue1.png", true);
	m_units1[4] = LoadSprite("Sprite/Units/Balles.png", true);
	m_units1[5] = LoadSprite("Sprite/Units/BallesUp.png", true);

	m_units2[MIDDLE] = LoadSprite("Sprite/Units/Squad2/NormalVue3.png", true);
	m_units2[DEFENSIVE] = LoadSprite("Sprite/Units/Squad2/TankVue3.png", true);
	m_units2[CORNERBACK] = LoadSprite("Sprite/Units/Squad2/SpeedVue3.png", true);
	m_units2[QUARTERBACK] = LoadSprite("Sprite/Units/Squad2/SwanVue3.png", true);
	m_units2[4] = LoadSprite("Sprite/Units/Balles.png", true);
	m_units2[5] = LoadSprite("Sprite/Units/BallesUp.png", true);



	m_limit.xMin = 0;
	m_limit.xMax = NB_LINE;
	m_limit.yMin = 1;
	m_limit.yMax = 4;

	m_grid->LoadGrid();
	m_background = LoadSprite("Sprite/Background.png", false);

	Card::InitCardsRender();
}

GameData* GameData::GetInstance()
{
	if (_SINGLETON == nullptr)
	{
		_SINGLETON = new GameData;
	}

	return _SINGLETON;
}

GameData::~GameData()
{
	delete m_hudData;
	delete m_grid;
	delete[] m_players;
	delete m_particleManager;

	m_players = nullptr;
}

void GameData::Update(sf::RenderWindow& _window, float& _dt)
{
	if (m_turn % 2 == 0)
	{
		UpdateHud(*m_hudData, _window, _dt, m_players[0], m_players[1], *m_camera);
	}
	else
	{
		UpdateHud(*m_hudData, _window, _dt, m_players[1], m_players[0], *m_camera);
	}

	m_grid->UdpateGrid();
	UpdateCamera(*m_camera, _dt);
	m_particleManager->Update(_dt);

	for (int i = 0; i < 2; i++)
	{
		m_players[i].Update(_dt);
	}

	if (rand() % 12 == 0)
	{
		float y = (rand() / (float)RAND_MAX) * 25 - 10;
		GetParticleManager()->AddParticle(new WindParticle(sf::Vector2f(-2, y), 22.f));
	}
}

void GameData::Draw(sf::RenderWindow& _window)
{

	sf::Vector2f camCenter = m_camera->GetCamera().getCenter();
	sf::Vector2f camSize = m_camera->GetCamera().getSize();
	sf::Vector2f camOffset = camCenter - sf::Vector2f{ camSize.x / 2, camSize.y / 2 };
	sf::Vector2f camScale = { camSize.x / SCREEN_WIDTH , camSize.y / SCREEN_HEIGHT };
	_window.draw(m_background);
	m_grid->DrawGrid(_window);
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			m_players[i].DrawUnit(_window, m_units1);

			for (size_t j = 0; j < m_players[i].GetUnit().size(); j++)
			{
				sf::Vector2i pos = m_players[i].GetUnit()[j].GetPos();

				m_grid->GetCell()[pos.x][pos.y].m_sprite->setColor(sf::Color::Red);

				if (rand() % 5 == 0)
				{
					GetParticleManager()->AddParticle(new DustParticle(sf::Vector2f(pos.x + (rand() / (float)RAND_MAX), pos.y + (rand() / (float)RAND_MAX)), 1.f, sf::Color(100 +rand() % 255,0,0)));
				}
			}
		}
		else if (i == 1)
		{
			m_players[i].DrawUnit(_window, m_units2);

			for (size_t j = 0; j < m_players[i].GetUnit().size(); j++)
			{
				sf::Vector2i pos = m_players[i].GetUnit()[j].GetPos();

				m_grid->GetCell()[pos.x][pos.y].m_sprite->setColor(sf::Color::Blue);

				if (rand() % 5 == 0)
				{
					GetParticleManager()->AddParticle(new DustParticle(sf::Vector2f(pos.x + (rand() / (float)RAND_MAX), pos.y + (rand() / (float)RAND_MAX)), 1.f, sf::Color(0, 0, 100 + rand() % 255)));
				}
			}
		}
	}

	m_particleManager->Draw(_window);
	this->GetPlayerFromTurn()->GetCardStack()->RenderStack(_window, sf::Vector2f(camSize.x - 250 + camOffset.x, camSize.y - 60 + camOffset.y));
	DrawHud(*m_hudData, _window, camOffset, camScale);
}

void GameData::MouseMoved(sf::RenderWindow& _window, sf::Event& _event)
{
	sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));

	m_grid->MouseMovedGrid(mousePos, GetPlayerFromTurn()->GetMana());

	//std::cout << "Mana joueur 1 : " << m_players[0].GetMana() << '\n';
	//std::cout << "Mana joueur 2 : " << m_players[1].GetMana() << '\n';
}


void GameData::MouseWheelScrolled(sf::RenderWindow& _window, sf::Event& _event)
{
	m_camera->MouseWheelScrolledCamera(_window, _event);
}

void GameData::KeyPressed(sf::Event& _event)
{

	switch (_event.key.code)
	{
	case sf::Keyboard::Key::LControl:
		break;
	case sf::Keyboard::Key::Enter:
		m_turn++;

		reloadTurn(*m_hudData, m_players[0], m_players[1], m_turn);

		m_players[m_turn % 2].SetMana(5);
		m_players[m_turn % 2].SetUnitSelected(-1);
		GetGridData()->SetIsClicked(false);

		if (m_turn % 2)
		{
			m_limit.yMin = 1;
			m_limit.yMax = 4;
		}
		else
		{
			m_limit.yMin = NB_COLUMN - 4;
			m_limit.yMax = NB_COLUMN - 1;
		}

	default:
		break;
	}
}

void GameData::KeyReleased(sf::Event& _event)
{
	switch (_event.key.code)
	{
	case sf::Keyboard::Key::LControl:
		break;
	default:
		break;
	}
}

void GameData::MousePressed(sf::RenderWindow& _window, sf::Event& _event, Sound& _sound)
{
	sf::Vector2f camCenter = m_camera->GetCamera().getCenter();
	sf::Vector2f camSize = m_camera->GetCamera().getSize();
	sf::Vector2f camOffset = camCenter - sf::Vector2f{ camSize.x / 2, camSize.y / 2 };
	sf::Vector2f camScale = { camSize.x / SCREEN_WIDTH , camSize.y / SCREEN_HEIGHT };

	sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
	if (_event.mouseButton.button == sf::Mouse::Left)
	{
		//m_grid->MousePressedGrid(mousePos);
	}
	if (m_turn < 0)
	{
		m_players[1].MousePressed(m_turn, *m_grid, mousePos, m_limit, _sound);
	}
	else
	{
		m_players[m_turn % 2].MousePressed(m_turn, *m_grid, mousePos, m_limit, _sound);
	}
	if (_event.mouseButton.button == sf::Mouse::Left && m_hudData->targetUnit != 6)
	{
		sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));

		m_hudData->targetUnit = 6;
		m_hudData->whichFramesClicked = 6;
		for (int i = 0; i < 4; i++)
		{
			m_hudData->moveFramesInfo[i] = 0;
		}
	}
	else
	{
		if (m_turn == 0)
		{
			MousePressedHUD(m_hudData, _window, _event, m_players[0], m_players[1], camOffset, camScale);
		}
		else
		{
			MousePressedHUD(m_hudData, _window, _event, m_players[1], m_players[0], camOffset, camScale);
		}
	}
}

void GameData::IncrementTurn()
{
	this->m_turn++;
}

HudData* GameData::GetHudData()
{
	return m_hudData;
}

GridData* GameData::GetGridData()
{
	return m_grid;
}

ParticleManager* GameData::GetParticleManager()
{
	return m_particleManager;
}

Player* GameData::GetPlayer1()
{
	return &m_players[0];
}

Player* GameData::GetPlayer2()
{
	return  &m_players[1];
}

CameraData* GameData::GetCameraData()
{
	return m_camera;
}

Sound* GameData::GetSoundData()
{
	return m_sound;
}

sf::Sprite GameData::GetBackground()
{
	return m_background;
}

int GameData::GetTurn()
{
	return m_turn;
}

Player* GameData::GetPlayerFromTurn()
{
	if (this->m_turn & 1)
	{
		return &m_players[1];
	}
	else
	{
		return  &m_players[0];
	}
}

Player* GameData::GetOtherPlayer(Player* _player)
{
	if (_player == &m_players[1])
	{
		return &m_players[0];
	}
	else
	{
		return &m_players[1];
	}
}

