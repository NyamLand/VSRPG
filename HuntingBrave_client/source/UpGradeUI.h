
#pragma once

//***************************************************************
//
//	UpGradeUI�N���X
//
//***************************************************************

//	include
#include	"Image.h"
#include	"ExpUI.h"
#include	"Font.h"

//	class
class UpGradeUI
{
private:
	Image*	 back;
	Image*	*	typeIcon;
	Image**	levelIcon;
	Image*		curLevelIcon;
	ExpUI*		expUI;
	NeedExpUI*		needExpUI;
	Font*		flavorText;

	float		percentage;
	float		percentage2;

	char		select;
	char		beforeSelect;
	LPSTR	text;

	int level;
	int id;

public:
	//	�������E���
	UpGradeUI( void );
	~UpGradeUI( void );
	
	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
	void	LevelIconRender( void );

	//	����֐�
	void	Dicision( void );
	void	MoveCursor( void );
	bool	IconScaling( void );

	//	���ݒ�
	void	SetBigIconSrcPos( void );
};
