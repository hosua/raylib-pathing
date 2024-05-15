#pragma once

#include "defs.hh"
#include "raylib.h"

#include <cstdio>
#include <map>
#include <memory>
#include <vector>

typedef enum {
	ENT_NONE,
	ENT_WALL,
	ENT_PLAYER,
} EntType;

extern std::map<EntType, Color> g_entity_color_map;

class WorldNode {
	public:
		WorldNode(Vector2 start = { 0.f, 0.f }):
			m_left(nullptr),
			m_up(nullptr),
			m_right(nullptr),
			m_down(nullptr){
				int rows = WINDOW_H / BLOCK_SIZE;
				int cols = (WINDOW_W - LEFT_PANE_W) / BLOCK_SIZE;

				_grid = std::vector(rows, std::vector(cols, ENT_NONE));
				_grid[start.y][start.x] = ENT_PLAYER;


			}
		
		const int getRows() const { return _grid.size(); }
		const int getCols() const { return _grid[0].size(); }
		const Vector2 getDims() const { return { (float)getRows(), (float)getCols() }; }

		const bool inBounds(int x, int y) const { return x >= 0 && x < getCols() && y >= 0 && y < getRows(); }
		
		const EntType getEntityAt(int x, int y) const { return _grid[y][x]; }

		std::vector<std::vector<EntType>>& getGrid() { return _grid; }
		void setGrid(std::vector<std::vector<EntType>> new_grid) { _grid = new_grid; }

		std::vector<Vector2>& getPath(){ return _path; }
		void setPath(std::vector<Vector2> path){ _path = path; }

		void render();
		
		std::shared_ptr<WorldNode> m_left, m_up, m_right, m_down;
	private:
		std::vector<std::vector<EntType>> _grid;
		std::vector<Vector2> _path;
};

class World {
public:
	World(){ 
		_curr = _head = std::make_shared<WorldNode>(); 
		movePlayer(20, 20);
	}
	~World() = default;
	
	bool movePlayer(int dx, int dy);
	void setEntity(int dx, int dy, EntType ent_type);
	void setCurrNode(std::shared_ptr<WorldNode> new_node){ _curr = new_node; }
	std::shared_ptr<WorldNode> getCurrNode() const { return _curr; }
	std::shared_ptr<WorldNode> getHeadNode() const { return _head; }
	const Vector2 getPlayerPos() const { return _player; }

private:
	std::shared_ptr<WorldNode> _head = nullptr;
	std::shared_ptr<WorldNode> _curr = nullptr;
	Vector2 _player;
};

void randomizeB(World& world, WorldNode* node, bool randomize_player=false);
