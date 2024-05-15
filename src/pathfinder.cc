#include "pathfinder.hh"

#include <cstdio>
#include <algorithm>
#include <math.h>
#include <set>

static const std::vector<Vector2> DIR_CARDINAL_4 = {{0, +1}, {+1, 0}, {-1, 0}, {0, -1}};
static const std::vector<Vector2> DIR_CARDINAL_8 = {
	{0, +1}, {+1, 0}, {-1, 0}, {0, -1},
	{+1, +1}, {+1, -1}, {-1, +1}, {-1, -1}
};

static int get_manhattan_dist(int x1, int y1, int x2, int y2);
static float get_euclidean_dist(int x1, int y1, int x2, int y2);
static int get_heuristic(int x1, int y1, int x2, int y2);
static bool in_bounds(int x, int y, const std::vector<std::vector<EntType>>& grid);

static float get_euclidean_dist(int x1, int y1, int x2, int y2){
	return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

static int get_manhattan_dist(int x1, int y1, int x2, int y2){
	return abs(y2 - y1) + abs(x2 - x1);
}

static int get_heuristic(int x1, int y1, int x2, int y2){
	return get_manhattan_dist(x1, y1, x2, y2);
}

static bool in_bounds(int x, int y, const std::vector<std::vector<EntType>>& grid){
	return (x >= 0 && x < (int)grid[0].size() && y >= 0 && y < (int)grid.size());
}

struct SearchState {
	int g, h, f,
		x, y;
	std::shared_ptr<SearchState> parent;
};

bool operator<(const SearchState& a, const SearchState& b){
	return a.f > b.f; // min heap on f = g + h
}

class AStarPQ : public std::priority_queue<SearchState> {
	public:
		std::shared_ptr<SearchState> find(const Vector2& vec) {
			for (auto itr = c.begin(); itr != c.end(); ++itr){
				SearchState state = *itr;
				if (vec.x == state.x && vec.y == state.y)
					return std::make_shared<SearchState>(*itr);
			}
			return nullptr;
		}
};

std::vector<Vector2> PathFinder::find(Vector2 start, Vector2 dest, std::vector<std::vector<EntType>> grid){
	int g = 0;	
	AStarPQ pq;
	std::set<std::pair<int,int>> vis;

	int h = get_heuristic(start.x, start.y, dest.x, dest.y);
	int f = g + h;
	int x = (int)start.x, y = (int)start.y;

	pq.push({ g, h, f,
			x, y,
			nullptr 
			});

	while (!pq.empty()){
		SearchState node = pq.top();
		x = node.x, y = node.y;
		pq.pop();
		// found goal
		if (x == dest.x && y == dest.y){
			std::vector<Vector2> path;
			path.push_back({(float)dest.x, (float)dest.y});
			// reconstruct path;
			for (SearchState* crawl = node.parent.get(); crawl; crawl = crawl->parent.get()){
				x = crawl->x, y = crawl->y;
				printf("(%i,%i)-> ", x, y);
				path.push_back({(float)x, (float)y});
			}
			printf("\n");
			std::reverse(path.begin(), path.end());
			return path;
		}
		vis.insert(std::make_pair(x, y));

		for (const auto& [mx, my] : DIR_CARDINAL_4){
			int nx = x + mx, ny = y + my;
			if (in_bounds(nx, ny, grid) &&
					grid[ny][nx] != ENT_WALL &&
					vis.find(std::make_pair(nx, ny)) == vis.end()){
				h = get_heuristic(nx, ny, dest.x, dest.y);
				f = g + h;
				SearchState new_node = {g, h, f,
						nx, ny,
						std::make_shared<SearchState>(node)
						};
				std::shared_ptr<SearchState> open_node = nullptr;
				if ( (open_node = pq.find({(float)nx, (float)ny})) ){
					if (g < open_node->g){
						open_node->parent = std::make_shared<SearchState>(new_node);
						open_node->g = g;
						open_node->f = open_node->g + open_node->h;
					}
				} else {
					pq.push(new_node);
				}
			}
		}
		g++;
	}

	return {};
}

