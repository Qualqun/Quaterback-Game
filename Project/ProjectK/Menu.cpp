#include "Menu.hpp"
#include "FontManager.hpp"
#include "Translator.hpp"
#include "Game/Game.hpp"

void InitMenu(MenuData& _menu)
{
	//Loading sprite of the element
	_menu.background = LoadSprite("Sprite/Menu/Background.png", false);
	_menu.titleName = LoadSprite("Sprite/Menu/TitleName.png", true);
	_menu.studioLogo = LoadSprite("Sprite/Menu/StudioLogo.png", true);
	_menu.credit = LoadSprite("Sprite/Menu/Credit.png", true);
	_menu.tutorial = LoadSprite("Sprite/Menu/Tutorial.png", false);
	_menu.soundSliderInfo = LoadSprite("Sprite/Menu/SoundSliderInfo.png", true);
	_menu.soundSlider = LoadSprite("Sprite/Menu/Slider.png", true);
	_menu.soundSliderCursor = LoadSprite("Sprite/Menu/SliderCursor.png", true);

	
	//Set position of the element
	_menu.titleName.setPosition({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 });
	sf::FloatRect studioHitbox = _menu.studioLogo.getGlobalBounds();
	_menu.studioLogo.setPosition({ 0 + studioHitbox.width / 2, SCREEN_HEIGHT - studioHitbox.height / 2 });
	_menu.credit.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 5 * 2.25 });

	_menu.soundSlider.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 });
	_menu.soundSliderCursor.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 });
	sf::FloatRect sliderHitbox = _menu.soundSlider.getGlobalBounds();
	_menu.soundSliderInfo.setPosition({ sliderHitbox.left + sliderHitbox.width / 2 ,sliderHitbox.top - sliderHitbox.height });


	sf::Sprite button;
	bool buttonStatus = false;
	//Loading sprite of the buttons
	button = LoadSprite("Sprite/Menu/PlayButton.png", true);
	_menu.button.push_back(std::make_pair(button, buttonStatus));
	button = LoadSprite("Sprite/Menu/TutorialButton.png", true);
	_menu.button.push_back(std::make_pair(button, buttonStatus));
	button = LoadSprite("Sprite/Menu/CreditButton.png", true);
	_menu.button.push_back(std::make_pair(button, buttonStatus));
	button = LoadSprite("Sprite/Menu/OptionButton.png", true);
	_menu.button.push_back(std::make_pair(button, buttonStatus));
	button = LoadSprite("Sprite/Menu/QuitButton.png", true);
	_menu.button.push_back(std::make_pair(button, buttonStatus));
	button = LoadSprite("Sprite/Menu/BackButton.png", true);
	_menu.button.push_back(std::make_pair(button, buttonStatus));


	//Set position of the buttons
	_menu.button[BPLAY].first.setPosition({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	sf::FloatRect buttonHitbox = _menu.button[BPLAY].first.getGlobalBounds();
	sf::Vector2f playPos = _menu.button[BPLAY].first.getPosition();
	_menu.button[BTUTORIAL].first.setPosition({ SCREEN_WIDTH / 2, playPos.y + buttonHitbox.height * 1.1f });
	sf::Vector2f tutoPos = _menu.button[BTUTORIAL].first.getPosition();
	_menu.button[BCREDIT].first.setPosition({ SCREEN_WIDTH / 2, tutoPos.y + buttonHitbox.height * 1.1f });
	sf::Vector2f creditPos = _menu.button[BCREDIT].first.getPosition();
	_menu.button[BOPTION].first.setPosition({ SCREEN_WIDTH / 2 , creditPos.y + buttonHitbox.height * 1.1f });
	sf::Vector2f optionPos = _menu.button[BOPTION].first.getPosition();
	_menu.button[BQUIT].first.setPosition({ SCREEN_WIDTH / 2 , optionPos.y + buttonHitbox.height * 1.1f });
	_menu.button[BBACK].first.setPosition({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10 * 9 });

	//Set the menu we are in
	_menu.state = MAIN;
}

void UpdateMenu(MenuData& _menu)
{

}

void DrawMenu(MenuData& _menu, sf::RenderWindow& _window)
{
	_window.draw(_menu.background);

	//Check which menu are we in
	if (_menu.state == MAIN)
	{
		_window.draw(_menu.titleName);
		_window.draw(_menu.studioLogo);

		//Draw the button with their select animation
		BlitSprite(_menu.button[BPLAY].first, _menu.button[BPLAY].first.getPosition() + sf::Vector2f{ 0, -OFFSET_SELECTION * _menu.button[BPLAY].second }, 0, _window);
		_menu.button[BPLAY].first.setPosition(_menu.button[BPLAY].first.getPosition() + sf::Vector2f{ 0,+OFFSET_SELECTION * _menu.button[BPLAY].second });
		
		BlitSprite(_menu.button[BTUTORIAL].first, _menu.button[BTUTORIAL].first.getPosition() + sf::Vector2f{ 0, -OFFSET_SELECTION * _menu.button[BTUTORIAL].second }, 0, _window);
		_menu.button[BTUTORIAL].first.setPosition(_menu.button[BTUTORIAL].first.getPosition() + sf::Vector2f{ 0,+OFFSET_SELECTION * _menu.button[BTUTORIAL].second });
		
		BlitSprite(_menu.button[BCREDIT].first, _menu.button[BCREDIT].first.getPosition() + sf::Vector2f{ 0, -OFFSET_SELECTION * _menu.button[BCREDIT].second }, 0, _window);
		_menu.button[BCREDIT].first.setPosition(_menu.button[BCREDIT].first.getPosition() + sf::Vector2f{ 0,+OFFSET_SELECTION * _menu.button[BCREDIT].second });

		BlitSprite(_menu.button[BOPTION].first, _menu.button[BOPTION].first.getPosition() + sf::Vector2f{ 0, -OFFSET_SELECTION * _menu.button[BOPTION].second }, 0, _window);
		_menu.button[BOPTION].first.setPosition(_menu.button[BOPTION].first.getPosition() + sf::Vector2f{ 0,+OFFSET_SELECTION * _menu.button[BOPTION].second });

		BlitSprite(_menu.button[BQUIT].first, _menu.button[BQUIT].first.getPosition() + sf::Vector2f{ 0, -OFFSET_SELECTION * _menu.button[BQUIT].second }, 0, _window);
		_menu.button[BQUIT].first.setPosition(_menu.button[BQUIT].first.getPosition() + sf::Vector2f{ 0,+OFFSET_SELECTION * _menu.button[BQUIT].second });
	}
	if (_menu.state == TUTORIAL)
	{
		_window.draw(_menu.tutorial);

		//Draw the button with their select animation
		BlitSprite(_menu.button[BBACK].first, _menu.button[BBACK].first.getPosition() + sf::Vector2f{ 0, -OFFSET_SELECTION * _menu.button[BBACK].second }, 0, _window);
		_menu.button[BBACK].first.setPosition(_menu.button[BBACK].first.getPosition() + sf::Vector2f{ 0,+OFFSET_SELECTION * _menu.button[BBACK].second });
	}
	if (_menu.state == CREDIT)
	{
		_window.draw(_menu.credit);

		//Draw the button with their select animation
		BlitSprite(_menu.button[BBACK].first, _menu.button[BBACK].first.getPosition() + sf::Vector2f{ 0, -OFFSET_SELECTION * _menu.button[BBACK].second }, 0, _window);
		_menu.button[BBACK].first.setPosition(_menu.button[BBACK].first.getPosition() + sf::Vector2f{ 0,+OFFSET_SELECTION * _menu.button[BBACK].second });
	}
	if (_menu.state == OPTION)
	{
		_window.draw(_menu.soundSliderInfo);
		_window.draw(_menu.soundSlider);
		_window.draw(_menu.soundSliderCursor);

		sf::Text french(Translator::GetTranslation("lang.fr"), *FontManager::GetFont("Hyper Super Regular"), 60);
		french.setFillColor(sf::Color::White);
		french.setOutlineColor(sf::Color::Black);
		french.setOutlineThickness(2);

		sf::Text english(Translator::GetTranslation("lang.en"), *FontManager::GetFont("Hyper Super Regular"), 60);
		english.setFillColor(sf::Color::White);
		english.setOutlineColor(sf::Color::Black);
		english.setOutlineThickness(2);

		CameraData* camera = GameData::GetInstance()->GetCameraData();

		french.setPosition(SCREEN_WIDTH / 2 - french.getGlobalBounds().getSize().x - 30, SCREEN_HEIGHT / 2 + 100);
		english.setPosition(SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 + 100);

		sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));

		sf::FloatRect frenchHitbox = french.getGlobalBounds();
		if (frenchHitbox.contains(mousePos))
		{
			french.setFillColor(sf::Color::Green);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				Translator::ChangeLang(Lang::FRENCH);
		}
		else
		{
			french.setFillColor(sf::Color::White);
		}

		sf::FloatRect englishHitbox = english.getGlobalBounds();
		if (englishHitbox.contains(mousePos))
		{
			english.setFillColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				Translator::ChangeLang(Lang::ENGLISH);
		}
		else
		{
			english.setFillColor(sf::Color::White);
		}

		_window.draw(french);
		_window.draw(english);

		//Draw the button with their select animation
		BlitSprite(_menu.button[BBACK].first, _menu.button[BBACK].first.getPosition() + sf::Vector2f{ 0, -OFFSET_SELECTION * _menu.button[BBACK].second }, 0, _window);
		_menu.button[BBACK].first.setPosition(_menu.button[BBACK].first.getPosition() + sf::Vector2f{ 0,+OFFSET_SELECTION * _menu.button[BBACK].second });
	}
}

void CleanupMenu(MenuData& _menu)
{

}

void KeyPressedMenu(MenuData& _menu, sf::RenderWindow& _window, sf::Event& _event, GameStates& _gameState, Sound& _sound)
{
	//Check which menu are we in
	if (_menu.state == MAIN)
	{

	}
	else if (_menu.state == TUTORIAL)
	{
		if (_event.key.code == sf::Keyboard::Key::Escape)
		{
			_menu.state = MAIN;
			//We use this function while changing the submenu to check the colision of the button and mouse
			MouseMovedMenu(_menu, _window, _event, _sound);
		}
	}
	else if (_menu.state == CREDIT)
	{
		if (_event.key.code == sf::Keyboard::Key::Escape)
		{
			_menu.state = MAIN;
			//We use this function while changing the submenu to check the colision of the button and mouse
			MouseMovedMenu(_menu, _window, _event, _sound);
		}
	}
	else if (_menu.state == OPTION)
	{
		if (_event.key.code == sf::Keyboard::Key::Escape)
		{
			_menu.state = MAIN;
			//We use this function while changing the submenu to check the colision of the button and mouse
			MouseMovedMenu(_menu, _window, _event, _sound);
		}

		if (_event.key.code == sf::Keyboard::Key::P)
		{
			_sound.UseSound(_sound.GetTestSoundIndex());
			//UseSound(_sound.GetTestSoundIndex());
			_sound.IncrementTestSoundIndex();
		}
		switch (_event.key.code)
		{
		case sf::Keyboard::Key::Numpad0:
			_sound.StartBackgroundMusic(0);
			break;
		case sf::Keyboard::Key::Numpad1:
			_sound.StartBackgroundMusic(1);
			break;
		case sf::Keyboard::Key::Numpad2:
			_sound.StartBackgroundMusic(2);
			break;
		default:
			break;
		}
	}
}

void MousePressedMenu(MenuData& _menu, sf::RenderWindow& _window, sf::Event& _event, GameStates& _gameState, CameraData& _cameraData, Sound& _sound)
{
	//Check which menu are we in
	if (_menu.state == MAIN)
	{
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			//Get the mouse pos and buttons hitbox to check any collision
			sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
			sf::FloatRect buttonHitbox = _menu.button[BPLAY].first.getGlobalBounds();
			if (buttonHitbox.contains(mousePos))
			{
				_gameState.SetCurrentState("GAME");
				_cameraData.SetCameraGame();
				_sound.UseSound(BUTTONCLICK);
				//UseSound(BUTTONCLICK);
				_sound.StartBackgroundMusic(BACKGROUNDCALM);
				
			}
			buttonHitbox = _menu.button[BTUTORIAL].first.getGlobalBounds();
			if (buttonHitbox.contains(mousePos))
			{
				_menu.state = TUTORIAL;
				//We use this function while changing the submenu to check the colision of the button and mouse
				MouseMovedMenu(_menu, _window, _event, _sound);
				_menu.button[BBACK].first.setPosition({ SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 10 * 9 });
				_sound.UseSound(BUTTONCLICK);
				//UseSound(BUTTONCLICK);
			}
			buttonHitbox = _menu.button[BCREDIT].first.getGlobalBounds();
			if (buttonHitbox.contains(mousePos))
			{
				_menu.state = CREDIT;
				//We use this function while changing the submenu to check the colision of the button and mouse
				MouseMovedMenu(_menu, _window, _event, _sound);
				_menu.button[BBACK].first.setPosition({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10 * 9 });
				_sound.UseSound(BUTTONCLICK);
				//UseSound(BUTTONCLICK);
			}
			buttonHitbox = _menu.button[BOPTION].first.getGlobalBounds();
			if (buttonHitbox.contains(mousePos))
			{
				_menu.state = OPTION;
				//We use this function while changing the submenu to check the colision of the button and mouse
				MouseMovedMenu(_menu, _window, _event, _sound);
				_menu.button[BBACK].first.setPosition({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10 * 9 });
				_sound.UseSound(BUTTONCLICK);
				//UseSound(BUTTONCLICK);
			}
			buttonHitbox = _menu.button[BQUIT].first.getGlobalBounds();
			if (buttonHitbox.contains(mousePos))
			{
				_window.close();
			}
		}
	}
	else if (_menu.state == TUTORIAL)
	{
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			//Get the mouse pos and button hitbox to check any collision
			sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
			sf::FloatRect buttonHitbox = _menu.button[BBACK].first.getGlobalBounds();
			if (buttonHitbox.contains(mousePos))
			{
				_menu.state = MAIN;
				_sound.UseSound(BUTTONCLICK);
				//UseSound(BUTTONCLICK);
				//We use this function while changing the submenu to check the colision of the button and mouse
				MouseMovedMenu(_menu, _window, _event, _sound);
			}
		}
	}
	else if (_menu.state == CREDIT)
	{
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			//Get the mouse pos and buttons hitbox to check any collision
			sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
			sf::FloatRect buttonHitbox = _menu.button[BBACK].first.getGlobalBounds();
			if (buttonHitbox.contains(mousePos))
			{
				_menu.state = MAIN;
				_sound.UseSound(BUTTONCLICK);
				//UseSound(BUTTONCLICK);
				//We use this function while changing the submenu to check the colision of the button and mouse
				MouseMovedMenu(_menu, _window, _event, _sound);
			}
		}
	}
	else if (_menu.state == OPTION)
	{
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			//Get the mouse pos and buttons hitbox to check any collision
			sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
			sf::FloatRect buttonHitbox = _menu.button[BBACK].first.getGlobalBounds();
			if (buttonHitbox.contains(mousePos))
			{
				_menu.state = MAIN;
				_sound.UseSound(BUTTONCLICK);
				//UseSound(BUTTONCLICK);
				//We use this function while changing the submenu to check the colision of the button and mouse
				MouseMovedMenu(_menu, _window, _event, _sound);
			}

			//Get the slider hitbox
			sf::FloatRect sliderHitbox = _menu.soundSlider.getGlobalBounds();
			if (sliderHitbox.contains(mousePos))
			{
				_menu.soundSliderCursor.setPosition({ mousePos.x, _menu.soundSliderCursor.getPosition().y });

				//Put the cursor in its bound
				sf::Vector2f sliderPos = _menu.soundSliderCursor.getPosition();
				if (sliderPos.x < SCREEN_WIDTH / 2 - SLIDER_SIZE / 2)
				{
					sliderPos.x = SCREEN_WIDTH / 2 - SLIDER_SIZE / 2;
				}
				if (sliderPos.x > SCREEN_WIDTH / 2 + SLIDER_SIZE / 2)
				{
					sliderPos.x = SCREEN_WIDTH / 2 + SLIDER_SIZE / 2;
				}
				_menu.soundSliderCursor.setPosition(sliderPos);

				//Set the volume percentage
				float temp = (sliderPos.x - (SCREEN_WIDTH / 2 - SLIDER_SIZE/2)) / SLIDER_SIZE * 100;
				_sound.SetVolume(temp);
				_sound.UseSound(BUTTONCLICK);
				//UseSound(BUTTONCLICK);
				std::cout << temp << std::endl;
			}
		}
	}
}

void MouseMovedMenu(MenuData& _menu, sf::RenderWindow& _window, sf::Event& _event, Sound& _sound)
{
	//Check which menu are we in
	if (_menu.state == MAIN)
	{
		//Chech the collision between the bouttons and the mouse to highlight them and make them have an animation
		//And if there is no colission we set the buttons to their default state
		sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));

		//I've could have use a for loop to check every button but too late now
		sf::FloatRect buttonHitbox = _menu.button[BPLAY].first.getGlobalBounds();
		if (buttonHitbox.contains(mousePos))
		{
			//Check if the button is already hoverred
			if (_menu.button[BPLAY].second == false)
			{
				_sound.UseSound(BUTTONHOVER);
				//UseSound(BUTTONHOVER);
			}
			_menu.button[BPLAY].first.setColor(sf::Color::Green);
			_menu.button[BPLAY].second = true;
		}
		else
		{
			_menu.button[BPLAY].first.setColor(sf::Color::Color(255, 255, 255, 255));
			_menu.button[BPLAY].second = false;
		}
		buttonHitbox = _menu.button[BTUTORIAL].first.getGlobalBounds();
		if (buttonHitbox.contains(mousePos))
		{
			if (_menu.button[BTUTORIAL].second == false)
			{
				_sound.UseSound(BUTTONHOVER);
				//UseSound(BUTTONHOVER);
			}
			_menu.button[BTUTORIAL].first.setColor(sf::Color::Green);
			_menu.button[BTUTORIAL].second = true;
		}
		else
		{
			_menu.button[BTUTORIAL].first.setColor(sf::Color::Color(255, 255, 255, 255));
			_menu.button[BTUTORIAL].second = false;
		}
		buttonHitbox = _menu.button[BCREDIT].first.getGlobalBounds();
		if (buttonHitbox.contains(mousePos))
		{
			if (_menu.button[BCREDIT].second == false)
			{
				_sound.UseSound(BUTTONHOVER);
				//UseSound(BUTTONHOVER);
			}
			_menu.button[BCREDIT].first.setColor(sf::Color::Green);
			_menu.button[BCREDIT].second = true;
		}
		else
		{
			_menu.button[BCREDIT].first.setColor(sf::Color::Color(255, 255, 255, 255));
			_menu.button[BCREDIT].second = false;
		}
		buttonHitbox = _menu.button[BOPTION].first.getGlobalBounds();
		if (buttonHitbox.contains(mousePos))
		{
			if (_menu.button[BOPTION].second == false)
			{
				_sound.UseSound(BUTTONHOVER);
				//UseSound(BUTTONHOVER);
			}
			_menu.button[BOPTION].first.setColor(sf::Color::Green);
			_menu.button[BOPTION].second = true;
		}
		else
		{
			_menu.button[BOPTION].first.setColor(sf::Color::Color(255, 255, 255, 255));
			_menu.button[BOPTION].second = false;
		}
		buttonHitbox = _menu.button[BQUIT].first.getGlobalBounds();
		if (buttonHitbox.contains(mousePos))
		{
			if (_menu.button[BQUIT].second == false)
			{
				_sound.UseSound(BUTTONHOVER);
				//UseSound(BUTTONHOVER);
			}
			_menu.button[BQUIT].first.setColor(sf::Color::Green);
			_menu.button[BQUIT].second = true;
		}
		else
		{
			_menu.button[BQUIT].first.setColor(sf::Color::Color(255, 255, 255, 255));
			_menu.button[BQUIT].second = false;
		}
	}
	else if (_menu.state == TUTORIAL)
	{
		//Chech the collision between the bouttons and the mouse to highlight them and make them have an animation
		//And if there is no colission we set the buttons to their default state
		sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
		sf::FloatRect buttonHitbox = _menu.button[BBACK].first.getGlobalBounds();
		if (buttonHitbox.contains(mousePos))
		{
			if (_menu.button[BBACK].second == false)
			{
				_sound.UseSound(BUTTONHOVER);
				//UseSound(BUTTONHOVER);
			}
			_menu.button[BBACK].first.setColor(sf::Color::Green);
			_menu.button[BBACK].second = true;
		}
		else
		{
			_menu.button[BBACK].first.setColor(sf::Color::Color(255, 255, 255, 255));
			_menu.button[BBACK].second = false;
		}
	}
	else if (_menu.state == CREDIT)
	{
		//Chech the collision between the bouttons and the mouse to highlight them and make them have an animation
		//And if there is no colission we set the buttons to their default state
		sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
		sf::FloatRect buttonHitbox = _menu.button[BBACK].first.getGlobalBounds();
		if (buttonHitbox.contains(mousePos))
		{
			if (_menu.button[BBACK].second == false)
			{
				_sound.UseSound(BUTTONHOVER);
				//UseSound(BUTTONHOVER);
			}
			_menu.button[BBACK].first.setColor(sf::Color::Green);
			_menu.button[BBACK].second = true;
		}
		else
		{
			_menu.button[BBACK].first.setColor(sf::Color::Color(255, 255, 255, 255));
			_menu.button[BBACK].second = false;

		}
	}
	else if (_menu.state == OPTION)
	{
		//Chech the collision between the bouttons and the mouse to highlight them and make them have an animation
		//And if there is no colission we set the buttons to their default state
		sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
		sf::FloatRect buttonHitbox = _menu.button[BBACK].first.getGlobalBounds();
		if (buttonHitbox.contains(mousePos))
		{
			if (_menu.button[BBACK].second == false)
			{
				_sound.UseSound(BUTTONHOVER);
				//UseSound(BUTTONHOVER);
			}
			_menu.button[BBACK].first.setColor(sf::Color::Green);
			_menu.button[BBACK].second = true;
		}
		else
		{
			_menu.button[BBACK].first.setColor(sf::Color::Color(255, 255, 255, 255));
			_menu.button[BBACK].second = false;
		}
	}
}