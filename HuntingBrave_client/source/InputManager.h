
#pragma once

//***************************************************************
//
//	InputManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"

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

//	class
class InputManager : public	Singleton<InputManager>
{
	friend	Singleton<InputManager>;
public:
	enum BUTTON_STATE
	{
		NO_INPUT = -1,
		STAY = 1,
		UP,
		ENTER
	};

private:
	//	初期化・解放
	InputManager( void );
	~InputManager( void );

public:
	//	動作関数
	bool StickInputCheck( const Vector3& inputVec, float minInput );
	BUTTON_TYPE	GetInput( char& inputType );

	void	Update( void );

	//	入力情報取得
	bool	GetAButton( BUTTON_STATE buttonState );
	bool	GetBButton( BUTTON_STATE buttonState );
	bool	GetXButton( BUTTON_STATE buttonState );
	bool	GetYButton( BUTTON_STATE buttonState );
	bool	GetR1Button( BUTTON_STATE buttonState );
	bool	GetR3Button( BUTTON_STATE buttonState );
	bool	GetL1Button( BUTTON_STATE buttonState );
	bool	GetL3Button( BUTTON_STATE buttonState );
	bool	GetStartButton( BUTTON_STATE buttonState );
	bool	GetSelectButton( BUTTON_STATE buttonState );

	//	スティック入力取得
	Vector3 GetStickInputLeft( void );
	Vector3 GetStickInputRight( void );
};

#define	inputManager ( InputManager::GetInstance() )