// Pos.cpp: implementation of the Pos class.
//
//////////////////////////////////////////////////////////////////////


#include <sstream>

#include "Pos.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Pos::Pos()
: m_bPlayersTurn(true)
{

}

Pos::~Pos()
{

}

std::shared_ptr<MoveIter> Pos::PossibleMoves()
{
	return std::shared_ptr<MoveIter>(new MoveIter(*this));
}

Move Pos::FindMove(int nLevels)
{
	int nBestSoFar = 0;
	Move BestSoFar;
	bool bFirst = true;
	std::shared_ptr<MoveIter> iter = PossibleMoves();
	while(iter->HasMore())
	{
		Pos branch = (**iter).Perform(*this);
		int nBranchValue = branch.Value(nLevels-1, true);

		if(bFirst
			|| nBestSoFar > nBranchValue)
		{
			bFirst = false;
			nBestSoFar = nBranchValue;
			BestSoFar = (**iter);
		}
		++(*iter);
	}

	return BestSoFar; // might be the empty move
}

void Pos::DistributePit(int nPit)
{
//	ASSERT(m_pits[nPit] != 0); // cannot move empty pit

/*	ASSERT((m_bPlayersTurn
			  && nPit <= 5
			  && nPit >= 0)
			  || (!m_bPlayersTurn
				   && nPit <= 12
					&& nPit >= 7)); // wrong player!
					*/

	int nBalls = m_pits[nPit];
	m_pits[nPit] = 0;
	int nCurrPit = nPit;
	do
	{
		nCurrPit++;
		if(m_bPlayersTurn
			&& nCurrPit == 13)
			nCurrPit = 0;

		if(!m_bPlayersTurn
			&& nCurrPit == 6)
			nCurrPit = 7;

		if(nCurrPit > 13)
			nCurrPit = 0;
		
		nBalls --;
		m_pits[nCurrPit]++;
	} while(nBalls>0);

	if(m_pits[nCurrPit] == 1
		&& m_pits[OppositePit(nCurrPit)] != 0
		&& WithinMovingSideHome(nCurrPit))
	{
		m_pits[MovingSideKalaha()] += m_pits[nCurrPit];
		m_pits[MovingSideKalaha()] += m_pits[OppositePit(nCurrPit)];
		m_pits[nCurrPit] = 0;
		m_pits[OppositePit(nCurrPit)] = 0;
	}

	IfAnySideEmptyMoveAllToKalaha();

	if(nCurrPit != MovingSideKalaha())
		m_bPlayersTurn = !m_bPlayersTurn;
}

int Pos::Value()
{
	int nSumPlayer = 0;
	for(int i=0 ; i<= 5 ; i++)
		nSumPlayer += m_pits[i];

	int nSumOpponent = 0;
	for(int i=7 ; i<= 12; i++)
		nSumOpponent += m_pits[i];

	if(nSumPlayer == 0
		|| nSumOpponent == 0)
	{
		if(m_pits[6] == m_pits[13]) 
			return -90;  // it is a draw (need to invert with m_bPlayerTurn ??)

		if(m_pits[6] > m_pits[13])
			return 100;
		else
			return -100;
	}

	return m_pits[6] - m_pits[13];
}

int Pos::Value(int nLevels, bool bMaxLevel)
{
	if(nLevels == 1)
	{
		return Value();
	}
	int nBestSoFar = 0;
	std::shared_ptr<MoveIter> iter = PossibleMoves();
	bool bFirst = true;
	while(iter->HasMore())
	{
		int nBranchValue = (**iter).Perform(*this).Value(nLevels-1, !bMaxLevel);
		if(bFirst
			|| (bMaxLevel
				 && nBranchValue > nBestSoFar)
			||	(!bMaxLevel
				 && nBranchValue < nBestSoFar))
		{
			bFirst = false;
			nBestSoFar = nBranchValue;
		}

		++(*iter);
	}
	if(bFirst)
	{
		// win or loss
		return Value();
	}

	return nBestSoFar;
}

int Pos::NoOfBallsInPit(int i)
{
	return m_pits[i];
}

int Pos::OppositePit(int i)
{
	int f[] = {12, 11, 10, 9, 8, 7, 13, 5, 4, 3, 2, 1, 0, 6};
	return f[i];
}

int Pos::MovingSideKalaha()
{
	if(m_bPlayersTurn)
		return 6;
	else
		return 13;
}

bool Pos::WithinMovingSideHome(int nPit)
{
	return ((m_bPlayersTurn
			   && nPit >= 0
				&& nPit <= 5)
			  || (!m_bPlayersTurn
					&& nPit >= 7
					&& nPit <= 12));
}

void Pos::IfAnySideEmptyMoveAllToKalaha()
{
	int nPSum = 0;
	for(int i=0 ; i <= 5 ; i++)
		nPSum += m_pits[i];

	int nOSum = 0;
	for(int i=7 ; i<= 12 ; i++)
		nOSum += m_pits[i];

	if(nOSum == 0
		|| nPSum == 0)
	{
		m_pits[MovingSideKalaha()] += (nOSum + nPSum);
		for(int i=0 ; i<=5 ; i++)
			m_pits[i] = 0;

		for(int i=7 ; i<=12 ; i++)
			m_pits[i] = 0;
	}
}


//		10	7	78	8	8	7 
//	12							9
//		89	8	99	12	12	12
//		this sides turn

std::string Pos::toString()
{
	std::string csPos;
	std::stringstream csRow1;
	csRow1 << "\t" << m_pits[12] << "\t" << m_pits[11] << "\t" << m_pits[10] << "\t" << m_pits[9]  << "\t" << m_pits[8] << "\t" << m_pits[7];

	std::stringstream csRow2;
	csRow2 << m_pits[13] << "\t\t\t\t\t\t\t" << m_pits[6];

	std::stringstream csRow3;
	csRow3 << "\t" << m_pits[0] << "\t" << m_pits[1] << "\t" << m_pits[2] << "\t" << m_pits[3]  << "\t" << m_pits[4] << "\t" << m_pits[5];

	std::string csFirstRow;
	std::string csSecondRow;
	if(m_bPlayersTurn)
		csSecondRow = "\t\tthis sides turn";
	else
		csFirstRow = "\t\tthis sides turn";

	csPos += csFirstRow + "\n" + "\n" + csRow1.str() + "\n" + csRow2.str() + "\n" +csRow3.str() + "\n" + "\n" +csSecondRow +"\n";
	return csPos;
}



bool Pos::PlayerWins()
{
	return Value() == 100;
}

bool Pos::OpponentWins()
{
	return Value() == -100;
}

bool Pos::ItIsADraw()
{
	return Value() == -90 || Value() == 90;
}

bool Pos::IsGameOver()
{
	return PlayerWins() || OpponentWins() || ItIsADraw();
}

