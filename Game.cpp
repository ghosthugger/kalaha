// Game.cpp: implementation of the Game class.
//
//////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Game.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Game::Game()
{

}

Game::~Game()
{

}

void Game::Play()
{
	pos.m_pits[0] = 6;
	pos.m_pits[1] = 6;
	pos.m_pits[2] = 6;
	pos.m_pits[3] = 6;
	pos.m_pits[4] = 6;
	pos.m_pits[5] = 6;
	pos.m_pits[6] = 0;

	pos.m_pits[7] = 6;
	pos.m_pits[8] = 6;
	pos.m_pits[9] = 6;
	pos.m_pits[10] = 6;
	pos.m_pits[11] = 6;
	pos.m_pits[12] = 6;
	pos.m_pits[13] = 0;

	pos.m_bPlayersTurn = true;

	int nDifficulty = 0;
	while(nDifficulty > 7
			|| nDifficulty < 2)
	{
		std::cout << std::endl << "Enter difficulty level (2-7) (2=very easy) (7=to hard):";
		cin >> nDifficulty;
	}

	cout << endl << "Game starts!" << endl;

	while(!pos.OpponentWins()
			&& !pos.PlayerWins()
			&& !pos.ItIsADraw())
	{
		cout << pos.toString();

		Move move;
		if(pos.m_bPlayersTurn)
		{

			int index = 0;
			do
			{
				cout << "enter index of pit to distribute" << endl;
				cin >> index;
			}
			while(index-1 < 6
					&& index-1 >= 0
					&& pos.m_pits[index-1] == 0);

			move.AddPartMove(index-1);
		}
		else
		{
			cout << endl << "Computer desperately tries to figure something out" << endl;
			move = pos.FindMove(nDifficulty);
		}
		
		pos = move.Perform(pos);
	}

	cout << endl << "Final position" << endl;
	if(pos.OpponentWins())
		cout << "Computer won!";
	else if(pos.PlayerWins())
		cout << "You won!";
	else if(pos.ItIsADraw())
		cout << "it is a draw!";


	cout << pos.toString();

	int moped = 0;
	cin >> moped;
}
