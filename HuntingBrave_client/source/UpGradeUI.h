
#pragma once

//***************************************************************
//
//	UpGradeUI�N���X
//
//***************************************************************

//	include
#include	"Image.h"
#include	"ExpUI.h"

//	class
class UpGradeUI
{
private:
	Image*	 back;
	Image*	*	typeIcon;
	Image**	levelIcon;
	Image*		curLevelIcon;
	ExpUI*		expUI;

	float		percentage;
	float		percentage2;

	char		select;
	char		beforeSelect;

	int id;

public:
	//	�������E���
	UpGradeUI( void );
	~UpGradeUI( void );
	
	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	����֐�
	void	Dicision( void );

	//	���ݒ�
	void	SetBigIconSrcPos( void );
};
