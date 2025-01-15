#include "FontManager.hpp"

std::map<std::string, sf::Font*> FontManager::m_fonts = std::map<std::string, sf::Font*>();
Logger FontManager::m_logger = Logger(std::cout, "FontManager");

void FontManager::RegisterFont(std::string _file, std::string _name)
{
	sf::Font* font = new sf::Font;

	if (font->loadFromFile("assets/fonts/" + _file))
	{
		m_logger.Success("Loaded font : " + _name);
	}
	else
	{
		m_logger.Error("Couldn't load font : " + _name);
		delete font;
		return;
	}

	FontManager::m_fonts[_name] = font;
}

sf::Font* FontManager::GetFont(std::string _name)
{
	sf::Font* font = FontManager::m_fonts[_name];

	if (font == nullptr)
	{
		FontManager::m_logger.Warning("You are trying to get an unknown font -> " + _name);
	}

	return font;
}

void FontManager::InitFonts()
{
	FontManager::RegisterFont("LTCushion-Medium.ttf", "Cushion Medium");
	FontManager::RegisterFont("LTCushion-Light.ttf", "Cushion Light");
	FontManager::RegisterFont("LTCushion-Bold.ttf", "Cushion Bold");
	FontManager::RegisterFont("HyperSuperRegular.ttf", "Hyper Super Regular");

	m_logger.Debug(std::to_string(m_fonts.size()) + " loaded fonts");
}