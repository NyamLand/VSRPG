
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

namespace
{
	//	�萔
	#define	PLAYER_SCALE	0.2f

	//	�t�@�C����
	namespace
	{
		const LPSTR ModelFileName[] =
		{
			"DATA/CHR/suppin/suppin.IEM",			//	�����҂�
			"DATA/CHR/Magician/magician.IEM",	//	�}�W�V����
			"DATA/CHR/suppin/suppin.IEM",			//	�v���[�X�g
			"DATA/CHR/Fighter/fighter.IEM",			//	�t�@�C�^�[
			"DATA/CHR/suppin/suppin.IEM",			//	�i�C�g
			"DATA/CHR/suppin/suppin.IEM"			//	�A�T�V��
		};
	}
}

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
		//Release();
	}

	//	������
	bool	PlayerManager::Initialize( void )
	{
		//	���f���ǂݍ���
		LoadModel();

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			player[p] = nullptr;

			if ( gameParam->GetPlayerActive( p ) )
			{
				PlayerParam		playerParam = gameParam->GetPlayerParam( p );
				SetPlayer( p );
			}
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

		for ( int i = 0; i < PLAYER_MODEL_TYPE::MODEL_MAX; i++ )
		{
			SafeDelete( obj[i] );
		}
	}

	//	���f���ǂݍ���
	void	PlayerManager::LoadModel( void )
	{
		for ( int i = 0; i < PLAYER_MODEL_TYPE::MODEL_MAX; i++ )
		{
			obj[i] = nullptr;
			obj[i] = 	new iex3DObj( ModelFileName[i] );
			
			//	���ݒ�
			obj[i]->SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
			obj[i]->SetAngle( 0.0f );
			obj[i]->SetScale( PLAYER_SCALE );
			obj[i]->SetMotion( MOTION_NUM::POSUTURE );
			obj[i]->Update();
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
			//	���݃`�F�b�N
			if ( player[p] == nullptr )	continue;
			
			//	�v���C���[�X�V
			player[p]->Update( gameParam->GetPlayerParam( p ) );
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


	void	PlayerManager::RenderHp(void)
	{
		for (int p = 0; p < PLAYER_MAX; p++)
		{
			if (player[p] == nullptr)	continue;
			player[p]->BarRender();

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
		player[id]->SetObj( obj[PLAYER_MODEL_TYPE::NORMAL]->Clone() );
		player[id]->SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		player[id]->SetAngle( 0.0f );
		player[id]->SetScale( PLAYER_SCALE );
		player[id]->Initialize( id );
	}

//-------------------------------------------------------------------------------------
//	���擾
//-------------------------------------------------------------------------------------

	//	Player���擾
	Player*&	PlayerManager::GetPlayer( int id )
	{
		return	player[id];
	}
