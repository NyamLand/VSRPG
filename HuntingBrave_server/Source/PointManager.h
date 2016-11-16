
#pragma once

//****************************************************************
//
//	PointManager�N���X
//
//****************************************************************

//	include
#include	"GameParam.h"

//	class
class PointManager
{
private:
	GameParam*	gameParam;
	int		point[PLAYER_MAX];

public:
	//	�������E���
	PointManager( GameParam* gameParam );
	~PointManager( void );

	//	�X�V
	void	Update( int client );

	//	���ݒ�
	void	SetHitParam( int client );
};

extern	PointManager*	pointManager;