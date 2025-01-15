#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Logger.hpp"
#include "Utilities/Utilities.hpp"
#include "FontManager.hpp"
#include "TextBox.hpp"
#include "Translator.hpp"

#include <functional>

#define CARD_WIDTH 300
#define CARD_HEIGHT 500
#define CARD_TYPE_WIDTH 300
#define CARD_TYPE_HEIGHT 500

class Player;
class Unit;

class Card
{
protected:
	std::string m_name;
	sf::Texture m_iconTexture;
	sf::Texture m_backgroundTexture;
	sf::RenderTexture m_renderTexture;
	TextBox m_textBox;
	std::function<bool(Player&, Unit&)> m_activeFunction;
	bool m_needsUnitTarget;
	static Logger _LOGGER;

	Card(std::string _name, std::function<bool(Player&, Unit&)> _func);
	Card(std::string _name, std::function<bool(Player&, Unit&)> _func, bool _needsUnit);

	void CreateRenderTexture();

public:
	static Card* _SHIELD;
	/*static Card* _KNOCKBACK;
	static Card* _GRAB;*/
	static Card* _ADD_AP;
	static Card* _HEAL;

	static sf::Texture* _CARD_BACK;
	static sf::Texture* _CARD_BACK_ICON;

	~Card();

	bool OnActive(Player&, Unit&);

	// Called during the loading of the game, initializes the RenderTexture
	static void InitCardsRender();

	static Card* GetRandomCard();

	// Binds the card texture to a Sprite reference, ready to be draw on screen
	void BindTexture(sf::Sprite&);

	// Render the card to the screen at the coordinates specified
	void RenderCard(sf::RenderWindow& _window, sf::Sprite& _sprite, sf::Vector2f _coords, bool _centered = true);

	inline std::string GetName() const { return m_name; }
};

#endif