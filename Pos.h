// Pos.h: interface for the Pos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POS_H__DD5941E1_FAEC_4A0E_82F2_2818ACA5682D__INCLUDED_)
#define AFX_POS_H__DD5941E1_FAEC_4A0E_82F2_2818ACA5682D__INCLUDED_

#include <string>
#include <memory>

#include "Move.h"
#include "MoveIter.h"


class Pos  
{
public:
	Pos();
	virtual ~Pos();
	bool WithinMovingSideHome(int nPit);
	int MovingSideKalaha();
	int OppositePit(int i);
	int NoOfBallsInPit(int i);
	int Value(int nLevels, bool bMaxLevel, int nAlfa, int nBeta);
	int Value();
	void DistributePit(int nPit);
	Move FindMove(int nLevels);
	std::shared_ptr<MoveIter> PossibleMoves();
	std::string toString();

	bool PlayerWins();
	bool OpponentWins();
	bool ItIsADraw();
	bool IsGameOver();

	void IfAnySideEmptyMoveAllToKalaha();
	int m_pits[14];
	bool m_bPlayersTurn;
};

#endif // !defined(AFX_POS_H__DD5941E1_FAEC_4A0E_82F2_2818ACA5682D__INCLUDED_)
