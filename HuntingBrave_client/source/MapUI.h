
#pragma once

//***************************************************************
//
//	MapUI�N���X
//
//***************************************************************

//	include
#include	"GameData.h"

//	class
class MapUI
{
private:
	Image*	back;
	Image*		player[PLAYER_MAX];
	int	posx, posy, width, height;

public:
	//	�������E���
	MapUI( void );
	~MapUI( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
};

