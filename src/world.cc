#include "world.hh"

#include "defs.hh"
#include "raylib.h"

#include <set>
#include <stack>

static void conways_game_of_life_iteration(std::vector<std::vector<EntType>>& grid);

static bool in_bounds(int x, int y, const std::vector<std::vector<EntType>>& grid){
	return (x >= 0 && x < (int)grid[0].size() && y >= 0 && y < (int)grid.size());
}
static const std::vector<Vector2> DIR_CARDINAL_4 = {{0, +1}, {+1, 0}, {-1, 0}, {0, -1}};
static const std::vector<Vector2> DIR_CARDINAL_8 = {
	{0, +1}, {+1, 0}, {-1, 0}, {0, -1},
	{+1, +1}, {+1, -1}, {-1, +1}, {-1, -1}
};

std::map<EntType, Color> g_entity_color_map = {
	{ ENT_NONE, GRAY },
	{ ENT_WALL, DARKGRAY },
	{ ENT_PLAYER, SKYBLUE },
};

void WorldNode::render(){
	for (int y = 0; y < getRows(); ++y){
		for (int x = 0; x < getCols(); ++x){
			if (_grid[y][x] != ENT_NONE){
				DrawRectangle(LEFT_PANE_W + x * BLOCK_SIZE, y * BLOCK_SIZE, 
						BLOCK_SIZE, BLOCK_SIZE, 
						g_entity_color_map[_grid[y][x]]);
			}
		}
	}

	// render lines
	for (int i = 0; i < getRows(); ++i) // horizontal
		DrawLine(LEFT_PANE_W, i * BLOCK_SIZE, WINDOW_W, i * BLOCK_SIZE, DARKGRAY);
	for (int i = 0; i < getCols(); ++i) // vertical 
		DrawLine(LEFT_PANE_W + i * BLOCK_SIZE, 0, LEFT_PANE_W + i * BLOCK_SIZE, WINDOW_H, DARKGRAY);
}

bool World::movePlayer(int nx, int ny){
	std::shared_ptr<WorldNode> node = getCurrNode();
	WorldNode* chunk = getCurrNode().get();

	int sx, sy;
	sx = _player.x, sy = _player.y;

	if (chunk->inBounds(nx, ny) && chunk->getEntityAt(nx, ny) != ENT_WALL){
		std::vector<std::vector<EntType>> & grid = chunk->getGrid();

		grid[_player.y][_player.x] = ENT_NONE;
		_player = { (float)nx, (float)ny };	
		grid[_player.y][_player.x] = ENT_PLAYER;
	}

	return sx != _player.x && sy != _player.y;
}



void World::setEntity(int dx, int dy, EntType to_type){
	WorldNode* chunk = getCurrNode().get();
	if (chunk->inBounds(dx, dy)){
		EntType from_type = chunk->getEntityAt(dx, dy);

		std::vector<std::vector<EntType>> & grid = chunk->getGrid();
		switch(to_type){
			case ENT_PLAYER:
				movePlayer(dx, dy);
				break;
			case ENT_WALL:
				if (from_type != ENT_PLAYER){
					grid[dy][dx] = to_type;
				}
				break;
			case ENT_NONE:
				if (from_type != ENT_PLAYER){
					grid[dy][dx] = to_type;
				}
				break;
			default:
				break;
		}
	}
}

// returns true if the start and end nodes in the grid are connected
static bool is_connected(std::vector<std::vector<EntType>> grid){
	Vector2 start, end;
	
	int cx, cy;
	cx = Random::getInt(0, grid[0].size());
	cy = Random::getInt(0, grid.size());

	for (int y = 0; y < (int)grid.size(); ++y){
		for (int x = 0; x < (int)grid[y].size(); ++x){
			if (grid[y][x] == ENT_PLAYER){
				start = { (float)x, (float)y };
				end = { (float)cx, (float)cy };
			}
		}
	}

	std::set<std::pair<int,int>> vis;
	std::stack<Vector2> s;
	s.push(start);

	while (!s.empty()){
		Vector2 node = s.top();
		s.pop();
		int x = node.x, y = node.y;
		vis.insert(std::make_pair(x, y));
		// printf("[%i,%i] ->", x, y);
		if (x == end.x && y == end.y)
			return true;
		for (const auto& [mx, my] : DIR_CARDINAL_4){
			int nx = x + mx, ny = y + my;
			if (in_bounds(nx, ny, grid) &&
					grid[ny][nx] != ENT_WALL &&
					vis.find(std::make_pair(nx, ny)) == vis.end()){
				s.push({ (float)nx, (float)ny });
			}
		}
	}
	return false;
}


static void conways_game_of_life_iteration(std::vector<std::vector<EntType>>& grid){
	int rows = grid.size();
	int cols = grid[0].size();

	for (int y = 0; y < rows; ++y){
		for (int x = 0; x < cols; ++x){
			int neighbor_count = 0;
			for (const auto& [mx, my] : DIR_CARDINAL_8){
				int nx = x + mx, ny = y + my;
				if (in_bounds(nx, ny, grid) &&
						grid[ny][nx] == ENT_WALL){
					neighbor_count++;	
				}
			}

			if (grid[y][x] == ENT_WALL){
				if (neighbor_count < 0) {
					// Any live cell with fewer than two live neighbors dies
					grid[y][x] = ENT_NONE;
				}
				else if (neighbor_count == 2 || neighbor_count == 3){
					// Any live cell with two or three live neighbors lives
				} 
				else {
					// Any live cell with more than three live neighbors dies
					grid[y][x] = ENT_NONE;
				}
			} else if (grid[y][x] == ENT_NONE){
				// Any dead cell with exactly three live neighbors becomes alive
				if (neighbor_count == 3)
					grid[y][x] = ENT_WALL;

			}
		}
	}
}

// randomize the world using Conway's Game of Life algorithm

void randomizeB(World& world, WorldNode* node, bool randomize_player) {
	// probability that cell will initially be a wall
	const float a = 0.33f; 
	// the number of iterations to preprocess for Conway's GOL.
	const int iters = 100;
	
	world.getCurrNode()->getPath().clear();

	int rows = world.getCurrNode()->getRows();
	int cols = world.getCurrNode()->getCols();
	
	Vector2 og_player_pos = world.getPlayerPos();

	std::vector<std::vector<EntType>> grid(rows, std::vector<EntType>(cols, ENT_NONE));
	int sx, sy;
	if (randomize_player){
		sx = Random::getInt(0, cols-1);
		sy = Random::getInt(0, rows-1);
	} else {
		sx = og_player_pos.x;
		sy = og_player_pos.y;
	}
	// place start pos on the world

	grid[sy][sx] = ENT_PLAYER;

	// place end pos on the world
	int ex, ey;
	do {
		ex = Random::getInt(0, cols-1);
		ey = Random::getInt(0, rows-1);
	}
	while ((sx == ex && sy == ey)); // redo if end is equal to start
	grid[ey][ex] = ENT_NONE;

	// seed the intial grid 
	for (int y = 0; y < rows; ++y){
		for (int x = 0; x < cols; ++x){
			if (Random::getFloat(0.f, 1.f) < a){
				if (grid[y][x] == ENT_NONE)
					grid[y][x] = ENT_WALL;
			}
		}
	}

	// do Conway's GOL iter times
	for (int i = 0; i < iters; ++i)
		conways_game_of_life_iteration(grid);
	
	while (!is_connected(grid))
		conways_game_of_life_iteration(grid);

	node->setGrid(grid);

	world.movePlayer(sx, sy);
}

