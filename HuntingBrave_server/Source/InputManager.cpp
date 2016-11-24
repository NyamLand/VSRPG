
#include	"iextreme.h"
#include	"InputManager.h"

//*****************************************************************************************************************************
//
//	InputManagerクラス
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//	実体
InputManager*	inputManager = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	InputManager::InputManager( void )
	{
		//	inputInfo初期化
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	スティック入力初期化
			inputInfo[p].axisX = 0.0f;
			inputInfo[p].axisY = 0.0f;
			
			//	キー情報初期化
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::A, 0 ) );
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::B, 0 ) );
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::X, 0 ) );
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::Y, 0 ) );
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::L1, 0 ) );
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::L3, 0 ) );
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::R1, 0 ) );
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::R3, 0 ) );
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::SELECT, 0 ) );
			inputInfo[p].keyState.insert( std::map<int, int>::value_type( KEY_TYPE::START, 0 ) );
		}
	}

	//	デストラクタ
	InputManager::~InputManager( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	map解放
			inputInfo[p].keyState.clear();
		}
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	入力情報設定
	void	InputManager::SetInput( int id, int keyType, int keyState )
	{
		//	情報設定
		inputInfo[id].keyState[keyType] = keyState;
	}

	//	スティック入力情報せってい
	void	InputManager::SetAxis( int id, float axisX, float axisY )
	{
		inputInfo[id].axisX = axisX;
		inputInfo[id].axisY = axisY;
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	入力情報取得
	InputInfo&	InputManager::GetInput( int id )
	{
		return	inputInfo[id];
	}

	//	入力状態取得
	bool	InputManager::GetInputState( int id, int keyType, int keyState )
	{
		if ( inputInfo[id].keyState[keyType] == keyState )	return	true;
		return	false;
	}

