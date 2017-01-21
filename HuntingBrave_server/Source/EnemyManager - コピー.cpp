
#include	"iextreme.h"
#include	<vector>
#include	"Random.h"
#include	"GameParam.h"
#include	"EnemyManager.h"

//*****************************************************************************************************************************
//
//	EnemyManager�N���X
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

#define	ENEMY_MAX	5
#define	APPEND_INTERVAL	10

namespace
{
	namespace ENEMY_COMMAND
	{
		enum
		{
			ENEMY_INFO,
			ERASE_INFO,
			APPEND_INFO
		};
	}

}

EnemyManager*	enemyManager = nullptr;

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	EnemyManager::EnemyManager( void ) : timer( nullptr )
	{
		enemyList.clear();
		if ( timer == nullptr )	timer = new Timer();
	}

	//	�f�X�g���N�^
	EnemyManager::~EnemyManager( void )
	{
		Release();
	}

	//	������
	bool	EnemyManager::Initialize( void )
	{
		enemyList.clear();
		if ( timer == nullptr )	timer = new Timer();
		return	true;
	}

	//	���
	void	EnemyManager::Release( void )
	{
		for ( auto it = enemyList.begin(); it != enemyList.end(); )
		{
			it = enemyList.erase( it );
		}

		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}
	}
	
//----------------------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	EnemyManager::Update( void )
	{
		int	enemyNum = 0;
		for ( auto it = enemyList.begin(); it != enemyList.end(); )
		{
			//	�X�V
			( *it )->Update();

			//	�G��񑗐M
			int index = std::distance( enemyList.begin(), it );
			SendEnemyInfo( index, ( *it )->GetEnemyParam() );

			enemyNum++;
			it++;
		}

		//	��莞�Ԃ��Ƃɐ���
		if ( timer != nullptr )		return;

		if ( timer->Update() )
		{
			//	�ǉ�
			if ( enemyNum < ENEMY_MAX )
				Append( Vector3( 0.0f, 0.0f, 0.0f ), 0.0f );

			timer->Start( APPEND_INTERVAL );
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	���X�g�ɒǉ�
	void	EnemyManager::Append( const Vector3& pos, float angle )
	{
		//	������
		Enemy*	enemy = new Enemy();
		enemy->SetPos( pos );
		enemy->SetAngle( angle );
		enemy->Update();
		
		//	���X�g�ɒǉ�
		enemyList.push_back( enemy );

		//	�ǉ���񑗐M
		SendAppend();
	}

	//	�G��񑗐M
	void	EnemyManager::SendEnemyInfo( int index, const EnemyParam& enemyParam )
	{
		//	�\���̐錾
		static	struct
		{
			char com;
			char enemyCom;
			int	index;
			Vector3	pos;
			float			angle;
			int			motion;
		} enemyInfo;

		//	���ݒ�
		enemyInfo.com = SEND_COMMAND::ENEMY_INFO;
		enemyInfo.enemyCom = ENEMY_COMMAND::ENEMY_INFO;
		enemyInfo.index = index;
		enemyInfo.pos = enemyParam.pos;
		enemyInfo.angle = enemyParam.angle;
		enemyInfo.motion = enemyParam.motion;
		
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( char* )&enemyInfo, sizeof( enemyInfo ) );
		}
	}

	//	�G�폜��񑗐M
	void	EnemyManager::SendErase( int index )
	{
		static	struct
		{
			char com;
			char enemyCom;
			int	index;
		} enemyInfo;

		enemyInfo.com = SEND_COMMAND::ENEMY_INFO;
		enemyInfo.enemyCom = ENEMY_COMMAND::ERASE_INFO;
		enemyInfo.index = index;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( char* )&enemyInfo, sizeof( enemyInfo ) );
		}
	}

	//	���X�g�ǉ���񑗐M
	void	EnemyManager::SendAppend( void )
	{	
		static	struct
		{
			char com;
			char enemyCom;
		} enemyInfo;

		enemyInfo.com = SEND_COMMAND::ENEMY_INFO;
		enemyInfo.enemyCom = ENEMY_COMMAND::APPEND_INFO;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( char* )&enemyInfo, sizeof( enemyInfo ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------
