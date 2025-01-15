#include "Card.hpp"
#include "Unit.hpp"
#include "Player.hpp"
#include "HealParticle.hpp"
#include "Game/Game.hpp"
#include "ShieldParticle.hpp"

Logger Card::_LOGGER = Logger(std::cout, "Cards");

Card* Card::_SHIELD = new Card("shield", [](Player& _player, Unit& _unit)
	{
		if (_unit.HasShield())
		{
			return false;
		}

		GameData::GetInstance()->GetParticleManager()->AddParticle(new ShieldParticle(GridData::World2Screen(_unit.GetPos().x, _unit.GetPos().y, 0)));
		_unit.AddShield(); 
		return true;
	});
//Card* Card::_KNOCKBACK = new Card("push", [](Player& _player, Unit& _unit) { return true; });
//Card* Card::_GRAB = new Card("grab", [](Player& _player, Unit& _unit) { return true; });
Card* Card::_ADD_AP = new Card("addap", [](Player& _player, Unit& _unit) 
	{ 
		_player.SetMana(_player.GetMana() + 1);
		return true;
	}, false);

Card* Card::_HEAL = new Card("heal", [](Player& _player, Unit& _unit)
	{
		GameData::GetInstance()->GetParticleManager()->AddParticle(new HealParticle(GridData::World2Screen(_unit.GetPos().x, _unit.GetPos().y, 0), 2));
		_unit.Heal(2);
		return true;
	});

sf::Texture* Card::_CARD_BACK = new sf::Texture;
sf::Texture* Card::_CARD_BACK_ICON = new sf::Texture;

Card::Card(std::string _name, std::function<bool(Player&, Unit&)> _func)
{
	this->m_name = _name;
	this->m_iconTexture.loadFromFile("assets/textures/card_" + _name + "_icon.png");
	this->m_backgroundTexture.loadFromFile("assets/textures/card_" + _name + ".png");
	this->m_activeFunction = _func;
	this->m_needsUnitTarget = true;

	Card::_LOGGER.Success("Card " + _name + " created");
}

Card::Card(std::string _name, std::function<bool(Player&, Unit&)> _func, bool _needsUnit)
{
	this->m_name = _name;
	this->m_iconTexture.loadFromFile("assets/textures/card_" + _name + "_icon.png");
	this->m_backgroundTexture.loadFromFile("assets/textures/card_" + _name + ".png");
	this->m_activeFunction = _func;
	this->m_needsUnitTarget = _needsUnit;

	Card::_LOGGER.Success("Card " + _name + " created");
}

Card::~Card()
{

}

//void Card::AddCardToPlayer(Player& _player)
//{
//	_player.cardStack->AddCardToStack(this);
//}

bool Card::OnActive(Player& _player, Unit& _unit)
{
	return this->m_activeFunction(_player, _unit);
}

void Card::CreateRenderTexture()
{
	sf::Sprite sprite;
	sf::ContextSettings settings;

	this->m_renderTexture.create(CARD_WIDTH, CARD_HEIGHT, settings);
	this->m_renderTexture.clear(sf::Color::Transparent);

	sprite.setTextureRect(sf::IntRect(0, 0, CARD_WIDTH, CARD_HEIGHT));
	sprite.setTexture(this->m_backgroundTexture);
	sprite.setPosition(0, 0);
	this->m_renderTexture.draw(sprite);

	sprite.setTextureRect(sf::IntRect(0, 0, CARD_TYPE_WIDTH, CARD_TYPE_HEIGHT));
	sprite.setTexture(this->m_iconTexture);
	sprite.setPosition(0, 0);
	this->m_renderTexture.draw(sprite);

	sf::Text cardName(Translator::GetTranslation("card." + this->m_name + ".name"), *FontManager::GetFont("Hyper Super Regular"), 35);
	cardName.setPosition(32, 332);
	cardName.setFillColor(sf::Color::White);
	this->m_renderTexture.draw(cardName);

	this->m_textBox = TextBox(Translator::GetTranslation("card." + this->m_name + ".summary"), sf::IntRect(0, 0, 261, 96), 25);
	this->m_textBox.SetFont(FontManager::GetFont("Hyper Super Regular"));
	this->m_textBox.SetColor(sf::Color::White);
	this->m_textBox.SplitTextIntoLines();
	this->m_textBox.RenderText(this->m_renderTexture, sf::Vector2i(24, 385));

	this->_LOGGER.Success("Created the RenderTexture for " + this->m_name);
}

void Card::BindTexture(sf::Sprite& _sprite)
{
	this->m_renderTexture.display();
	_sprite.setTexture(this->m_renderTexture.getTexture());
}

void Card::RenderCard(sf::RenderWindow& _window, sf::Sprite& _sprite, sf::Vector2f _coords, bool _centered)
{
	this->BindTexture(_sprite);
	_sprite.setPosition(_coords);

	if (_centered)
	{
		_sprite.setOrigin(CARD_WIDTH / 2, CARD_HEIGHT / 2);
	}

	CameraData* camera = GameData::GetInstance()->GetCameraData();

	sf::FloatRect cardRect = sf::FloatRect(_coords.x - (CARD_WIDTH * camera->GetScale().x) / 2, _coords.y - (CARD_HEIGHT * camera->GetScale().y) / 2, CARD_WIDTH * camera->GetScale().x, CARD_HEIGHT * camera->GetScale().y);

	if (IsHovered(_sprite.getGlobalBounds(), _window))
	{
		_sprite.setScale(1.05f, 1.05f);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->m_needsUnitTarget)
			{
				GameData::GetInstance()->GetPlayerFromTurn()->ApplyCard(this);
			}
			else
			{
				GameData::GetInstance()->GetPlayerFromTurn()->GetCardStack()->RemoveCard(this);
				this->OnActive(*GameData::GetInstance()->GetPlayerFromTurn(), *(Unit*)nullptr);
			}

			GameData::GetInstance()->GetPlayerFromTurn()->GetCardStack()->ToggleVisibility();
		}
	}

	_window.draw(_sprite);
	_sprite.setScale(1.f, 1.f);
}

Card* Card::GetRandomCard()
{
	int random = rand() % 3;

	switch (random)
	{
	case 0:
		return Card::_SHIELD;
	case 1:
		return Card::_ADD_AP;
	case 2:
		return Card::_HEAL;
	default:
		return Card::_SHIELD;
	}
}

void Card::InitCardsRender()
{
	Card::_CARD_BACK_ICON->loadFromFile("assets/textures/card_back_icon.png");
	Card::_CARD_BACK->loadFromFile("assets/textures/card_back.png");
	Card::_SHIELD->CreateRenderTexture();
	/*Card::_KNOCKBACK->CreateRenderTexture();
	Card::_GRAB->CreateRenderTexture();*/
	Card::_ADD_AP->CreateRenderTexture();
	Card::_HEAL->CreateRenderTexture();
}