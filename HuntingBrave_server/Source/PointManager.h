
#pragma once

//****************************************************************
//
//	PointManager�N���X
//
//****************************************************************

//	class
class PointManager
{
private:
	int		point[PLAYER_MAX];

public:
	//	�������E���
	PointManager( void );
	~PointManager( void );

	//	����֐�
	void	CalcPoint( int id, int point );
	void	SendPoint( int id );
	void	ReceiveHuntInfo( int client, const LPSTR& data );

	//	���ݒ�
};

extern	PointManager*	pointManager;