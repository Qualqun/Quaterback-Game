#ifndef CAMERA_HPP
#define CAMERA_HPP


#include "Common.hpp"

#define CAMERA_SPEED 300.f
#define CAMERA_X_MAX 2560
#define CAMERA_Y_MAX 1440
#define CAMERA_X_MIN 1280
#define CAMERA_Y_MIN 720


class CameraData
{
private:
	sf::View camera;

public:
	sf::Vector2i oldMousePos;

	CameraData() ;
	~CameraData() {};

	void SetCamera(sf::View _camera) { camera = _camera; }
	sf::View GetCamera() const { return camera; }
	void SetCameraGame();
	void SetCameraMenu();

	void MoveCamera(sf::Vector2f _pos) { camera.move(_pos); }
	void SetZoom(float _zoom) { camera.zoom(_zoom); }
	
	sf::Vector2f GetOffset();
	sf::Vector2f GetScale();

	void MouseWheelScrolledCamera(sf::RenderWindow& _window, sf::Event& _event);
};

void UpdateCamera(CameraData& _camera, float _dt);



#endif