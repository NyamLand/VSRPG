
#pragma once

//*****************************************************************************************************************************
//
//	InputManagerクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"

//	定数( XBoxコントローラ )
namespace
{
	//	キー
	namespace KEY_TYPE
	{
		enum 
		{
			NO_INPUT,
			A = 4,
			B,
			X,
			Y,
			L1 = 8,
			R1,
			L3 = 12,
			R3,
			SELECT,
			START,
		};
	}

	//	入力状態
	namespace KEY_STATE
	{
		enum
		{
			NO_INPUT,
			STAY,
			UP,
			ENTER
		};
	}
}

//	struct
struct InputInfo
	{
		float	axisX, axisY;
		int	keyType;
		int	keyState;
	};


//	class
class InputManager
{
private:
	InputInfo	inputInfo[PLAYER_MAX];

public:
	//	初期化・解放
	InputManager( void );
	~InputManager( void );

	//	情報設定
	void	SetInput( int id, int keyType, int keyState );
	void	SetAxis( int id, float axisX, float axisY );

	//	情報取得
	InputInfo&	GetInput( int id );
	bool	GetInputState( int id, int keyType, int keyState );
};

extern	InputManager*	inputManager;