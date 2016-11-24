
#include	"iextreme.h"
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
	void	InputManager::SetInput( int id, int keyType, int keyState )
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

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	���͏��擾
	InputInfo&	InputManager::GetInput( int id )
	{
		return	inputInfo[id];
	}

	//	���͏�Ԏ擾
	bool	InputManager::GetInputState( int id, int keyType, int keyState )
	{
		if ( inputInfo[id].keyState[keyType] == keyState )	return	true;
		return	false;
	}

