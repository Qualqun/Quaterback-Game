#include "Camera.hpp"

void InitCamera(CameraData& _camera)
{

}

void UpdateCamera(CameraData& _camera, float _dt)
{
	//Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		_camera.MoveCamera({ 0,-CAMERA_SPEED * _dt });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		_camera.MoveCamera({ 0,CAMERA_SPEED * _dt });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		_camera.MoveCamera({ -CAMERA_SPEED * _dt ,0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		_camera.MoveCamera({ CAMERA_SPEED * _dt ,0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageUp))
	{
		_camera.SetZoom(1.05);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageDown))
	{
		_camera.SetZoom(0.95);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		_camera.MoveCamera((sf::Vector2f)_camera.oldMousePos - (sf::Vector2f)mousePos);
		_camera.oldMousePos = mousePos;
	}

	//Check if the camera go outsize of the playable zone
	sf::Vector2f camSize = _camera.GetCamera().getSize();
	if (camSize.x > CAMERA_X_MAX)
	{
		sf::View newCam = _camera.GetCamera();
		newCam.setSize(CAMERA_X_MAX, newCam.getSize().y);
		_camera.SetCamera(newCam);
	}
	if (camSize.y > CAMERA_Y_MAX)
	{
		sf::View newCam = _camera.GetCamera();
		newCam.setSize(newCam.getSize().x, CAMERA_Y_MAX);
		_camera.SetCamera(newCam);
	}
	//Check if the camera get to small
	if (camSize.x < CAMERA_X_MIN)
	{
		sf::View newCam = _camera.GetCamera();
		newCam.setSize(CAMERA_X_MIN, newCam.getSize().y);
		_camera.SetCamera(newCam);
	}
	if (camSize.y < CAMERA_Y_MIN)
	{
		sf::View newCam = _camera.GetCamera();
		newCam.setSize(newCam.getSize().x, CAMERA_Y_MIN);
		_camera.SetCamera(newCam);
	}


	//Get the new size in case it was adjusted before
	camSize = _camera.GetCamera().getSize();
	//std::cout << "x : " << camSize.x << "	" << "y : " << camSize.y << std::endl;
	sf::Vector2f camCenter = _camera.GetCamera().getCenter();
	if (camCenter.x - camSize.x / 2 < 0)
	{
		sf::View newCam = _camera.GetCamera();
		newCam.move({ 0 - (camCenter.x - camSize.x / 2) ,0.f });
		_camera.SetCamera(newCam);
	}
	if (camCenter.x + camSize.x / 2 > CAMERA_X_MAX)
	{
		sf::View newCam = _camera.GetCamera();
		newCam.move({ 2560.f - (camCenter.x + camSize.x / 2) ,0.f });
		_camera.SetCamera(newCam);
	}
	if (camCenter.y - camSize.y / 2 < 0)
	{
		sf::View newCam = _camera.GetCamera();
		newCam.move({ 0.f ,0 - (camCenter.y - camSize.y / 2) });
		_camera.SetCamera(newCam);
	}
	if (camCenter.y + camSize.y / 2 > CAMERA_Y_MAX)
	{
		sf::View newCam = _camera.GetCamera();
		newCam.move({ 0.f,1440.f - (camCenter.y + camSize.y / 2) });
		_camera.SetCamera(newCam);
	}

}

void CameraData::MouseWheelScrolledCamera(sf::RenderWindow& _window, sf::Event& _event)
{
	if (_event.type == sf::Event::MouseWheelScrolled)
	{
		if (_event.mouseWheelScroll.delta < 0)
		{
			camera.zoom(1.05);
		}
		else if (_event.mouseWheelScroll.delta > 0)
		{
			camera.zoom(0.95);
		}
	}
}

CameraData::CameraData()
{
	camera.setSize({ SCREEN_WIDTH , SCREEN_HEIGHT });
	camera.setCenter({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
};

sf::Vector2f CameraData::GetOffset()
{
	sf::Vector2f camCenter = camera.getCenter();
	sf::Vector2f camSize = camera.getSize();
	sf::Vector2f camOffset = camCenter - sf::Vector2f{ camSize.x / 2, camSize.y / 2 };
	return camOffset;
}

sf::Vector2f CameraData::GetScale()
{
	sf::Vector2f camSize = camera.getSize();
	return sf::Vector2f{ camSize.x / SCREEN_WIDTH, camSize.y / SCREEN_HEIGHT };
}

void CameraData::SetCameraGame()
{
	camera.setSize({ SCREEN_WIDTH * 1.25 , SCREEN_HEIGHT * 1.25 });
	camera.setCenter({ CAMERA_X_MAX / 2, CAMERA_Y_MAX / 2 });
}

void CameraData::SetCameraMenu()
{
	camera.setSize({ SCREEN_WIDTH , SCREEN_HEIGHT });
	camera.setCenter({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
}