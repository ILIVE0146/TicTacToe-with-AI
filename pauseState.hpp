#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
namespace GameEngine{
	class PauseState : public State{
		GameDataRef _data;
        sf::Sprite resumeButton;
        sf::Sprite homebuton;
	public:
		PauseState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}