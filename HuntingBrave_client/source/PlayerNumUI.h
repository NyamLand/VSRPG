
#pragma once

//***************************************************************
//
//	PlayerNumUI�N���X
//
//***************************************************************

//	class
class PlayerNumUI
{
protected:
	Image* numImage;

public:
	//	�������E���
	PlayerNumUI( int player, int x, int y, int w, int h );
	~PlayerNumUI( void );

	//	�X�V�E�`��
	void	Update( int player );
	void	Update( int x, int y, int w, int h );
	void	Render( void );
};

