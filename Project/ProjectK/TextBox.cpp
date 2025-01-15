#include "TextBox.hpp"

Logger TextBox::m_logger = Logger(std::cout, "TextBox");

TextBox::TextBox()
{
	this->m_text = "";
	this->m_boxSize = sf::IntRect(0, 0, 420, 420);
	this->m_align = Align::LEFT;
	this->m_characterSize = 24;
	this->m_color = &sf::Color::Black;
}

TextBox::TextBox(std::string _text, sf::IntRect _boxSize, unsigned int _characterSize)
{
	this->m_text = _text;
	this->m_boxSize = _boxSize;
	this->m_align = Align::LEFT;
	this->m_characterSize = _characterSize;
	this->m_color = &sf::Color::Black;
}

TextBox::TextBox(TextBox& _copy)
{
	this->m_text = _copy.m_text;
	this->m_boxSize = _copy.m_boxSize;
	this->m_align = _copy.m_align;
	this->m_textLines = _copy.m_textLines;
	this->m_font = _copy.m_font;
	this->m_characterSize = _copy.m_characterSize;
	this->m_color = _copy.m_color;
}

TextBox::~TextBox()
{
	for (sf::Text* text : this->m_textLines)
	{
		delete text;
	}
}

void TextBox::SetFont(sf::Font* _font)
{
	this->m_font = _font;
}

sf::Font* TextBox::GetFont()
{
	return this->m_font;
}

void TextBox::SetColor(const sf::Color& _color)
{
	this->m_color = &_color;
}

std::vector<sf::Text*> TextBox::SplitTextIntoLines()
{
	this->m_textLines.clear();

	std::stringstream stream(m_text);
	std::string currentWord;

	sf::Text tempText;
	sf::Text tempTextAdded;

	tempText.setFont(*this->m_font);
	tempTextAdded.setFont(*this->m_font);
	tempText.setCharacterSize(this->m_characterSize);
	tempTextAdded.setCharacterSize(this->m_characterSize);

	while (stream >> currentWord)
	{
		tempTextAdded.setString(tempText.getString() + " " + currentWord);

		if (tempTextAdded.getGlobalBounds().width >= m_boxSize.width)
		{
			this->m_textLines.push_back(new sf::Text(tempText.getString(), *this->m_font, this->m_characterSize));
			tempText.setString(currentWord + " ");
		}
		else
		{
			tempText.setString(tempTextAdded.getString() + " ");
		}
	}

	this->m_textLines.push_back(new sf::Text(tempText.getString(), *this->m_font, this->m_characterSize));

	for (sf::Text* text : this->m_textLines)
	{
		text->setFillColor(*this->m_color);
	}

	return this->m_textLines;
}

void TextBox::RenderText(sf::RenderTarget& _target, sf::Vector2i _location)
{
	int lineNumber = 0;

	for (sf::Text* text : this->m_textLines)
	{
		text->setPosition(_location.x, _location.y + lineNumber * (text->getCharacterSize() + 6));
		_target.draw(*text);
		lineNumber++;
	}
}