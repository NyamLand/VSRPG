
#include	"iextreme.h"
#include	"GlobalFunction.h"
//#include	"GameManager.h"
#include	"PlayerManager.h"

//***************************************************************
//
//	PlayerManager�N���X
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	�O���[�o��
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	�������E���
//-------------------------------------------------------------------------------------
	
	//	�R���X�g���N�^
	PlayerManager::PlayerManager( void ) : gameParam( nullptr )
	{
		//	�S�v���C���[������
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			player[p] = nullptr;
		}
	}
		
	//	�f�X�g���N�^
	PlayerManager::~PlayerManager( void )
	{
		Release();
	}

	//	������
	bool	PlayerManager::Initialize( GameParam* gameParam )
	{
		//	�Q�[���p�����[�^�擾
		this->gameParam = gameParam;

		//	�S�v���C���[������
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			player[p] = nullptr;
		}
		return	true;
	}

	//	���
	void	PlayerManager::Release( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			SafeDelete( player[p] );
		}
	}

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------
	
	//	�X�V
	void	PlayerManager::Update( int id )
	{
		PlayerParam param = gameParam->GetPlayerParam( id );
		if ( !player[id]->Update( param ) ) 
		{
			SafeDelete( player[id] );
		}
		else
		{
			//	�v���C���[�X�V
			gameParam->SetPlayerParam( id, param.pos, param.angle );
		}
	}

//-------------------------------------------------------------------------------------
//	����֐�
//-------------------------------------------------------------------------------------

	//	�v���C���[����
	void	PlayerManager::SetPlayer( int id, int type )
	{
		//	���݃`�F�b�N
		if ( player[id] != nullptr )	return;

		//	�v���C���[����
		player[id] = new Player();
	}

//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	���擾
//-------------------------------------------------------------------------------------

	//	Player���擾
	Vector3	PlayerManager::GetPos( int id )
	{
		return	player[id]->GetPos();
	}
