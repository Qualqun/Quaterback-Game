#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "Common.hpp"

struct Anim
{
	sf::Vector2i texRect = { 0,0 };
	unsigned int offset = 0;
	unsigned int framerate = 0;
	unsigned int frameNb = 0;
	bool isLooping = false;
	float timeAnim = 0;
};

Anim InitAnimation(sf::Vector2i _textureRect, const unsigned int _framerate, const unsigned int _frameNb, const unsigned int _offsetY, const bool _isLooping);
void Animation(sf::Sprite& _sprite, Anim* _anim, const unsigned int _state, const float _dt);
#endif