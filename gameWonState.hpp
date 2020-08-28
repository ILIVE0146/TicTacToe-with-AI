#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace GameEngine
{
	class GameWonState : public State
	{
		GameDataRef _data;

		sf::Sprite _retryButton;
		sf::Sprite _homeButton;
	public:
		GameWonState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}