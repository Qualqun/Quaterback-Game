#ifndef CARD_STACK_HPP
#define CARD_STACK_HPP

#include "Common.hpp"
#include <list>
#include "Card.hpp"

#define HOVER_Y_DELTA 20
#define MAX_DRAWN_CARDS 4
#define CARDS_PER_LINE 5
#define SPACE_BETWEEN_CARDS_X 20
#define SPACE_BETWEEN_CARDS_Y 10

class CardStack
{
public:
	CardStack();

	void AddCardToStack(Card* _card);
	bool HasCard(Card* _card);
	void RemoveCard(Card* _card);
	void Empty();

	void RenderStack(sf::RenderWindow& _window, sf::Vector2f _position);
	void RenderHiddenStack(sf::RenderWindow& _window, sf::Vector2f _position);
	void RenderVisibleStack(sf::RenderWindow& _window, sf::Vector2f _position);

	bool IsStackHover(sf::RenderWindow& _window, sf::Vector2f _position);

	void ToggleVisibility();

private:
	std::list<Card*> m_cardStack;
	bool m_isCardStackVisible = false;
	Logger m_logger = Logger(std::cout, "CardStack");
};

#endif