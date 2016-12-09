
#pragma once

//***************************************************************
//
//	NameInput�N���X
//
//***************************************************************

//	include
#include	"Image.h"
#include	"GameData.h"

//	class
class NameInput
{
private:
	iex2DObj*	back;
	Image*			cursorImage;
	Image*			nameImage[NAME_MAX];
	float	percentageX, percentageY;
	float	axisX, axisY;
	bool	inputState, cancelState, doneState;
	int cursorX, cursorY;
	int nameCursor;
	int saveX, saveY;
	int	name[NAME_MAX];

public:
	//	�������E���
	NameInput( void );
	~NameInput( void );

	//	�X�V�E�`��
	bool	Update( void );
	void	Render( void );

	//	����֐�
	void	MoveCursor( void );
	void	UpdateInfo( void );
	void	DecisionCharacter( void );
	void	Cancel( void );

	//	���擾
	bool	GetCancelState( void );
	int*	GetName( void );
};
 