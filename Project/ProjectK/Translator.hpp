#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <iostream>
#include <json/json.h>
#include "Logger.hpp"
#include <fstream>

enum Lang
{
	ENGLISH, FRENCH
};

class Translator
{
private:
	static std::map<Lang, std::string> m_registeredLangs;
	static Lang m_currentLang;
	static Logger m_logger;

	static std::ifstream GetCurrentIfstream();
	static void RegisterLang(Lang _lang, std::string _langFile);
public:
	Translator(Lang _lang);

	static bool ChangeLang(Lang _lang);
	static std::string GetTranslation(std::string _key);
	static void InitTranslator();
};

#endif