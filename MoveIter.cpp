// MoveIter.cpp: implementation of the MoveIter class.
//
//////////////////////////////////////////////////////////////////////

#include "MoveIter.h"

#include "Move.h"
#include "Pos.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MoveIter::MoveIter()
{

}

MoveIter::~MoveIter()
{

}

Move MoveIter::operator *()
{
	return *m_iter;
}

void MoveIter::operator++()
{
	m_iter++;
}

bool MoveIter::HasMore()
{
	return m_iter != m_vecAllPossibleMoves.end(); 
}

MoveIter::MoveIter(Pos pos)
{
	Move move;
	FindAllPossibleMoves(move, pos);
	m_iter = m_vecAllPossibleMoves.begin();
}

void MoveIter::FindAllPossibleMoves(Move move, Pos pos)
{
	int nDelta = 0;
	if(!pos.m_bPlayersTurn)
		nDelta = 7;  // generate opponent moves

	for(int i=0+nDelta ; i<=5+nDelta ; i++)
	{
		if(move.Perform(pos).m_pits[i] != 0)
		{
			Move newMove(move);  // unneccesary copy ?
			newMove.AddPartMove(i);
			Pos newPos = newMove.Perform(pos);
			if(newPos.m_bPlayersTurn == pos.m_bPlayersTurn
			   && !newPos.IsGameOver())
			{
				FindAllPossibleMoves(newMove, pos);
			}
			else
			{
				m_vecAllPossibleMoves.push_back(newMove);
			}
		}
	}
}

