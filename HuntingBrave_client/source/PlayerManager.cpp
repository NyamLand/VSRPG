
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<vector>
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
		for ( int i = 0; i < PLAYER_TYPE::MODEL_MAX; i++ )
		{
			obj[i] = nullptr;
		}

		playerList.clear();
	}
		
	//	�f�X�g���N�^
	PlayerManager::~PlayerManager( void )
	{
		//Release();
	}

	//	������
	bool	PlayerManager::Initialize( void )
	{
		//	���X�g������
		playerList.clear();

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			SetPlayer( p );
		}
		return	true;
	}

	//	���
	void	PlayerManager::Release( void )
	{
		for ( auto it = playerList.begin(); it != playerList.end(); )
		{
			it = playerList.erase( it );
		}
	}

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------
	
	//	�X�V
	void	PlayerManager::Update( void )
	{
		//	�S�v���C���[�X�V
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) )
				playerList[p]->Update();
		}
	}

	//	�`��
	void	PlayerManager::Render( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) )
				playerList[p]->Render();
		}
	}

	//	HP�o�[�`��
	void	PlayerManager::RenderHp( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) )
				playerList[p]->BarRender();
		}
	}

//-------------------------------------------------------------------------------------
//	����֐�
//-------------------------------------------------------------------------------------

	//	�N���X�`�F���W
	void	PlayerManager::ClassChange( int id, char nextClass )
	{
		Player*	 player = nullptr;

		switch ( nextClass )
		{
		case PLAYER_TYPE::NORMAL:
			player = new Suppin();
			break;

		case PLAYER_TYPE::FIGHTER:
			player = new Fighter();
			break;

		case PLAYER_TYPE::MAGICIAN:
			player = new Magician();
			break;

		default:
			player = new Suppin();
		}

		//	���f���Z�b�g�A������
		player->Initialize( id );

		//	���X�g�ɒǉ�
		playerList.insert( playerList.begin() + id, player );
	}

//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

	//	�v���C���[����
	void	PlayerManager::SetPlayer( int id )
	{
		//	�v���C���[����
		ClassChange( id, PLAYER_TYPE::NORMAL );
	}

//-------------------------------------------------------------------------------------
//	���擾
//-------------------------------------------------------------------------------------

	//	Player���擾
	Player*&	PlayerManager::GetPlayer( int id )
	{
		return	playerList[id];
	}
