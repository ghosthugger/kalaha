// Game.h: interface for the Game class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__67D1310E_8C8F_4E9F_BDBE_3282C1E6CC17__INCLUDED_)
#define AFX_GAME_H__67D1310E_8C8F_4E9F_BDBE_3282C1E6CC17__INCLUDED_


#include "Pos.h"

class Game  
{
public:
	void Play();
	Game();
	virtual ~Game();
private:
	Pos pos;
};

#endif // !defined(AFX_GAME_H__67D1310E_8C8F_4E9F_BDBE_3282C1E6CC17__INCLUDED_)
