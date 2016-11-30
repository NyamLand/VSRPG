
#pragma once

//****************************************************************
//
//	PointManagerƒNƒ‰ƒX
//
//****************************************************************

//	class
class PointManager
{
private:
	int		point[PLAYER_MAX];

public:
	//	‰Šú‰»E‰ğ•ú
	PointManager( void );
	~PointManager( void );

	//	“®ìŠÖ”
	void	CalcPoint( int id, int point );
	void	SendPoint( int id );

	//	î•ñİ’è
};

extern	PointManager*	pointManager;