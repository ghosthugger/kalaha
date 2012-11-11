// MoveIter.h: interface for the MoveIter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEITER_H__512A77BE_B003_40B9_8E25_98055B1C1336__INCLUDED_)
#define AFX_MOVEITER_H__512A77BE_B003_40B9_8E25_98055B1C1336__INCLUDED_

#include "Move.h"	// Added by ClassView

class Move;
class Pos;

class MoveIter  
{
public:
	void FindAllPossibleMoves(Move move, Pos pos);
	MoveIter(Pos pos);
	bool HasMore();
	MoveIter();
	virtual ~MoveIter();
	Move operator *();
	void operator++();
private:
	MoveIter(const MoveIter& other) {};  // do not copy me!
	std::vector<Move> m_vecAllPossibleMoves;
	std::vector<Move>::iterator m_iter;

};

#endif // !defined(AFX_MOVEITER_H__512A77BE_B003_40B9_8E25_98055B1C1336__INCLUDED_)
