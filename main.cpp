#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "files_check.hpp"

int main()
{
	imageCheck ch;
	ch.check_image_exist();
	GameEngine::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic-Tac-Toe");
}