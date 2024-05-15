#include "defs.hh"
#include "raylib.h"

#include "pathfinder.hh"
#include "world.hh"

#include <raygui-cpp.h>
#include <iostream>
#include <random>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//#define RAYGUI_CUSTOM_ICONS     // It requires providing gui_icons.h in the same directory
//#include "gui_icons.h"          // External icons data provided, it can be generated with rGuiIcons tool

void UpdateDrawFrame(void);

World world;

static std::mt19937 s_gen(std::random_device{}());;

int main(){
	InitWindow(WINDOW_W, WINDOW_H, "raylib grid");
	GuiLoadStyleDefault(); // TODO: Not working?
	// GuiLoadStyle("assets/styles/dark.rgs"); // TODO: Not working?

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(60);   

	// Main game loop
	while (!WindowShouldClose()) {   // Detect window close button or ESC key
		// game main loop
		UpdateDrawFrame();
	}
#endif

	CloseWindow();        
	return 0;
}

typedef enum {
	IM_NONE,
	IM_BUILDING,
	IM_MOVING,
} InputMode;

InputMode input_mode = IM_MOVING;

void UpdateDrawFrame(void){
	// Update

	std::string mouse_pos_text, cell_pos_text;
	Vector2 mouse_pos = GetMousePosition();
	mouse_pos_text = "(" + std::to_string((int)mouse_pos.x) + ", " + std::to_string((int)mouse_pos.y) + ")";

	int cx, cy; // cell x,y position on grid

	if (mouse_pos.x > LEFT_PANE_W){

		cx = (mouse_pos.x - LEFT_PANE_W) / BLOCK_SIZE;
		cy = mouse_pos.y / BLOCK_SIZE;
		cell_pos_text = "(" + std::to_string(cx) + ", " + std::to_string(cy) + ")";

		if (world.getCurrNode()->inBounds(cx, cy)){
			switch (input_mode){
				case IM_BUILDING:
					{
						if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
								world.getCurrNode()->getEntityAt(cx, cy) != ENT_PLAYER){
							world.setEntity(cx, cy, ENT_WALL);
						} else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) &&
								world.getCurrNode()->getEntityAt(cx, cy) != ENT_PLAYER){
							world.setEntity(cx, cy, ENT_NONE);
						}
					} break;
				case IM_MOVING:
					{
						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
								world.getCurrNode()->getEntityAt(cx, cy) != ENT_PLAYER){
							const Vector2 player = world.getPlayerPos();
							std::vector<Vector2> path = PathFinder::find({player.x, player.y}, {(float)cx, (float)cy}, world.getCurrNode()->getGrid());
							world.getCurrNode()->setPath(path);
						}
					}
				default:
					break;
			}
		}
	}

	std::shared_ptr<WorldNode> curr = world.getCurrNode();
	std::vector<Vector2>& path = curr->getPath();

	// Draw
	BeginDrawing();
	ClearBackground(LIGHTGRAY);
	// GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

	curr->render();
	
	// if there is a path, render it
	if (path.size() > 0 && input_mode == IM_MOVING){
		Vector2 next = path.front();
		world.movePlayer(next.x, next.y);
		path.erase(path.begin());
		for (const Vector2& vec : path){
			DrawRectangle(LEFT_PANE_W + vec.x * BLOCK_SIZE, vec.y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, ColorAlpha(LIME, 0.5f));
		}
	}

	if (GuiButton({5,5, 120, 50}, "Build")){
		if (input_mode != IM_BUILDING){
			std::cout << "Set to building mode\n";
			curr->getPath().clear();
			input_mode = IM_BUILDING;
		}
	}

	if (GuiButton({5,60, 120, 50}, "Move")){
		if (input_mode != IM_MOVING){
			std::cout << "Set to movement mode\n";
			input_mode = IM_MOVING;
		}
	}

	if (GuiButton({5,115, 120, 50}, "Randomize B")){
		std::cout << "Randomizing map with Algorithm B\n";
		curr->getPath().clear();
		path.clear();
		randomizeB(world, world.getCurrNode().get(), false);
	}
	
	if (world.getPlayerPos().y == 0 && 
			GuiButton({50, 195, 25, 25 }, GuiIconText(ICON_ARROW_UP, ""))){
		world.movePlayer(world.getPlayerPos().x, curr->getRows()-1, true);
		if (curr->m_up.get() == nullptr){
			curr->m_up = std::make_shared<WorldNode>();
			randomizeB(world, world.getCurrNode()->m_up.get(), false);
			curr->m_up->m_down = curr;
		}
		world.setCurrNode(curr->m_up);
	}

	if (world.getPlayerPos().x == 0 &&
			GuiButton({25, 225, 25, 25 }, GuiIconText(ICON_ARROW_LEFT, ""))){
		world.movePlayer(curr->getCols()-1, world.getPlayerPos().y, true);
		if (curr->m_left.get() == nullptr){
			curr->m_left = std::make_shared<WorldNode>();
			randomizeB(world, world.getCurrNode()->m_left.get(), false);
			curr->m_left->m_right = curr;
		}
		world.setCurrNode(curr->m_left);
	}

	if (world.getPlayerPos().x == world.getCurrNode()->getCols()-1 &&
			GuiButton({75, 225, 25, 25 }, GuiIconText(ICON_ARROW_RIGHT, ""))){
		world.movePlayer(0, world.getPlayerPos().y, true);
		if (curr->m_right.get() == nullptr){
			curr->m_right = std::make_shared<WorldNode>();
			randomizeB(world, world.getCurrNode()->m_right.get(), false);
			curr->m_right->m_left = curr;
		}
		world.setCurrNode(curr->m_right);
	}
	
	if (world.getPlayerPos().y == world.getCurrNode()->getRows()-1 && 
			GuiButton({50, 255, 25, 25 }, GuiIconText(ICON_ARROW_DOWN, ""))){
		world.movePlayer(world.getPlayerPos().x, 0, true);
		if (curr->m_down.get() == nullptr){
			curr->m_down = std::make_shared<WorldNode>();
			randomizeB(world, world.getCurrNode()->m_down.get(), false);
			curr->m_down->m_up = curr;
		}
		world.setCurrNode(curr->m_down);
	}

	// DrawText("Sample text!", 190, 200, 20, LIGHTGRAY);
	DrawText(mouse_pos_text.c_str(), 5, WINDOW_H - 50, 20, DARKGRAY);
	DrawText(cell_pos_text.c_str(), 5, WINDOW_H - 25, 20, DARKGRAY);

	EndDrawing();
}

int Random::getInt(int min, int max){
	std::uniform_int_distribution<> s_distr(min, max);
	return s_distr(s_gen);
}

float Random::getFloat(float min, float max){
	std::uniform_real_distribution<> s_distr(min, max);
	return s_distr(s_gen);
}
