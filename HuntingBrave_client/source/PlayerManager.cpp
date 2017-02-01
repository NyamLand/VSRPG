
#include	"iextreme.h"
#include	"system/System.h"
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
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if( gameParam->GetPlayerActive( p ) == false )	continue;
			
			player[p] = nullptr;
			SetPlayer( p );
		}

		return	true;
	}

	//	���
	void	PlayerManager::Release( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			SafeDelete( player[i] );
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
			if ( gameParam->GetPlayerActive( p ) == false )		continue;
			
			//	�X�V
			player[p]->Update();
		}
	}

	//	�`��
	void	PlayerManager::Render( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) == false )		continue;
			
			//	�`��
			player[p]->Render( shader, "damageEffect" );
		}
	}

	//	HP�o�[�`��
	void	PlayerManager::RenderHp( void )
	{
		return;
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) == false )	continue;
			
			//	�o�[�`��
			player[p]->BarRender();
		}
	}

//-------------------------------------------------------------------------------------
//	����֐�
//-------------------------------------------------------------------------------------

	//	�N���X�`�F���W
	void	PlayerManager::ClassChange( int id, char nextClass )
	{
		if ( gameParam->GetPlayerActive( id ) == false )	return;

		//	�N���X�`�F���W
		player[id]->ChangeModel( nextClass );
	}

	//	��M
	void	PlayerManager::Receive( const LPSTR& data )
	{
		ReceiveClassChangeData* receiveData = 
			( ReceiveClassChangeData* )data;
		ClassChange( receiveData->id, receiveData->nextClass );
	}

//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

	//	�v���C���[����
	void	PlayerManager::SetPlayer( int id )
	{
		player[id] = new Player();
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
