
#pragma once

//***************************************************************
//
//	Result�N���X
//
//***************************************************************

//	include
#include	"NameUI.h"
#include	"PlayerTitleUI.h"
#include	"GameData.h"
#include	"Stage.h"

//	class
class TestResult
{
private:
	Stage*	stage;

public:
	//	�������E���
	TestResult( void );
	~TestResult( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
};
