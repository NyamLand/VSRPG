
#include	"iextreme.h"
#include	<map>
#include	"InputManager.h"

//*****************************************************************************************************************************
//
//	InputManager�N���X
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//	����
InputManager*	inputManager = nullptr;

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	InputManager::InputManager( void )
	{
		//	inputInfo������
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	�X�e�B�b�N���͏�����
			inputInfo[p].axisX = 0.0f;
			inputInfo[p].axisY = 0.0f;
			
			//	�L�[��񏉊���
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

	//	�f�X�g���N�^
	InputManager::~InputManager( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	map���
			inputInfo[p].keyState.clear();
		}
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	���͏��ݒ�
	void	InputManager::SetInput( int id, char keyType, char keyState )
	{
		//	���ݒ�
		inputInfo[id].keyState[keyType] = keyState;
	}

	//	�X�e�B�b�N���͏�񂹂��Ă�
	void	InputManager::SetAxis( int id, float axisX, float axisY )
	{
		inputInfo[id].axisX = axisX;
		inputInfo[id].axisY = axisY;
	}

	//	���͏�񃊃Z�b�g
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
//	���擾
//----------------------------------------------------------------------------------------------

	//	���͏��擾
	InputInfo&	InputManager::GetInput( int id )
	{
		return	inputInfo[id];
	}

	//	���͏�Ԏ擾
	bool	InputManager::GetInputState( int id, char keyType, char keyState )
	{
		if ( inputInfo[id].keyState[keyType] == keyState )	return	true;
		return	false;
	}

