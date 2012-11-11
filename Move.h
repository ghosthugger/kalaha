// Move.h: interface for the Move class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVE_H__A64AA900_7DFA_49E7_9CD4_E81F0080E7A8__INCLUDED_)
#define AFX_MOVE_H__A64AA900_7DFA_49E7_9CD4_E81F0080E7A8__INCLUDED_

//#include "pos.h"
#include <vector>
#include <string>

class Pos;

class Move  
{
public:
	Move(const Move& other);
	void AddPartMove(int i);
	Pos Perform(Pos p);
	Move();
	virtual ~Move();
	std::string toString();
private:
	std::vector<int> m_vecPartMoves;
};

#endif // !defined(AFX_MOVE_H__A64AA900_7DFA_49E7_9CD4_E81F0080E7A8__INCLUDED_)
