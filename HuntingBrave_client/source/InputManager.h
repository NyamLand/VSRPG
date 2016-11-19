
#pragma once

//***************************************************************
//
//	InputManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"

//	定数
namespace
{
	//	キー種類
	namespace KEY_TYPE
	{
		enum
		{
			A = KEY_A,
			B,
			X,
			Y,
			L1 = KEY_L1,
			R1,
			L3 = KEY_L3,
			R3,
			SELECT,
			START,
		};
	}

	//	キー状態
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

//	class
class InputManager : public	Singleton<InputManager>
{
	friend	Singleton<InputManager>;
public:

private:
	//	初期化・解放
	InputManager( void );
	~InputManager( void );

public:
	//	スティック入力取得
	void GetStickInputLeft( float& axisX, float& axisY );
	void GetStickInputRight( float& axisX, float& axisY );
};

#define	inputManager ( InputManager::GetInstance() )