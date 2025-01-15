#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "../Common.hpp"

sf::Sprite LoadSprite(const std::string _path, bool _isCentered);
void BlitSprite(sf::Sprite& _sprite, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window);
void BlitSprite(sf::Sprite& _sprite, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window, sf::Vector2f _scale);

/* Interpolates linearly index between min and max
   index -> must be on [0;1] */
double Lerp(double _min, double _max, double _index);

/* Cosinusoid interpolation between min and max
   index -> must be on [0;1] */
double Corp(double _min, double _max, double _index);

// Returns the value passed as a parameter on the [min;max] interval
double Clamp(double _min, double _max, double _value);

// Allows to know if the mouse is contained within a given rectangle
bool IsHovered(const sf::FloatRect& _rect, sf::RenderWindow& _window);

// Returns a random integer between in [min;max]
int RandIntInRange(int _min, int _max);

#endif // !UTILITIES_H
