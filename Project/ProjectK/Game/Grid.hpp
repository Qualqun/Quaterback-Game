#ifndef GRID_HPP
#define GRID_HPP

#include "../Common.hpp"
#include "../Utilities/Utilities.hpp"

#define OFFSET_X ((SCREEN_WIDTH/2.f) + 750.f )
#define OFFSET_Y 130.f

#define NB_LINE 7
#define NB_COLUMN 16

enum PlayZone
{
	TOUCHDOWN_ENEMY,
	SPAWN_ENEMY,
	NEUTRAL,
	SPAWN_SELF,
	TOUCHDOWN_SELF
};

class GridData
{
private:

	struct Cell
	{
		sf::Sprite* m_sprite{ nullptr };
		bool* m_isOccupied{ nullptr };
	};

	sf::Texture* m_tex{ nullptr };
	Cell** m_cell{ nullptr };
	int m_nbClic = 0;
	bool m_isClicked = true;
	int m_pathFollowingIndex = 0;

	static bool m_isPathfindingEnabled;
	static bool m_allowDiagonal;
	std::vector<sf::Vector2i> m_oldPath;
	static sf::Vector2i m_start;
	static sf::Vector2i m_end;
protected:
	sf::Texture* GetGridTexture() const { return m_tex; }
	std::vector<sf::Vector2i> BFS(const sf::Vector2i& _start, const sf::Vector2i& _end, const int& _mana);
	std::vector<sf::Vector2i> BFSDiagonal(sf::Vector2i _start, sf::Vector2i _end, const int& _mana);
	void CleanPath(sf::Vector2i _start, sf::Vector2i _end);

	void HandleCellsHovering(sf::Vector2f mousePosition);

public:

#pragma region constructors
	//Default constructor
	GridData();
	//Copy constructor
	GridData(const GridData& _source); //by reference of lvalue
	//Move constructor
	GridData(GridData&& _source) noexcept; //by reference of rvalue
	//Deconstructor    
	~GridData();
#pragma endregion

	void LoadGrid(void);
	void UdpateGrid(void);
	void DrawGrid(sf::RenderWindow& _window);

	void MousePressedGrid(sf::Vector2i mousePosition);
	void MouseMovedGrid(sf::Vector2f mousePosition, const int& _mana);
	void UpdateCellColors(const std::vector<sf::Vector2i>& path, const int& _mana);

#pragma region getters
	bool IsCellOccupied(int lineID, int columnID);
	Cell** GetCell() const { return m_cell; }
	int GetZoneOnMap(sf::Vector2i _coord);
	std::vector<sf::Vector2i> GetOldPath() { return m_oldPath ;};
	static sf::Vector2i GetStartPoint() { return m_start; };
	static sf::Vector2i GetEndPoint() { return m_end; };
	static bool isPathfindingOn() { return m_isPathfindingEnabled; };
	static sf::Vector2f Screen2World(sf::Vector2f _screenPos);
	static sf::Vector2f World2Screen(float _x, float _y, float _z);

#pragma endregion

#pragma region setters
	//Setters
	void SetIsOccupied(int lineID, int columnID, const bool& isOccupied);
	void SetIsClicked(bool _isClick) { m_isClicked = _isClick; };
	static void SetIsPathfindingEnabled(bool _set) { m_isPathfindingEnabled = _set; }
	static void SetPathfindingMethod(bool _set) { m_allowDiagonal = _set; }
#pragma endregion
};

#endif // !GRID_HPP
