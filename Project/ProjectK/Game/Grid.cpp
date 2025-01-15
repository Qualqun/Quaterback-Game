#include "Grid.hpp"
#include <queue>
#include <tuple>
#include <deque>
#include <array>

#pragma region defines

#define REC_WIDTH 85
#define REC_HEIGHT 50


#define TILE_WIDTH 210
#define TILE_HEIGHT 122
#define TILE_MAX_HEIGHT 0.3

#define TOUCHDOWN_ENEMY_CELL 0
#define SPAWN_ENEMY_MIN 1
#define SPAWN_ENEMY_MAX 4
#define NEUTRAL_MIN 4
#define NEUTRAL_MAX NB_COLUMN - 5
#define SPAWN_SELF_MIN NB_COLUMN - 4
#define SPAWN_SELF_MAX NB_COLUMN - 1
#define TOUCHDOWN_SELF_CELL NB_COLUMN - 1


#pragma endregion

#pragma region enums

enum DirTypes
{
	NONE,
	LEFT = -1,
	RIGHT = 1,
	DOWN = -1,
	UP = 1
};
#pragma endregion

//Change ici HEDI mon petit bout de kiri
bool GridData::m_isPathfindingEnabled = false;
bool GridData::m_allowDiagonal = true;
sf::Vector2i GridData::m_start = { -1,-1 };
sf::Vector2i GridData::m_end = { -1,-1 };

#pragma region localFunctions


void GridCellLiftUp(sf::Sprite& _sprite)
{
	_sprite.setPosition(sf::Vector2f{ _sprite.getPosition().x, _sprite.getPosition().y - 10 });
}
void GridCellLiftDown(sf::Sprite& _sprite)
{
	_sprite.setPosition(sf::Vector2f{ _sprite.getPosition().x, _sprite.getPosition().y + 10 });
}

void GridData::HandleCellsHovering(sf::Vector2f _currentCell)
{
	static sf::Vector2i previousCell = { -1, -1 };

	bool needReset = _currentCell.x < 0 || _currentCell.x >= NB_LINE || _currentCell.y < 0 || _currentCell.y >= NB_COLUMN;
	bool coordinatesChanged = _currentCell.x != previousCell.x || _currentCell.y != previousCell.y;
	bool previousCellInBounds = previousCell.x >= 0 && previousCell.x < NB_LINE && previousCell.y >= 0 && previousCell.y < NB_COLUMN;

	if (needReset || coordinatesChanged)
	{
		if (previousCellInBounds && !(previousCell == m_start))
		{
			m_cell[previousCell.x][previousCell.y].m_sprite->setColor(sf::Color::White);
			GridCellLiftDown(*m_cell[previousCell.x][previousCell.y].m_sprite);
		}
		else if (previousCellInBounds)
		{
			GridCellLiftDown(*m_cell[previousCell.x][previousCell.y].m_sprite);
			m_cell[(int)previousCell.x][(int)previousCell.y].m_sprite->setColor(sf::Color::White);
		}
		if (needReset)
		{
			previousCell = { -1, -1 };
		}
		else
		{
			m_cell[(int)_currentCell.x][(int)_currentCell.y].m_sprite->setColor(sf::Color::Magenta);
			GridCellLiftUp(*m_cell[(int)_currentCell.x][(int)_currentCell.y].m_sprite);
			previousCell = { (int)_currentCell.x, (int)_currentCell.y };
		}
	}
}

#pragma endregion

sf::Vector2f GridData::Screen2World(sf::Vector2f _screenPos)
{
	sf::Vector2f screenPos;
	screenPos.x = ((_screenPos.y - OFFSET_Y) / static_cast<float>(TILE_WIDTH / 1.75f) + (_screenPos.x - OFFSET_X) / static_cast<float>(TILE_WIDTH));
	screenPos.y = ((_screenPos.y - OFFSET_Y) / static_cast<float>(TILE_WIDTH / 1.75f) - (_screenPos.x - OFFSET_X) / static_cast<float>(TILE_WIDTH));

	return screenPos;
}

sf::Vector2f GridData::World2Screen(float _x, float _y, float _z)
{
	sf::Vector2f screenPos{ 0.f, 0.f };

	screenPos.x = (_x * (TILE_WIDTH / 2.f) - _y * (TILE_WIDTH / 2.f)) + OFFSET_X;
	screenPos.y = static_cast<float>(_x * (TILE_WIDTH / 3.5f) + _y * (TILE_WIDTH / 3.5f) - _z * TILE_WIDTH * 0.577f) + OFFSET_Y;

	return screenPos;
}
void GridData::LoadGrid(void)
{
	m_tex->loadFromFile("Sprite/Grid/hexagone.png");
	sf::Vector2f spriteOrigin = static_cast<sf::Vector2f>(GetGridTexture()->getSize());
	spriteOrigin.x /= 2;
	spriteOrigin.y /= 2 + TILE_HEIGHT / 2;

	for (int lineID = 0; lineID < NB_LINE; lineID++)
	{
		for (int columnID = 0; columnID < NB_COLUMN; columnID++)
		{
			sf::Sprite* cellSprite = m_cell[lineID][columnID].m_sprite;
			cellSprite->setTexture(*GetGridTexture());
			cellSprite->setOrigin(spriteOrigin);

			sf::Vector2f screenPos = World2Screen(static_cast<float>(lineID), static_cast<float>(columnID), 0 * TILE_MAX_HEIGHT);

			cellSprite->setPosition(screenPos);
		}
	}
}

void GridData::UdpateGrid(void)
{
	if (!m_isClicked)
	{
		CleanPath(m_start, m_end);
		//GetCell()[m_start.x][m_start.y].m_sprite->setColor(sf::Color::White);
	}
}

void GridData::DrawGrid(sf::RenderWindow& _window)
{
	for (int lineID = 0; lineID < NB_LINE; lineID++)
	{
		for (int columnID = 0; columnID < NB_COLUMN; columnID++)
		{

			_window.draw(*m_cell[lineID][columnID].m_sprite);
		}
	}


	float lineThickness = 12.f;

	for (int columnID = 0; columnID < NB_COLUMN; columnID++)
	{
		sf::Vector2f topPoint = World2Screen(static_cast<float>(0), static_cast<float>(columnID), 0 * TILE_MAX_HEIGHT);
		sf::Vector2f bottomPoint = World2Screen(static_cast<float>(NB_LINE), static_cast<float>(columnID), 0 * TILE_MAX_HEIGHT);
		sf::Vector2f center = (topPoint + bottomPoint);

		float length = 845.f;
		float angle = std::atan2(bottomPoint.y - topPoint.y, bottomPoint.x - topPoint.x) * (180.0f / static_cast<float>(M_PI));

		sf::RectangleShape line(sf::Vector2f(length, lineThickness));
		line.setOrigin(0, lineThickness / 2.0f);
		topPoint.y -= 2.f;
		line.setPosition(topPoint);
		line.setRotation(angle);


		if (columnID >= TOUCHDOWN_ENEMY_CELL + 1 && columnID <= TOUCHDOWN_ENEMY_CELL + 1)
		{
			line.setFillColor(sf::Color(255, 153, 51));
			_window.draw(line);
		}
		else if (columnID >= NEUTRAL_MIN && columnID <= NEUTRAL_MIN)
		{
			line.setFillColor(sf::Color::Blue);
			_window.draw(line);
		}
		else if (columnID >= SPAWN_SELF_MIN && columnID <= SPAWN_SELF_MIN)
		{
			line.setFillColor(sf::Color::Red);
			_window.draw(line);
		}
		else if (columnID == TOUCHDOWN_SELF_CELL)
		{
			line.setFillColor(sf::Color(255, 153, 51));
			_window.draw(line);
		}
	}
}


void GridData::MouseMovedGrid(sf::Vector2f mousePosition, const int& _mana)
{
	sf::Vector2f worldPos = Screen2World({ mousePosition.x, mousePosition.y });
	std::vector<sf::Vector2i> path;

	if (worldPos.x >= 0 and worldPos.x < NB_LINE and worldPos.y >= 0 and worldPos.y < NB_COLUMN)
	{
		HandleCellsHovering(worldPos);
		if (m_isClicked && m_isPathfindingEnabled)
		{
			m_end = { (int)worldPos.x, (int)worldPos.y };
			CleanPath(m_start, m_end);

			if (!(m_start == m_end))
			{
				//m_cell[(int)m_start.x][(int)m_start.y].m_sprite->setColor(sf::Color::Magenta);
				if (m_allowDiagonal)
				{
					path = BFSDiagonal(m_start, m_end, _mana);
				}
				else
				{
					path = BFS(m_start, m_end, _mana);
				}

				// Draw only a portion of the path based on available mana
				int drawLength = std::min(static_cast<int>(path.size()), _mana);
				UpdateCellColors(std::vector<sf::Vector2i>(path.begin(), path.begin() + drawLength), _mana);
				m_oldPath = path; // Store the current valid path


			}
		}
		else
		{
			// If not in pathfinding mode, draw the last valid path
			UpdateCellColors(m_oldPath, _mana);
		}
	}
	else
	{
		// If outside the grid, draw the last valid path
		UpdateCellColors(m_oldPath, _mana);
	}
}
void GridData::UpdateCellColors(const std::vector<sf::Vector2i>& path, const int& _mana)
{
	for (int i = 0; i < path.size(); i++)
	{
		int line = path.at(i).x;
		int column = path.at(i).y;

		sf::Color cellColor = (i == path.size() - 1) ? sf::Color(255, 0, 127) : sf::Color::Yellow;
		m_cell[line][column].m_sprite->setColor(cellColor);
	}
}

void GridData::MousePressedGrid(sf::Vector2i mousePosition)
{
	if (mousePosition.x >= 0 and mousePosition.x < NB_LINE and mousePosition.y >= 0 and mousePosition.y < NB_COLUMN)
	{
		if (m_isClicked)
		{
			m_start = mousePosition;
		}
	}

	for (int lineID = 0; lineID < NB_LINE; lineID++)
	{
		for (int columnID = 0; columnID < NB_COLUMN; columnID++)
		{
			if ((m_cell[lineID][columnID].m_isOccupied))
			{
				m_cell[lineID][columnID].m_sprite->setColor(sf::Color::White);
			}
		}
	}
}

std::vector<sf::Vector2i> GridData::BFS(const sf::Vector2i& _start, const sf::Vector2i& _end, const int& _mana)
{
	std::deque<sf::Vector2i> queue;
	std::vector<std::vector<bool>> visited(NB_LINE, std::vector<bool>(NB_COLUMN, false));
	std::vector<std::vector<sf::Vector2i>> previousCell(NB_LINE, std::vector<sf::Vector2i>(NB_COLUMN));
	std::vector<sf::Vector2i> path;

	queue.push_back(_start);

	visited[_start.x][_start.y] = true;
	while (!queue.empty())
	{
		sf::Vector2i cell = queue.front();
		queue.pop_front();

		if (cell == _end)
		{
			while (cell != _start)
			{
				path.push_back(cell);
				cell = previousCell[cell.x][cell.y];

			}
			// Include the start cell in the path
			std::reverse(path.begin(), path.end());
			//path.pop_back();
			return path;
		}

		std::array<const sf::Vector2i, 4> directions = { { { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } } };
		//std::array<const sf::Vector2i, 4> directions = { { { LEFT, NONE }, { RIGHT, NONE }, { NONE, DOWN }, { NONE, UP } } };
		for (const sf::Vector2i& dir : directions)
		{
			sf::Vector2i nextCell = cell + dir;
			int lineID = nextCell.x;
			int columnID = nextCell.y;

			if (lineID >= 0 && lineID < NB_LINE && columnID >= 0 && columnID < NB_COLUMN &&
				(!IsCellOccupied(lineID, columnID) || (nextCell == _end && columnID == _end.y)) &&
				!visited[lineID][columnID])
			{
				queue.push_back(nextCell);
				previousCell[lineID][columnID] = cell;
				visited[lineID][columnID] = true;
			}
		}
	}

	// If the loop completes without finding the end, return an empty path
	return path;
}

std::vector<sf::Vector2i> GridData::BFSDiagonal(sf::Vector2i _start, sf::Vector2i _end, const int& _mana)
{
	std::deque<sf::Vector2i> queue;
	std::vector<std::vector<bool>> isFree(NB_LINE, std::vector<bool>(NB_COLUMN, true));
	std::vector<std::vector<sf::Vector2i>> startCell(NB_LINE, std::vector<sf::Vector2i>(NB_COLUMN));
	std::vector<sf::Vector2i> path;

	queue.push_back(_start);

	const std::array<sf::Vector2i, 8> directions =
	{
		{ {LEFT, NONE}, {RIGHT, NONE}, {NONE, DOWN}, {NONE, UP},
		  {LEFT, DOWN}, {RIGHT, DOWN}, {LEFT, UP}, {RIGHT, UP} }
	};

	while (!queue.empty())
	{
		sf::Vector2i cell = queue.front();
		queue.pop_front();

		if (cell == _end)
		{
			// Build the path if the destination is reached
			while (cell != _start)
			{
				path.push_back(cell);
				cell = startCell[cell.x][cell.y];
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		for (const sf::Vector2i& dir : directions)
		{
			sf::Vector2i nextCell = cell + dir;
			int lineID = nextCell.x;
			int columnID = nextCell.y;

			if (lineID >= 0 && lineID < NB_LINE && columnID >= 0 && columnID < NB_COLUMN &&
				(!IsCellOccupied(lineID, columnID) || (nextCell == _end && columnID == _end.y)) &&
				isFree[lineID][columnID])
			{
				queue.push_back(nextCell);
				startCell[lineID][columnID] = cell;
				isFree[lineID][columnID] = false;
			}
		}
	}

	return path;
}

void GridData::CleanPath(sf::Vector2i _start, sf::Vector2i _end)
{
	for (auto& path : m_oldPath)
	{
		int line = path.x;
		int column = path.y;
		m_cell[line][column].m_sprite->setColor(sf::Color::White);
	}
	m_oldPath.clear();
	_start = { -1,-1 };
	_end = { -1,-1 };
}

int GridData::GetZoneOnMap(sf::Vector2i _coord)
{
	if (_coord.y == TOUCHDOWN_ENEMY_CELL)
	{
		return TOUCHDOWN_ENEMY;
	}
	if (_coord.y >= SPAWN_ENEMY_MIN && _coord.y <= SPAWN_ENEMY_MAX)
	{
		return SPAWN_ENEMY;
	}
	if (_coord.y >= NEUTRAL_MIN && _coord.y <= NEUTRAL_MAX)
	{
		return NEUTRAL;
	}
	if (_coord.y >= SPAWN_SELF_MIN && _coord.y <= SPAWN_SELF_MAX)
	{
		return SPAWN_SELF;
	}
	if (_coord.y == TOUCHDOWN_SELF_CELL)
	{
		return TOUCHDOWN_SELF;
	}
}

#pragma region Getters
bool GridData::IsCellOccupied(int lineID, int columnID)
{
	if (lineID >= 0 && lineID < NB_LINE && columnID >= 0 && columnID < NB_COLUMN)
	{
		return *m_cell[lineID][columnID].m_isOccupied;
	}
	return false;
}
#pragma endregion

#pragma region Setters
void GridData::SetIsOccupied(int lineID, int columnID, const bool& isOccupied)
{
	if (lineID >= 0 && lineID < NB_LINE && columnID >= 0 && columnID < NB_COLUMN)
	{
		*m_cell[lineID][columnID].m_isOccupied = isOccupied;
	}
}
#pragma endregion

#pragma region constructors
GridData::GridData()
	: m_cell{ nullptr }
{
	//Allocate memory for each dimension of the pointer
	//First dimension allocation

	m_tex = new sf::Texture;
	m_cell = new Cell * [NB_LINE];

	for (int lineID = 0; lineID < NB_LINE; lineID++)
	{
		m_cell[lineID] = new Cell[NB_COLUMN];
		for (int columnID = 0; columnID < NB_COLUMN; columnID++)
		{
			m_cell[lineID][columnID].m_sprite = new sf::Sprite;
			m_cell[lineID][columnID].m_isOccupied = new bool(false);
		}
	}
	std::cout << "\033[6;1;31mDefault\033[0m constructor for grid called !!" << std::endl;
}
//Copy constructor
GridData::GridData(const GridData& _source)
	: m_cell{ _source.m_cell }
{
	for (int lineID = 0; lineID < NB_LINE; lineID++)
	{
		for (int columnID = 0; columnID < NB_COLUMN; columnID++)
		{
			_source.m_cell[lineID][columnID].m_sprite = new sf::Sprite;
			_source.m_cell[lineID][columnID].m_isOccupied = new bool;
		}
	}
	std::cout << "\033[6;1;32mCopy\033[0m  constructor for grid called !!" << std::endl;
}
//Move Constructor
GridData::GridData(GridData&& _source) noexcept
	:m_cell{ _source.m_cell }
{
	// Move ownership of m_cell and set it to nullptr in the source
	m_cell = _source.m_cell;
	_source.m_cell = nullptr;

	std::cout << "\033[6;1;33mMove\033[0m  constructor for grid called !!" << std::endl;
}


GridData::~GridData()
{
	if (m_cell != nullptr)
	{
		for (int lineID = 0; lineID < NB_LINE; lineID++)
		{
			for (int columnID = 0; columnID < NB_COLUMN; columnID++)
			{
				delete m_cell[lineID][columnID].m_sprite;
				m_cell[lineID][columnID].m_sprite = nullptr;
				delete m_cell[lineID][columnID].m_isOccupied;
				m_cell[lineID][columnID].m_isOccupied = nullptr;
			}
			delete[] m_cell[lineID];
			m_cell[lineID] = nullptr;
		}
		delete[] m_cell;
		m_cell = nullptr;
	}

	delete m_tex;
	m_tex = nullptr;

	std::cout << "\033[6;1;34mDeconstructor\033[0m constructor for grid called !!" << std::endl;
}
#pragma endregion


