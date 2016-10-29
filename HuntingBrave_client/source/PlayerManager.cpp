
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"UIManager.h"
#include	"GameParam.h"
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
	PlayerManager::PlayerManager( void )
	{
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
	void	PlayerManager::Update( void )
	{
		//	�S�v���C���[������
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	���݃`�F�b�N
			if ( player[p] == nullptr )	continue;
			
			//	�v���C���[�X�V
			bool isAlive = player[p]->Update( gameParam->GetPlayerParam( p ) );
			if ( isAlive == false )
			{
				SafeDelete( player[p] );
			}
		}
	}

	//	�`��
	void	PlayerManager::Render( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	���݃`�F�b�N
			if ( player[p] == nullptr )	continue;

			//	�`��
			player[p]->Render();
		}
	}

//-------------------------------------------------------------------------------------
//	����֐�
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

	//	�v���C���[����
	void	PlayerManager::SetPlayer( int id )
	{
		//	���݃`�F�b�N
		if ( player[id] != nullptr )	return;

		//	�v���C���[����
		player[id] = new Player();
		player[id]->Initialize();
	}

//-------------------------------------------------------------------------------------
//	���擾
//-------------------------------------------------------------------------------------

	//	Player���擾
	Player*	PlayerManager::GetPlayer( int id )
	{
		return	player[id];
	}
