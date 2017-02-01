
#include	"iextreme.h"
#include	<vector>
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
#define	ENEMY_MAX			5
#define APPEND_RADIUS		15.0f
#define APPEND_RADIUS_		220.0f		//���w�ȊO

#define	MOFFU_INIT_LIFE	10
#define	WOLF_INIT_LIFE		20
#define SHADOW_INIT_LIFE	30

#define	MOFFU_LIFE_UP_PARAM		25
#define	WOLF_LIFE_UP_PARAM		30
#define	SHADOW_LIFE_UP_PARAM	40


#define	TIMER_RESET	10.0f
#define	MINUTE	60


//-------------------------------------------------------------------------------------
//	�������E���
//-------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	EnemyManager::EnemyManager( void ):
		appendOK( true )
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
		
		//	���C�t������
		lifeUpParam[ENEMY_TYPE::MOFFU] = MOFFU_INIT_LIFE;
		lifeUpParam[ENEMY_TYPE::WOLF] = WOLF_INIT_LIFE;
		lifeUpParam[ENEMY_TYPE::SHADOW] = SHADOW_INIT_LIFE;
		timer = new Timer();
		timer->Start( TIMER_RESET );
	
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

		SafeDelete( timer );
	}

	//	�I�u�W�F�N�g�ǂݍ���
	void	EnemyManager::Load( void )
	{
		org[ENEMY_TYPE::WOLF] = new iex3DObj( "DATA/CHR/Enemy/wolf/wolf.IEM" );
		org[ENEMY_TYPE::MOFFU] = new iex3DObj( "DATA/CHR/Enemy/mofumofu/moffu.IEM" );
		org[ENEMY_TYPE::SHADOW] = new iex3DObj("DATA/CHR/Enemy/shadow/shadow.IEM");
	}

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------

	//	�X�V
	void	EnemyManager::Update( void )
	{
		if ( timer->Update() )
		{
			if ( ( int )gameManager->GetTime() % MINUTE == 0 )
			{
				LifeUP();
			}
		}

		int		enemyNum = 0;

		for ( auto it = enemylist.begin(); it != enemylist.end(); )
		{
			//	���W�`�F�b�N
			PosCheck( *it );
			PlayerPosCheck( *it );

			//	�X�V
			( *it )->Update();
		
			//	�����`�F�b�N
			bool isAlive = ( *it )->GetLifeInfo().isAlive;

			//	���S���Ă����烊�X�g����폜
			if ( !isAlive )
			{
				//gameParam->SendHuntInfo((*it)->GetEnemyType());
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

	//	HP�`��
	void	EnemyManager::RenderHp( void )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); it++ )
		{
			( *it )->BarRender();
		}
	}

//-------------------------------------------------------------------------------------
//	����֐�
//-------------------------------------------------------------------------------------
	
	//	���X�g�ɒǉ�
	void	EnemyManager::Append( const Vector3& pos, char type )
	{
		Enemy* enemy = nullptr;

		switch ( type )
		{
		case WOLF:
			enemy = new Wolf();
			//enemy->GetLifeInfo().maxLife = 80.0f;
			break;

		case MOFFU:
			enemy = new Moffu();
			//enemy->GetLifeInfo().maxLife = 20.0f;
			break;

		case SHADOW:
			enemy = new Shadow();
			break;

		default:
			return;
		}

		//	������
		enemy->SetEnemyType( type );
		enemy->SetObj( org[type]->Clone() );
		enemy->Initialize( lifeUpParam[type] );
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
				Vector3	vec = enemy->GetPos() - (*it)->GetPos();
				vec.y = 0.0f;
				float		length = vec.Length();

				float collisionDist = enemy->GetCollisionInfo().radius + (*it)->GetCollisionInfo().radius;
				//	�߂��ꍇ�͗���
				if (length < collisionDist)
				{
					//	�x�N�g�����K��
					vec.Normalize();

					//	����
					(*it)->SetPos(enemy->GetPos() - vec * collisionDist);
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
			if (!gameParam->GetPlayerActive(p))	continue;
			if (enemy->GetMode() == enemy->MODE::DEAD)continue;

			//	�v���C���[�ւ̃x�N�g�������߂�
			Vector3	pPos = playerManager->GetPlayer(p)->GetPos();
			Vector3	vec = pPos - enemy->GetPos();
			vec.y = 0.0f;
			float		length = vec.Length();

			float collisionDist = enemy->GetCollisionInfo().radius + playerManager->GetPlayer(p)->GetCollisionInfo().radius;
			//	�߂��ꍇ�͗���
			if (length <  collisionDist)
			{
				//	�x�N�g�����K��
				vec.Normalize();

				//	����
				enemy->SetPos(pPos - vec * collisionDist);
			}
			
		
		}
	}

	//	��莞�Ԃ��ƂɓG�𐶐�
	void	EnemyManager::AddRegularTimeIntervals( void )
	{

		int id = gameParam->GetMyIndex();

		if ( ( int )gameManager->GetTime() % APPEND_INTERVAL != 0 )
		{
			//	�����t���O��true�ɂ���
			appendOK = true;
			return;
		}

		if ( !appendOK )	return;
		
		//	�o�����W�̐ݒ�
		float randX = random->GetFloat(-APPEND_RADIUS, APPEND_RADIUS);
		float randZ = random->GetFloat(-APPEND_RADIUS, APPEND_RADIUS);
		Vector3	appendPos = gameParam->GetPlayerParam(id).pos + Vector3(randX, 0.0f, randZ);

		float	length = Vector3(Vector3(0.0f, 0.0f, 0.0f) - appendPos).Length();
		if (length > APPEND_RADIUS_)	return;

		//	���X�g�ɒǉ�
		Append(appendPos, random->GetInt(WOLF, SHADOW));

		//	�����t���O��false�ɂ���
		appendOK = false;
		
	}

	//	���C�t�㏸
	void	EnemyManager::LifeUP( void )
	{
		timer->Start( TIMER_RESET );
		lifeUpParam[ENEMY_TYPE::MOFFU] += MOFFU_LIFE_UP_PARAM;
		lifeUpParam[ENEMY_TYPE::WOLF] += WOLF_LIFE_UP_PARAM;
		lifeUpParam[ENEMY_TYPE::SHADOW] += SHADOW_LIFE_UP_PARAM;
	}

//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	���擾
//-------------------------------------------------------------------------------------

	//	���X�g�擾
	list<Enemy*>&	EnemyManager::GetList( void )
	{
		return	enemylist;
	}
