#include "Animation.hpp"

void Animation(sf::Sprite& _sprite, Anim* _anim, const unsigned int _state, const float _dt)
{
	_anim->timeAnim += _dt;
	float frameTime = 1.f / _anim[_state].framerate;
	int frameNb = _anim->timeAnim / frameTime;
	int heightSum = 0;
	if (_anim->timeAnim > frameTime * frameNb)
	{
		if (frameNb > _anim[_state].frameNb - 1)
		{
			frameNb = _anim[_state].frameNb - 1;
		}
		for (int i = 0; i < _state; i++)
		{
			heightSum += _anim[i].texRect.y;
		}
		for (int i = 0; i <= _state; i++)
		{
			heightSum += _anim[i].offset;
		}
		sf::IntRect textureRect = { _anim[_state].texRect.x * frameNb, heightSum, _anim[_state].texRect.x, _anim[_state].texRect.y};
		_sprite.setTextureRect(textureRect);
		if (_anim[_state].isLooping == true && _anim->timeAnim > frameTime * _anim[_state].frameNb && frameNb == _anim[_state].frameNb - 1)
		{
			_anim->timeAnim = 0;
		}
	}
}

Anim InitAnimation(sf::Vector2i _textureRect, const unsigned int _framerate, const unsigned int _frameNb, const unsigned int _offsetY, const bool _isLooping)
{
	Anim anim;
	anim.texRect = _textureRect;
	anim.framerate = _framerate;
	anim.frameNb = _frameNb;
	anim.offset = _offsetY;
	anim.isLooping = _isLooping;
	anim.timeAnim = 0;
	return anim;
}