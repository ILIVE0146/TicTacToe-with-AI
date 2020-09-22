#include "unbeatableAI.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

using namespace std;

namespace GameEngine
{
	unbeatableAI::unbeatableAI(int playerPiece, GameDataRef data)
	{
		this->_data = data;

		this->playerPiece = playerPiece;

		if (O_piece_number == playerPiece)
		{
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

	void unbeatableAI::PlacePiece(int(*gridArray)[3][3], sf::Sprite gridPieces[3][3], int *gameState)
	{
		try
		{
			
		}
		catch (int error)
		{

		}

		*gameState = STATE_PLAYING;
	}

	

	void unbeatableAI::CheckIfPieceIsEmpty(int X, int Y, int(*gridArray)[3][3], sf::Sprite gridPieces[3][3])
	{
		// check if
		if (Empty_piece_number == (*gridArray)[X][Y])
		{
			(*gridArray)[X][Y] = AI_piece;
			gridPieces[X][Y].setTexture(this->_data->assets.GetTexture("O Piece"));

			gridPieces[X][Y].setColor(sf::Color(255, 255, 255, 255));


			throw - 2;
		}
	}

}