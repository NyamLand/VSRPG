
#pragma once

//***************************************************************
//
//	RankUI�N���X
//
//***************************************************************

//	class
class RankUI
{
protected:
	Image* rankImage;

public:
	//	�������E���
	RankUI( int x, int y, int w, int h );
	~RankUI( void );

	//	�X�V�E�`��
	void	Update( int player );
	void	Update( int x, int y, int w, int h );
	void	Render( void );
};

