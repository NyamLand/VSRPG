
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
#define	APPEND_INTERVAL	5
#define	PLAYER_RADIUS	1.5f

namespace
{
	namespace ENEMY_COMMAND
	{
		enum
		{
			ERASE_INFO = 10,
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
		timer->Start( APPEND_INTERVAL );
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
	void	EnemyManager::Update( float deltaTime )
	{
		int	enemyNum = 0;
		for ( auto it = enemyList.begin(); it != enemyList.end(); )
		{
			//	�C���f�b�N�X
			char index = std::distance( enemyList.begin(), it );
			
			//	���W�`�F�b�N
			PosCheck( *it );
			PlayerPosCheck( *it );

			//	�X�V
			( *it )->Update( index, deltaTime );

			enemyNum++;
			it++;
		}

		//	��莞�Ԃ��Ƃɐ���
		if ( timer == nullptr )		return;

		if ( timer->Update() )
		{
			//	�ǉ�
			if ( enemyNum < ENEMY_MAX )
				Append( Vector3( 0.0f, 0.0f, 50.0f ), 0.0f );

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

		
		//	�ǉ���񑗐M
		SendAppend( pos, angle );
		
		//	���X�g�ɒǉ�
		enemyList.push_back( enemy );
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
	void	EnemyManager::SendAppend( const Vector3& pos, float angle )
	{	
		static	struct
		{
			char com;
			char enemyCom;
			Vector3	pos;
			float			angle;
		} enemyInfo;

		enemyInfo.com = SEND_COMMAND::ENEMY_INFO;
		enemyInfo.enemyCom = ENEMY_COMMAND::APPEND_INFO;
		enemyInfo.pos = pos;
		enemyInfo.angle = angle;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( char* )&enemyInfo, sizeof( enemyInfo ) );
		}
	}

	//	���W�`�F�b�N�i �߂���Ή������� �j
	void	EnemyManager::PosCheck( Enemy* enemy )
	{
		for ( auto it = enemyList.begin(); it != enemyList.end(); it++ )
		{
			//	����VS�����͏��O
			if ( ( *it ) == enemy )	continue;

			//	����������ւ̃x�N�g��
			Vector3	vec = enemy->GetPos() - ( *it )->GetPos();
			vec.y = 0.0f;
			float		length = vec.Length();

			float collisionDist = enemy->GetCollisionInfo().radius + ( *it )->GetCollisionInfo().radius;
			
			//	�߂��ꍇ�͗���
			if ( length < collisionDist )
			{
				//	�x�N�g�����K��
				vec.Normalize();

				//	����
				( *it )->SetPos( enemy->GetPos() - vec * collisionDist );
				( *it )->SendEnemyInfo();
			}
		}

	}

	//	�v���C���[�Ƃ̍��W�`�F�b�N
	void	EnemyManager::PlayerPosCheck( Enemy* enemy )
	{
		//	����������ւ̃x�N�g��
		for (int p = 0; p < PLAYER_MAX; p++)
		{
			//	���݃`�F�b�N
			if ( !gameParam->GetPlayerActive( p ) )	continue;
			PlayerParam		playerParam = gameParam->GetPlayerParam( p );

			//	�v���C���[�ւ̃x�N�g�������߂�
			Vector3	pPos = playerParam.pos;
			Vector3	vec = pPos - enemy->GetPos();
			vec.y = 0.0f;
			float		length = vec.Length();

			float collisionDist = enemy->GetCollisionInfo().radius + PLAYER_RADIUS;
			
			//	�߂��ꍇ�͗���
			if ( length <  collisionDist )
			{
				//	�x�N�g�����K��
				vec.Normalize();

				//	����
				enemy->SetPos( pPos - vec * collisionDist );
				enemy->SendEnemyInfo();
			}
		}
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------
