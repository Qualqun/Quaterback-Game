#include "Utilities.hpp"

sf::Sprite LoadSprite(const std::string _path, bool _isCentered)
{
    //Création et chargement de la texture
    sf::Texture* tempTex = new sf::Texture(); //Nécessaire dynamiquement
    tempTex->loadFromFile(_path);

    //Création et configuration du sprite
    sf::Sprite tempSprite;
    tempSprite.setTexture(*tempTex);

    if (_isCentered) //Centrage du sprite
    {
        sf::Vector2u tempTaille = tempTex->getSize();
        sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x / 2.f, tempTaille.y / 2.f);
        tempSprite.setOrigin(tempOrigin);
    }

    return tempSprite;
}

void BlitSprite(sf::Sprite& _sprite, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window)
{
    _sprite.setRotation(_angle);
    _sprite.setPosition(_pos);
    _window.draw(_sprite);
}
void BlitSprite(sf::Sprite& _sprite, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window, sf::Vector2f _scale)
{
    _sprite.setScale(_scale);
    _sprite.setRotation(_angle);
    _sprite.setPosition(_pos);
    _window.draw(_sprite);
}
extern double Lerp(double _min, double _max, double _index)
{
    return (_max - _min) * _index + _min;
}

extern double Corp(double _min, double _max, double _index)
{
    return (_max - _min) * ((1. - std::cos(M_PI * _index)) / 2.) + _min;
}

extern double Clamp(double _min, double _max, double _value)
{
    return std::min(std::max(_value, _min), _max);
}

extern bool IsHovered(const sf::FloatRect& _rect, sf::RenderWindow& _window)
{
    sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
    return _rect.contains(mousePos.x, mousePos.y);
}

extern int RandIntInRange(int _min, int _max)
{
    return rand() % (_max - _min + 1) + _min;
}