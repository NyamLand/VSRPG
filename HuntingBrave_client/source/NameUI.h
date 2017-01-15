
#pragma once

//***************************************************************
//
//	NameUI�N���X
//
//***************************************************************

//	include
#include	"Image.h"

//	class
class NameUI
{
private:
	Image*		nameImage[NAME_MAX];
	int	posX, posY;
	int	scale;
	int	space;

public:
	//	�������E���
	NameUI( void );
	~NameUI( void );
	bool	Initialize( int x, int y, int w, int h );

	//	�X�V�E�`��
	void	Update( int* name );
	void	Render( void );

	//	���ݒ�
	void	SetPos( int posx, int posy );
	void	SetSpace( int space );
};
