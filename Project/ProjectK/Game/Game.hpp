#ifndef GAME_HPP
#define GAME_HPP

#include "../Utilities/Utilities.hpp"
#include "HUD.hpp"
#include "Grid.hpp"
#include "../Menu.hpp"
#include "../Card.hpp"
#include "../FontManager.hpp"
#include "../Translator.hpp"
#include "../Player.hpp"
#include "../Token.hpp"
#include "../Particles.hpp"
#include "../Camera.hpp"
#include "../Sound.hpp"

enum Units
{
	NORMAL,
	AILLIER,
	TANK,
	QUATTERBACK,
	NUMBER_UNITS,
};

enum Time
{
	MINUTES,
	SECONDS,
};

enum Frames
{
	BACK,
	FRONT
};

class GameData
{
	private :
		HudData* m_hudData = nullptr;
		GridData* m_grid = nullptr;
		Player* m_players = nullptr;
		CameraData* m_camera = nullptr;
		Sound* m_sound = nullptr;

		ParticleManager* m_particleManager = nullptr;
		std::vector<Token> m_token;


		sf::Sprite m_background;
		sf::Sprite m_units1[6];
		sf::Sprite m_units2[6];
		Limit m_limit;
		Role m_unitSelect;

		static GameData* _SINGLETON;

		int m_turn;

		GameData();

	public :
		~GameData();

#pragma region Lifecycle
		static GameData* GetInstance();
		void Update(sf::RenderWindow& _window, float& _dt);
		void Draw(sf::RenderWindow& _window);
#pragma endregion

#pragma region Inputs
		void MouseMoved(sf::RenderWindow& _window, sf::Event& _event);
		void MouseWheelScrolled(sf::RenderWindow& _window, sf::Event& _event);
		void KeyPressed(sf::Event& _event);
		void KeyReleased(sf::Event& _event);
		void MousePressed(sf::RenderWindow& _window, sf::Event& _event, Sound& _sound);


#pragma endregion

#pragma region Setters
		void IncrementTurn();
		void AddToken(Token _token) { m_token.push_back(_token); }
		void SetRole(Role _role) { m_unitSelect = _role; }
#pragma endregion

#pragma region Getters
		HudData* GetHudData();
		GridData* GetGridData();
		ParticleManager* GetParticleManager();
		Player* GetPlayer1();
		Player* GetPlayer2();
		CameraData* GetCameraData();
		Sound* GetSoundData();
		sf::Sprite GetBackground();
		int GetTurn();
		Role GetRoleSelect() { return m_unitSelect; }

		// Returns the player whose turn it is
		Player* GetPlayerFromTurn();

		// Returns the other player
		Player* GetOtherPlayer(Player* _player);
#pragma endregion
};
#endif // !GA%E_H


