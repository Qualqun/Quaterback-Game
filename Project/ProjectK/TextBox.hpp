#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "Common.hpp"
#include <sstream>
#include <vector>
#include "Logger.hpp"

enum Align
{
	LEFT, CENTER, RIGHT
};

class TextBox
{
protected:
	std::string m_text;
	sf::IntRect m_boxSize;
	Align m_align;
	unsigned int m_characterSize;
	std::vector<sf::Text*> m_textLines;
	sf::Font* m_font;
	const sf::Color* m_color;
	static Logger m_logger;

public:
	TextBox();
	~TextBox();
	TextBox(std::string _text, sf::IntRect _boxSize, unsigned int _characterSize);
	TextBox(TextBox& _copy);

	// Splits the full text into multiple sf::Text objects so that the overall width fits into the desired size
	std::vector<sf::Text*> SplitTextIntoLines();

	// Renders the text to a target (RenderWindow or RenderTexture)
	void RenderText(sf::RenderTarget& _target, sf::Vector2i _location);

	void SetFont(sf::Font* _font);
	sf::Font* GetFont();
	void SetColor(const sf::Color& _color);
};

#endif