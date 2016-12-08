
#pragma once

//***************************************************************
//
//	NameInputクラス
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
	//	初期化・解放
	NameInput( void );
	~NameInput( void );

	//	更新・描画
	bool	Update( void );
	void	Render( void );

	//	動作関数
	void	MoveCursor( void );
	void	UpdateInfo( void );
	void	DecisionCharacter( void );
	void	Cancel( void );

	//	情報取得
	bool	GetCancelState( void );
	int*	GetName( void );
};
 