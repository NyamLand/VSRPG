
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
	void	CharacterCheck( bool& voicedSpotState );
	void	CharacterCheckLast( void );
	bool	VoicedSpotCheck( int& out, int beforeIndex, int nameIndex, bool& semiVoicedSpot );
	void	MoveCursor( void );
	void	UpdateInfo( void );
	void	DecisionCharacter( void );
	void	Cancel( void );

	void	NormalCharacterSet( void );
	void	VoicedSpotCharacterSet( int nameIndex, bool semiVoicedSpot );

	//	���擾
	bool	GetCancelState( void );
	int*	GetName( void );
};
 