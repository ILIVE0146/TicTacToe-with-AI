#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Game.hpp"

namespace GameEngine{
    class ai{
        public:
        ai(int playerPiece, GameDataRef data);
        void placePiece(int (*gridArray)[3][3], sf::Sprite gridPieces[3][3],int *gameState);
        void checkSection(int x1,int y1,int x2,int y2,int X,int Y,int pieceToCheck,int (*gridArray)[3][3],sf::Sprite gridPieces[3][3]);
        void checkIfPieceIsEmpty(int X,int Y,int (*gridArray)[3][3], sf::Sprite gridPieces[3][3]);
        private:
        int aiPiece;
        int playerPiece;
        std::vector<std::array<int,6>>checkMatchVector;
        GameDataRef _data;
    };
}