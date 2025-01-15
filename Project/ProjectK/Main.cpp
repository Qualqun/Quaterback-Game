#include "Main.hpp"
#include "Utilities/Utilities.hpp"

int main()
{
	MainData* main = new MainData;
	srand(time(NULL));

	Load(*main);

	while (main->window->isOpen())
	{
		PollEvent(*main);
		Update(*main);
		Draw(*main, *main->window);
	}

	Cleanup(*main);
	delete main;
	return EXIT_SUCCESS;
}

void Load(MainData& _main)
{
	sf::VideoMode mode = { SCREEN_WIDTH, SCREEN_HEIGHT };
	_main.window = new sf::RenderWindow(mode, WINDOW_NAME, sf::Style::Fullscreen); //create window in the heap
	_main.window->setVerticalSyncEnabled(true);
	_main.window->setFramerateLimit(FPS_MAX);

	//Window Position
	sf::Vector2i windowPosition = _main.window->getPosition();
	windowPosition.y /= 2;
	_main.window->setPosition(windowPosition);

	_main.gameClock = new sf::Clock();
	_main.event = new sf::Event;
	_main.game = GameData::GetInstance();
	_main.menuData = new MenuData;

	_main.gameState = new GameStates;

	_main.gameState->LoadGameStates();
	_main.gameState->SetCurrentState("MENU");
	InitMenu(*_main.menuData);
}

void PollEvent(MainData& _main)
{
	while (_main.window->pollEvent(*_main.event))
	{
		switch (_main.event->type)
		{
		case sf::Event::Closed:
			_main.window->close();
			break;
		case sf::Event::KeyPressed:
			if (_main.gameState->GetCurrentState() == "MENU" && _main.menuData->state != MAIN)
			{
				KeyPressedMenu(*_main.menuData, *_main.window, *_main.event, *_main.gameState, *_main.game->GetSoundData());
			}
			else if (_main.gameState->GetCurrentState() == "GAME")
			{
				_main.game->KeyPressed(*_main.event);
				KeyPressedMain(_main);

			}
			else
			{
				KeyPressedMain(_main);
			}
			break;
		case sf::Event::KeyReleased:
			_main.game->KeyReleased(*_main.event);
			break;
		case sf::Event::MouseButtonPressed:
			if (_main.gameState->GetCurrentState() == "MENU")
			{
				MousePressedMenu(*_main.menuData, *_main.window, *_main.event, *_main.gameState, *_main.game->GetCameraData(), *_main.game->GetSoundData());
			}
			else if (_main.gameState->GetCurrentState() == "GAME")
			{
				_main.game->MousePressed(*_main.window, *_main.event, *_main.game->GetSoundData());

			}
			_main.game->GetCameraData()->oldMousePos = sf::Mouse::getPosition();
			break;
		case sf::Event::MouseMoved:
			if (_main.gameState->GetCurrentState() == "MENU")
			{
				MouseMovedMenu(*_main.menuData, *_main.window, *_main.event, *_main.game->GetSoundData());

			}
			else if (_main.gameState->GetCurrentState() == "GAME")
			{
				_main.game->MouseMoved(*_main.window, *_main.event);
			}
		case sf::Event::MouseWheelScrolled:
			if (_main.gameState->GetCurrentState() == "GAME")
			{
				_main.game->MouseWheelScrolled(*_main.window, *_main.event);
			}
		default:
			break;
		}
	}
}

void KeyPressedMain(MainData& _main)
{

	switch (_main.event->key.code)
	{
	case sf::Keyboard::Key::Escape:
		_main.window->close();
		break;
	case sf::Keyboard::Key::G:
		_main.gameState->SetCurrentState("GAME");
		break;
	case sf::Keyboard::Key::M:
		_main.gameState->SetCurrentState("MENU");
		break;
	case sf::Keyboard::Key::P:
		_main.gameState->SetCurrentState("PAUSE");
		break;
		break;
	default:
		break;
	}
}

void Update(MainData& _main)
{
	float dt = _main.gameClock->restart().asSeconds();

	if (_main.gameState->GetCurrentState() == "GAME")
	{
		_main.game->Update(*_main.window, dt);
	}
}

void Draw(MainData& _main, sf::RenderWindow& _window)
{
	_window.clear(sf::Color(149, 150, 180));

	_window.setView(_main.game->GetCameraData()->GetCamera());

	if (_main.gameState->GetCurrentState() == "MENU")
	{
		DrawMenu(*_main.menuData, _window);
	}
	if (_main.gameState->GetCurrentState() == "GAME")
	{
		_main.game->Draw(_window);
	}


	//Temp to show currentState text <-----TO DELETE
	//_main.gameState->text.setString(_main.gameState->GetCurrentState());
	//_window.draw(_main.gameState->text);

	_window.display();
}

void Cleanup(MainData& _main)
{
	delete _main.event;
	delete _main.gameClock;
	delete _main.window;
	delete _main.game;
}