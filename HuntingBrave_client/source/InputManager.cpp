
#include	"iextreme.h"
#include	"InputManager.h"

//***************************************************************
//
//	InputManagerクラス
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	グローバル
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------------------

	//	コンストラクタ
	InputManager::InputManager( void )
	{
	
	}

	//	デストラクタ
	InputManager::~InputManager( void )
	{

	}

	void	InputManager::Update( void )
	{
		BUTTON_STATE buttonState = BUTTON_STATE::ENTER;
		GetAButton( buttonState );
		GetBButton( buttonState );
		GetXButton( buttonState );
		GetYButton( buttonState );
		GetR1Button( buttonState );
		GetR3Button( buttonState );
		GetL1Button( buttonState );
		GetL3Button( buttonState );
		GetStartButton( buttonState );
		GetSelectButton( buttonState );
	}

//-------------------------------------------------------------------------------------
//	動作関数
//-------------------------------------------------------------------------------------

	//	スティック入力チェック( スティックの入力方向, 最小入力値 )
	bool	InputManager::StickInputCheck( const Vector3& inputVec, float minInput )
	{
		float axisX = inputVec.x;
		float axisY = inputVec.y;

		float length = sqrtf( axisX * axisX + axisY * axisY );
		
		if ( length >= minInput )	return	true;
		return	false;
	}

	//	入力情報取得
	BUTTON_TYPE	InputManager::GetInput( int& inputType )
	{
		//	変数準備
		BUTTON_TYPE	buttonType;
		inputType = BUTTON_STATE::NO_INPUT;

		//	入力取得
		if ( GetAButton( BUTTON_STATE::ENTER ) )
		{
			buttonType = BUTTON_TYPE::A;
			inputType = BUTTON_STATE::ENTER;
		}
		return	buttonType;
	}

//-------------------------------------------------------------------------------------
//	各ボタン情報取得
//-------------------------------------------------------------------------------------

	//	Aボタン取得
	bool InputManager::GetAButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_A ) == buttonState )
		{
			printf( "A-Button\n" );
			return	true;
		}

		return	false;
	}

	//	Bボタン取得
	bool InputManager::GetBButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_B ) == buttonState )
		{
			printf( "B-Button\n" );
			return	true;
		}

		return	false;
	}

	//	Xボタン取得
	bool InputManager::GetXButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_X ) == buttonState )
		{
			printf( "X-Button\n" );
			return	true;
		}

		return	false;
	}

	//	Yボタン取得
	bool InputManager::GetYButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_Y ) == buttonState )
		{
			printf( "Y-Button\n" );
			return	true;
		}

		return	false;
	}

	//	R1ボタン取得
	bool InputManager::GetR1Button( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_R1 ) == buttonState )
		{
			printf( "R1-Button\n" );
			return	true;
		}

		return	false;
	}

	//	R3ボタン取得
	bool InputManager::GetR3Button( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_R3 ) == buttonState )
		{
			printf( "R3-Button\n" );
			return	true;
		}

		return	false;
	}

	//	L1ボタン取得
	bool InputManager::GetL1Button( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_L1 ) == buttonState )
		{
			printf( "L1-Button\n" );
			return	true;
		}

		return	false;
	}

	//	L3ボタン取得
	bool InputManager::GetL3Button( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_L3 ) == buttonState )
		{
			printf( "L3-Button\n" );
			return	true;
		}
		
		return	false;
	}

	//	スタートボタン取得
	bool InputManager::GetStartButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_SELECT ) == buttonState )
		{
			printf( "Start-Button\n" );
			return	true;
		}

		return	false;
	}

	//	セレクトボタン取得
	bool InputManager::GetSelectButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_ENTER ) == buttonState )
		{
			printf( "Select-Button\n" );
			return	true;
		}

		return	false;
	}

	//	左スティック入力取得
	Vector3	InputManager::GetStickInputLeft( void )
	{
		//	出力
		Vector3	out = Vector3(
			KEY( KEY_AXISX ) * 0.001f,
			-KEY( KEY_AXISY ) * 0.001f,
			0.0f );

		return	out;
	}

	//	右スティック入力取得
	Vector3	InputManager::GetStickInputRight( void )
	{
		//	出力
		Vector3	out = Vector3 (
			KEY( KEY_AXISX2 ) * 0.001f,
			-KEY( KEY_AXISY2 ) * 0.001f,
			0.0f );

		return	out;
	}
