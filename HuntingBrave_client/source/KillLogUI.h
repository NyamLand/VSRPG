
#pragma once

//*************************************************************************
//
//	KillLogUI�N���X
//
//*************************************************************************

//	include
#include	"Image.h"

//	class
class KillLogUI
{
private:
	Image*		killLogImage;
	bool	killFrag;
	float	percentage;

public:
	//	�������E���
	KillLogUI( void );
	~KillLogUI( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
	
	//	���ݒ�
	void	SetKillLog( int killer, int dead );
};
