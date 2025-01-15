#include "CardStack.hpp"
#include "Game/Game.hpp"

CardStack::CardStack()
{

}

void CardStack::AddCardToStack(Card* _card)
{
	m_cardStack.push_back(_card);
}

bool CardStack::HasCard(Card* _card)
{
	const auto& pos = std::find(m_cardStack.cbegin(), m_cardStack.cend(), _card);

	if (pos != m_cardStack.cend())
	{
		return true;
	}

	return false;
}

void CardStack::RemoveCard(Card* _card)
{
	const auto& pos = std::find(m_cardStack.cbegin(), m_cardStack.cend(), _card);

	if (pos != m_cardStack.cend())
	{
		m_cardStack.erase(pos);
	}
}

void CardStack::Empty()
{
	m_cardStack.clear();
}

void CardStack::RenderStack(sf::RenderWindow& _window, sf::Vector2f _position)
{
	if (!this->m_isCardStackVisible)
	{
		this->RenderHiddenStack(_window, _position);
	}
	else
	{
		this->RenderVisibleStack(_window, _position);
	}
}

void CardStack::RenderHiddenStack(sf::RenderWindow& _window, sf::Vector2f _position)
{
	sf::Sprite sprite;
	sf::Sprite spriteIcon;
	sprite.setTexture(*Card::_CARD_BACK);
	sprite.setOrigin(Card::_CARD_BACK->getSize().x / 2, Card::_CARD_BACK->getSize().y / 2);
	spriteIcon.setTexture(*Card::_CARD_BACK_ICON);
	spriteIcon.setOrigin(Card::_CARD_BACK_ICON->getSize().x / 2, Card::_CARD_BACK_ICON->getSize().y / 2);

	if (m_cardStack.size() > MAX_DRAWN_CARDS)
	{
		for (int i = 0; i < 4; i++)
		{
			sprite.setPosition(_position.x + i * 10, _position.y - (IsStackHover(_window, _position) ? HOVER_Y_DELTA : 0));
			_window.draw(sprite);
		}

		sf::Text nbrCard = sf::Text(std::to_string(m_cardStack.size()), *FontManager::GetFont("Hyper Super Regular"), 95);
		nbrCard.setPosition(_position.x, _position.y - 150 - (IsStackHover(_window, _position) ? HOVER_Y_DELTA : 0));
		_window.draw(nbrCard);

		return;
	}

	for (int i = 0; i < m_cardStack.size(); i++)
	{
		sprite.setRotation(-5 * (std::floor((m_cardStack.size() / 2.f) - i)));
		spriteIcon.setRotation(-5 * (std::floor((m_cardStack.size() / 2.f) - i)));
		sprite.setPosition(_position.x + i * 15, _position.y - (IsStackHover(_window, _position) ? HOVER_Y_DELTA : 0));
		spriteIcon.setPosition(_position.x + i * 15, _position.y - (IsStackHover(_window, _position) ? HOVER_Y_DELTA : 0));

		_window.draw(sprite);
		_window.draw(spriteIcon);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && IsStackHover(_window, _position))
	{
		this->ToggleVisibility();
	}
}

void CardStack::RenderVisibleStack(sf::RenderWindow& _window, sf::Vector2f _position)
{
	int lineNbr = std::ceil(m_cardStack.size() / (float)CARDS_PER_LINE);
	float totalCardsHeight = (CARD_HEIGHT + (lineNbr > 1 ? SPACE_BETWEEN_CARDS_Y : 0)) * (lineNbr - 1);

	sf::Sprite sprite;

	for (int i = 0; i < lineNbr; i++)
	{
		int cardsOnThisLine = std::min(((int)m_cardStack.size() - i * CARDS_PER_LINE), CARDS_PER_LINE);
		float totalLineWidth = (CARD_WIDTH + (cardsOnThisLine > 1 ? SPACE_BETWEEN_CARDS_X : 0)) * (cardsOnThisLine - 1);

		for (int j = 0; j < cardsOnThisLine; j++)
		{
			std::list<Card*>::iterator it = m_cardStack.begin();
			std::advance(it, i * CARDS_PER_LINE + j);
			Card* card = *it;

			CameraData* camera = GameData::GetInstance()->GetCameraData();

			float cardPosX = camera->GetCamera().getSize().x / 2 - totalLineWidth / 2 + j * (CARD_WIDTH + SPACE_BETWEEN_CARDS_X);
			float cardPosY = camera->GetCamera().getSize().y / 2 - totalCardsHeight / 2 + i * (CARD_HEIGHT + SPACE_BETWEEN_CARDS_Y);

			card->RenderCard(_window, sprite, sf::Vector2f(cardPosX + camera->GetOffset().x, cardPosY + camera->GetOffset().y));
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->ToggleVisibility();
	}
}

bool CardStack::IsStackHover(sf::RenderWindow& _window, sf::Vector2f _position)
{
	sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));

	CameraData* camera = GameData::GetInstance()->GetCameraData();

	return mousePos.x >= (_position.x - (CARD_WIDTH * camera->GetScale().x) / 2) &&
		mousePos.x <= (_position.x + (m_cardStack.size() > 4 ? 24 : m_cardStack.size() * 15) + (CARD_WIDTH * camera->GetScale().x) / 2) &&
		mousePos.y >= (_position.y - (CARD_HEIGHT * camera->GetScale().y) / 2) &&
		mousePos.y <= (_position.y + (CARD_HEIGHT * camera->GetScale().y) / 2);
}

void CardStack::ToggleVisibility()
{
	this->m_isCardStackVisible = !this->m_isCardStackVisible;
}