
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

	//	���ݒ�
};

extern	PointManager*	pointManager;