
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

namespace
{
#define	PLAYER_SCALE	0.2f

	const LPSTR fileName[] = 
	{
		"DATA/CHR/suppin/Suppin.IEM",
		"DATA/CHR/Fighter/Fighter.IEM",
		"DATA/CHR/Magician/Magician.IEM",
		"DATA/CHR/suppin/Suppin.IEM",
		"DATA/CHR/suppin/Suppin.IEM",
		"DATA/CHR/suppin/Suppin.IEM"
	};
}

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

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			obj[i] = new iex3DObj( fileName[i] );
			obj[i]->SetAngle( 0.0f );
			obj[i]->SetScale( PLAYER_SCALE );
			obj[i]->SetPos( 0.0f, 0.0f, 0.0f );
			obj[i]->Update();
		}

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

		for ( int i = 0; i < PLAYER_TYPE::MODEL_MAX; i++ )
		{
			SafeDelete( obj[i] );
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
		return;
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
		player->SetObj( obj[nextClass]->Clone() );
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
