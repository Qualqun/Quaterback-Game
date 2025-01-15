#include "Translator.hpp"
#include "Card.hpp"

Logger Translator::m_logger = Logger(std::cout, "Translator");
std::map<Lang, std::string> Translator::m_registeredLangs = std::map<Lang, std::string>();
Lang Translator::m_currentLang = Lang::ENGLISH;

Translator::Translator(Lang _lang)
{
	ChangeLang(_lang);
}

void Translator::RegisterLang(Lang _lang, std::string _langFile)
{
	m_registeredLangs[_lang] = "assets/langs/" + _langFile + ".json";
}

void Translator::InitTranslator()
{
	RegisterLang(Lang::ENGLISH, "en");
	RegisterLang(Lang::FRENCH, "fr");
}

std::ifstream Translator::GetCurrentIfstream()
{
	return std::ifstream(Translator::m_registeredLangs[Translator::m_currentLang]);
}

bool Translator::ChangeLang(Lang _lang)
{
	m_currentLang = _lang;
	Card::InitCardsRender();
	return true;
}

std::string Translator::GetTranslation(std::string _key)
{
	Json::Reader reader;
	Json::Value root;
	std::ifstream stream = Translator::GetCurrentIfstream();

	reader.parse(stream, root);

	if (root[_key].isNull())
	{
		Translator::m_logger.Error("Missing translation \"" + _key + "\"");
		return "[no text]";
	}

	return root[_key].asString();
}