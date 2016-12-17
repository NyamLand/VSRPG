
#include	"iextreme.h"
#include	<map>
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
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::A, 0 ) );
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::B, 0 ) );
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::X, 0 ) );
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::Y, 0 ) );
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::L1, 0 ) );
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::L3, 0 ) );
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::R1, 0 ) );
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::R3, 0 ) );
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::SELECT, 0 ) );
			inputInfo[p].keyState.insert( std::map<char, char>::value_type( KEY_TYPE::START, 0 ) );
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
	void	InputManager::SetInput( int id, char keyType, char keyState )
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

	//	入力情報リセット
	void	InputManager::ResetInput( int client )
	{
		for( auto it = inputInfo[client].keyState.begin(); it != inputInfo[client].keyState.end(); it++ )
		{
			switch ( it->second )
			{
			case KEY_STATE::UP:
				it->second = KEY_STATE::NO_INPUT;
				break;

			case KEY_STATE::ENTER:
				it->second = KEY_STATE::STAY;
				break;
			}
		}
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
	bool	InputManager::GetInputState( int id, char keyType, char keyState )
	{
		if ( inputInfo[id].keyState[keyType] == keyState )	return	true;
		return	false;
	}

