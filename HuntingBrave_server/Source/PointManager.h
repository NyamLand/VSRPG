
#pragma once

//****************************************************************
//
//	PointManagerクラス
//
//****************************************************************

//	class
class PointManager
{
private:
	int		point[PLAYER_MAX];

public:
	//	初期化・解放
	PointManager( void );
	~PointManager( void );

	//	動作関数
	void	CalcPoint( int id, int point );
	void	SendPoint( int id );
	void	ReceiveHuntInfo( int client, const LPSTR& data );

	//	情報設定
};

extern	PointManager*	pointManager;