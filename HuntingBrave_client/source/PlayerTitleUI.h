
#pragma once

//***************************************************************
//
//	PlayerTitleUI�N���X
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"Image.h"

//	class
class PlayerTitleUI
{
private:
	int index;
	int front, back;
	int posx, posy;
	Image*	 frontTitleImage;
	Image*	 backTitleImage;

public:
	//	�������E���
	PlayerTitleUI( void );
	~PlayerTitleUI( void );
	void	Initialize( int front, int back, int x, int y, int w, int h );

	//	�X�V
	void	Update( void );

	//	�`��
	void	Render( void );

	//	���ݒ�
	void	SetPos( int x, int y );
	void	SetTitle( int front, int back );
};
