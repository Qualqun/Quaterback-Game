#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#include "Common.hpp"
#include "Logger.hpp"

class FontManager
{
private:
	static std::map<std::string, sf::Font*> m_fonts;
	static Logger m_logger;

	static void RegisterFont(std::string _file, std::string _name);

public:
	static void InitFonts();
	static sf::Font* GetFont(std::string _name);
};

#endif