#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

#include "ai.hpp"
#include "unbeatableAI.hpp"

namespace GameEngine
{
	class unbeatableGameState : public State
	{
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _pauseButton;

		sf::Sprite _gridSprite;

		sf::Sprite _gridPieces[3][3];
		int _gridArray[3][3];

		int turn;
		int gameState;

		unbeatableAI *ai;

		sf::Clock _clock;
	public:
		unbeatableGameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);


		void InitGridPieces();

		void CheckAndPlacePiece();

		void CheckHasPlayerWon(int turn);
		void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
	};
}