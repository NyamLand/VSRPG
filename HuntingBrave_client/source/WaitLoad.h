
#pragma once

//**************************************************************************
//
//	WaitLoad�N���X
//
//**************************************************************************

//	include
#include	"Font.h"
#include	"Timer.h"

//	class
class WaitLoad
{
private:
	Font*	font;
	Timer*	timer;
	char		text[256];
	int		count;

public:
	//	�������E���
	WaitLoad( void );
	~WaitLoad( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
};
