#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace GameEngine{
    class thinker
    {
    public:
        thinker(int playerPiece,GameDataRef data);
        void checkForOptimalSolutionToPlace(int(*gridArray)[3][3], sf::Sprite (*gridPieces)[3][3] , int *gameState);
        int minimax(int board[3][3], int depth, bool isMax);
        int evaluate(int b[3][3]);
        bool isMovesLeft(int board[3][3]);

    private:
        int maxPlayer;
        int minPlayer;
        GameDataRef _data;
    };
}