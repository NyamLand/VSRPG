
#pragma once

//***************************************************************
//
//	UpGradeUI�N���X
//
//***************************************************************

//	include
#include	"Image.h"

//	class
class UpGradeUI
{
private:
	Image*	 back;
	Image*	*	typeIcon;
	Image**	levelIcon;

public:
	//	�������E���
	UpGradeUI( void );
	~UpGradeUI( void );
	
	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
};
