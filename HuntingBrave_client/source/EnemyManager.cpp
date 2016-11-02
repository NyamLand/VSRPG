
#include	"iextreme.h"
#include	"Random.h"
#include	"GameData.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"PlayerManager.h"
#include	"UIManager.h"
#include	"EnemyManager.h"

//***************************************************************
//
//	EnemyManager�N���X
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	�O���[�o��
//-------------------------------------------------------------------------------------

//	�萔
#define	APPEND_INTERVAL		3
#define	COLLISION_DIST	2.0f
#define	ENEMY_MAX			5

namespace
{

}

//-------------------------------------------------------------------------------------
//	�������E���
//-------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	EnemyManager::EnemyManager( void ) : appendOK( true )
	{
		//���X�g������
		enemylist.clear();

		//	�I�u�W�F�N�g������
		for ( int i = 0; i < ENEMY_TYPE::TYPE_MAX; i++ )
		{
			org[i] = nullptr;
		}
	}

	//	�f�X�g���N�^
	EnemyManager::~EnemyManager( void )
	{
		Release();
	}

	//	������
	bool	EnemyManager::Initialize( void )
	{
		//���X�g������
		enemylist.clear();

		//	���f���ǂݍ���
		Load();

		return	true;
	}

	//	���
	void	EnemyManager::Release( void )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); )
		{
			it = enemylist.erase( it );
		}

		for ( int i = 0; i < ENEMY_TYPE::TYPE_MAX; i++ )
		{
			SafeDelete( org[i] );
		}
	}

	//	�I�u�W�F�N�g�ǂݍ���
	void	EnemyManager::Load( void )
	{
		org[ENEMY_TYPE::BIG_ENEMY] = new iex3DObj( "DATA/CHR/Enemy/minotaurus.IEM" );
		org[ENEMY_TYPE::SMALL_ENEMY] = new iex3DObj( "DATA/CHR/Enemy/zako.IEM" );
	}

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------

	//	�X�V
	void	EnemyManager::Update( void )
	{
		int		enemyNum = 0;

		for ( auto it = enemylist.begin(); it != enemylist.end(); )
		{
			//	���W�`�F�b�N
			PosCheck( *it );
			PlayerPosCheck( *it );

			//	�X�V
			( *it )->Update();
		
			//	�����`�F�b�N
			bool isAlive = ( *it )->GetIsAlive();

			//	���S���Ă����烊�X�g����폜
			if ( !isAlive )
			{
				it = enemylist.erase( it );
				continue;
			}

			//	�G�����Z
			enemyNum++;

			//	����
			it++;
		}

		//	��莞�Ԃ��ƂɓG�𐶐�
		if ( enemyNum < ENEMY_MAX )	AddRegularTimeIntervals();
	}

	//	�`��
	void	EnemyManager::Render( void )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); it++ )
		{
			( *it )->Render();
		}
	}

//-------------------------------------------------------------------------------------
//	����֐�
//-------------------------------------------------------------------------------------
	
	//	���X�g�ɒǉ�
	void	EnemyManager::Append( const Vector3& pos,int type )
	{
		Enemy* enemy = nullptr;

		switch ( type )
		{
		case BIG_ENEMY:
			enemy = new BigEnemy();
			break;

		case SMALL_ENEMY:
			enemy = new SmallEnemy();
			break;

		default:
			return;
		}

		//	������
		enemy->SetObj( org[type]->Clone() );
		enemy->Initialize();
		enemy->SetPos( pos );

		//	���X�g�ɒǉ�
		enemylist.push_back( enemy );
	}

	//	���W�`�F�b�N�i �߂���Ή������� �j
	void	EnemyManager::PosCheck( Enemy* enemy )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); it++ )
		{
			//	����VS�����͏��O
			if ( ( *it ) == enemy )	continue;

			//	����������ւ̃x�N�g��
			Vector3	vec = enemy->GetPos() - ( *it )->GetPos();
			float		length = vec.Length();

			//	�߂��ꍇ�͗���
			if ( length < COLLISION_DIST )
			{
				//	�x�N�g�����K��
				vec.Normalize();

				//	����
				( *it )->SetPos( enemy->GetPos() - vec * COLLISION_DIST );
			}
		}
	}

	//	�v���C���[�Ƃ̍��W�`�F�b�N
	void	EnemyManager::PlayerPosCheck( Enemy* enemy )
	{
		//	����������ւ̃x�N�g��
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	���݃`�F�b�N
			if( !gameParam->GetPlayerActive( p ) )	continue;
			
			//	�v���C���[�ւ̃x�N�g�������߂�
			Vector3	pPos = playerManager->GetPlayer( p )->GetPos();
			Vector3	vec = pPos - enemy->GetPos();
			float		length = vec.Length();
			
			//	�߂��ꍇ�͗���
			if ( length < COLLISION_DIST )
			{
				//	�x�N�g�����K��
				vec.Normalize();

				//	����
				enemy->SetPos( pPos - vec * COLLISION_DIST );
			}
		}
	}

	//	��莞�Ԃ��ƂɓG�𐶐�
	void	EnemyManager::AddRegularTimeIntervals( void )
	{
		if ( gameManager->GetTime() % APPEND_INTERVAL != 0 )
		{
			//	�����t���O��true�ɂ���
			appendOK = true;
			return;
		}

		if ( !appendOK )	return;

		//	�o�����W�̐ݒ�
		Vector3	appendPos = Vector3(
			random->GetFloat( -20.0f, 20.0f ),
			0.0f,
			random->GetFloat( -20.0f, 20.0f ) );
		
		//	���X�g�ɒǉ�
		Append( appendPos, ENEMY_TYPE::BIG_ENEMY );

		//	�����t���O��false�ɂ���
		appendOK = false;
	}

//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	���擾
//-------------------------------------------------------------------------------------
