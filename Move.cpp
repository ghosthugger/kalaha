// Move.cpp: implementation of the Move class.
//
//////////////////////////////////////////////////////////////////////

#include <sstream>

#include "Move.h"
#include "Pos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Move::Move(const Move& other)
{
	m_vecPartMoves.assign(other.m_vecPartMoves.begin(), other.m_vecPartMoves.end());
}

Move::Move()
{

}

Move::~Move()
{

}

Pos Move::Perform(const Pos p)
{
	Pos newPos = p;
	std::vector<int>::iterator iter = m_vecPartMoves.begin();
	while(iter != m_vecPartMoves.end())
	{
		newPos.DistributePit(*iter);

		iter++;
	}

	return newPos;
}

void Move::AddPartMove(int i)
{
	m_vecPartMoves.push_back(i);
}

std::string Move::toString()
{
	std::string csStr("Distribute the following pits: ");
	std::vector<int>::iterator iter = m_vecPartMoves.begin();
	while(iter != m_vecPartMoves.end())
	{
		int pit = *iter+1;
		std::stringstream oss;
		oss << pit;
		csStr += oss.str();
		iter++;
	}
	return csStr;
}
