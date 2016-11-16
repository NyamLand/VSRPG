
#pragma once

//*****************************************************************************************************************************
//
//	InputManagerクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"

//	定数
enum BUTTON_TYPE
{
	NO_INPUT = -1,
	A = 1,
	B,
	X,
	Y,
	R1,
	R3,
	L1,
	L3,
	START,
	SELECT,
};

//	struct
struct InputInfo
{
	float	axisX, axisY;
	int	buttonType;
	int	inputType;
};

//	class
class InputManager
{
public:
	enum BUTTON_STATE
	{
		NO_INPUT = -1,
		STAY = 1,
		UP,
		ENTER
	};

private:
	InputInfo	inputInfo[PLAYER_MAX];

public:
	//	初期化・解放
	InputManager( void );
	~InputManager( void );

	//	更新

	//	動作関数

	//	情報設定
	void	SetInput( int id, char buttonType, char inputType );
	void	SetAxis( int id, float axisX, float axisY );

	//	情報取得
	InputInfo&	GetInput( int id );
};

extern	InputManager*	inputManager;