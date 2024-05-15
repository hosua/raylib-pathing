#pragma once

#include <raylib.h>

#include <queue>
#include <vector>

#include "world.hh"

namespace PathFinder {
	std::vector<Vector2> find(Vector2 start, Vector2 dest, std::vector<std::vector<EntType>> grid);
}
