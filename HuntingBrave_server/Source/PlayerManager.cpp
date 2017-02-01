
#include	"iextreme.h"
#include	<vector>
#include	"PlayerManager.h"

//*****************************************************************************************************************************
//
//	PlayerManager�N���X
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

PlayerManager*	playerManager = nullptr;

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	PlayerManager::PlayerManager( GameParam* gameParam )
	{
		this->gameParam = gameParam;

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
	bool	PlayerManager::Initialize( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	�v���C���[���A�N�e�B�u��ԂȂ�
			if ( gameParam->GetPlayerActive( p ) )	SetPlayer( p );
		}
		return	true;
	}

	//	���
	void	PlayerManager::Release( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			ReleasePlayer( p );
		}
	}

//----------------------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	PlayerManager::Update( int id )
	{
		PlayerParam	param = gameParam->GetPlayerParam( id );

		//	�v���C���[�X�V
		if (  gameParam->GetPlayerActive( id ) == false )
		{
			ReleasePlayer( id );
		}
		else
		{
			//	�X�V�E���𔽉f
			player[id]->Update( param );
			gameParam->SetPlayerParam( id, param.pos, param.angle, param.effParam, param.motion );
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	�v���C���[�ݒ�
	void	PlayerManager::SetPlayer( int id )
	{
		//	�v���C���[����
		player[id] = new Player( id );
	}

	//	�v���C���[���
	void	PlayerManager::ReleasePlayer( int id )
	{
		if ( player[id] != nullptr )
		{
			delete	player[id];
			player[id] = nullptr;
		}
	}

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	���W�擾
	Vector3	PlayerManager::GetPos( int id )
	{
		return	Vector3( 0.0f, 0.0f, 0.0f );
	}

	//	�v���C���[�擾
	Player*&	PlayerManager::GetPlayer( int id )
	{
		return	player[id];
	}
