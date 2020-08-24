#include "ai.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
using namespace std;
namespace GameEngine{
    ai::ai(int playerPiece, GameDataRef data){
        this->_data = data;
        this->playerPiece = playerPiece;
        if(O_piece_number == playerPiece){
            aiPiece = X_piece_number;
        }
        else
        {
            aiPiece = O_piece_number;
        }
        checkMatchVector.push_back({ 0, 2, 1, 2, 2, 2 });
		checkMatchVector.push_back({ 0, 2, 0, 1, 0, 0 });
		checkMatchVector.push_back({ 0, 2, 1, 1, 2, 0 });
		checkMatchVector.push_back({ 2, 2, 1, 2, 0, 2 });
		checkMatchVector.push_back({ 2, 2, 2, 1, 2, 0 });
		checkMatchVector.push_back({ 2, 2, 1, 1, 0, 0 });
		checkMatchVector.push_back({ 0, 0, 0, 1, 0, 2 });
		checkMatchVector.push_back({ 0, 0, 1, 0, 2, 0 });
		checkMatchVector.push_back({ 0, 0, 1, 1, 2, 2 });
		checkMatchVector.push_back({ 2, 0, 2, 1, 2, 2 });
		checkMatchVector.push_back({ 2, 0, 1, 0, 0, 0 });
		checkMatchVector.push_back({ 2, 0, 1, 1, 0, 2 });
		checkMatchVector.push_back({ 0, 1, 1, 1, 2, 1 });
		checkMatchVector.push_back({ 1, 2, 1, 1, 1, 0 });
		checkMatchVector.push_back({ 2, 1, 1, 1, 0, 1 });
		checkMatchVector.push_back({ 1, 0, 1, 1, 1, 2 });
		checkMatchVector.push_back({ 0, 1, 2, 1, 1, 1 });
		checkMatchVector.push_back({ 1, 2, 1, 0, 1, 1 });
		checkMatchVector.push_back({ 0, 2, 2, 0, 1, 1 });
		checkMatchVector.push_back({ 2, 2, 0, 0, 1, 1 });
		checkMatchVector.push_back({ 0, 2, 2, 2, 1, 2 });
		checkMatchVector.push_back({ 0, 0, 2, 0, 1, 0 });
		checkMatchVector.push_back({ 0, 2, 0, 0, 0, 1 });
		checkMatchVector.push_back({ 2, 2, 2, 0, 2, 1 });
    }
    void ai::placePiece(int (*gridArray)[3][3], sf::Sprite gridPieces[3][3],int *gameState){
        try
        {
            for(int i=0;i<this->checkMatchVector.size();i++){
                checkSection(checkMatchVector[i][0],checkMatchVector[i][1],checkMatchVector[i][2],checkMatchVector[i][3],checkMatchVector[i][4],checkMatchVector[i][5],AI_piece,gridArray,gridPieces);
            }
            for(int i=0;i<this->checkMatchVector.size();i++){
                checkSection(checkMatchVector[i][0],checkMatchVector[i][1],checkMatchVector[i][2],checkMatchVector[i][3],checkMatchVector[i][4],checkMatchVector[i][5],Player_piece,gridArray,gridPieces);
            }
            checkIfPieceIsEmpty(1,1,gridArray,gridPieces);

            checkIfPieceIsEmpty(0,2,gridArray,gridPieces);
            checkIfPieceIsEmpty(2,2,gridArray,gridPieces);
            checkIfPieceIsEmpty(0,0,gridArray,gridPieces);
            checkIfPieceIsEmpty(2,0,gridArray,gridPieces);

            checkIfPieceIsEmpty(1,2,gridArray,gridPieces);
            checkIfPieceIsEmpty(0,1,gridArray,gridPieces);
            checkIfPieceIsEmpty(2,1,gridArray,gridPieces);
            checkIfPieceIsEmpty(1,0,gridArray,gridPieces);
        }
        catch(int error)
        {
            
        }
        *gameState = State_playing;
        
    }
    void ai::checkSection(int x1,int y1,int x2,int y2,int X,int Y,int pieceToCheck,int (*gridArray)[3][3],sf::Sprite gridPieces[3][3]){
        if((*gridArray)[x1][y1] == pieceToCheck && (*gridArray)[x2][y2] == pieceToCheck){
            if(Empty_piece_number == (*gridArray)[X][Y]){
                (*gridArray)[X][Y] == AI_piece;
                gridPieces[X][Y].setTexture(this->_data->assets.GetTexture("O Piece"));
                gridPieces[X][Y].setColor(sf::Color(255,255,255,255));
                throw -1;
            }
        }
    }
    void ai::checkIfPieceIsEmpty(int X,int Y,int (*gridArray)[3][3], sf::Sprite gridPieces[3][3]){
        if(Empty_piece_number == (*gridArray)[X][Y]){
            (*gridArray)[X][Y] = AI_piece;
            gridPieces[X][Y].setTexture(this->_data->assets.GetTexture("O Piece"));
            gridPieces[X][Y].setColor(sf::Color(255,255,255,255));
            throw -2;
        }
    }
}