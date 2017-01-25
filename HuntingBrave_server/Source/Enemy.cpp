
#include	"iextreme.h"
#include	"GameParam.h"
#include	"GlobalFunction.h"
#include	"Random.h"

#include	"Enemy.h"

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

#define	MINOTAURUS_HEIGHT	2.0f
#define	MINOTAURUS_RADIUS	1.5f

#define	ANGLEADJUST_SPEED 1.0f
#define	MOVE_SPEED	10.0f
#define	SEARCH_DIST	10.0f
#define	ATTACK_DIST	5.0f

namespace
{
	namespace MOTION_NUM
	{
		enum
		{
			POSTURE,	//	�ҋ@���[�V����
			MOVE = 2,	//	�ړ����[�V����
			ATTACK,		//	�U�����[�V����
			ATTACK2 = 5	//	�U�����[�V����
		};
	}

	namespace SEND_INFO_TYPE
	{
		enum
		{
			MOVE,
			MODE,
			MOTION,
			DEAD
		};
	}
}

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Enemy::Enemy( void ): timer( nullptr ),
		target( 0.0f, 0.0f, 0.0f ),
		deltaTime( 0.0f ),
		searchDist( SEARCH_DIST ),
		index( -1 ),
		alive( true ), atkFlag( false ), allState( false )
	{
		//	�\���̏�����
		ZeroMemory( &lifeInfo, sizeof( lifeInfo ) );
		ZeroMemory( &enemyParam, sizeof( enemyParam ) );

		//	�R���W�������ݒ�
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, MINOTAURUS_HEIGHT, MINOTAURUS_RADIUS );
		
		//	�^�C�}�[������
		timer = new Timer();

		//	�֐��|�C���^�ݒ�
		ModeFunction[MODE::ENTRY] = &Enemy::EntryMode;
		ModeFunction[MODE::MOVE] = &Enemy::MoveMode;
		ModeFunction[MODE::ATTACK] = &Enemy::AttackMode;

		mode = MODE::ENTRY;
	}

	//	�f�X�g���N�^
	Enemy::~Enemy( void )
	{
		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}
	}

	//	�N���C�A���g��񏉊���
	void	Enemy::ClientStateInitialize( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			clientState[i] = false;
		}
	}

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

	//	�X�V
	void	Enemy::Update( int index, float deltaTime )
	{
		this->index = index;
		this->deltaTime = deltaTime;

		//	����֐�
		( this->*ModeFunction[mode] )();

		SendEnemyInfo();
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------
	
	//	�ړ�
	void	Enemy::Move( void )
	{
		//	�v���C���[�����m�͈͂ɂ���΍s���J�n
		if ( DistCheck( target, atkFlag ) )
		{
			if ( !atkFlag )
			{
				//	�v���C���[�̕�������
				target.Normalize();
				AngleAdjust( target, ANGLEADJUST_SPEED );

				//	�����Ă�����ɑO�i
				Advance();
			}
			else
			{
				//	�U����
				SetMotion( MOTION_NUM::ATTACK );
			}
		}
		else
		{
			//	�ҋ@���[�V����
			SetMotion( MOTION_NUM::POSTURE );
		}
	}

	//	�O�i
	void	Enemy::Advance( void )
	{
		SetMotion( MOTION_NUM::MOVE );
		Vector3	moveVec = Vector3( sinf( enemyParam.angle ), 0.0f, cosf( enemyParam.angle ) );
		AddMove( moveVec * MOVE_SPEED );
	}

	//	�v���C���[�Ƃ̋����`�F�b�N
	bool	Enemy::DistCheck( Vector3& target, bool& attackFlag )
	{
		float length = 500.0f;
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			//	��A�N�e�B�u�̃v���C���[�̓X�L�b�v
			if ( gameParam->GetPlayerActive( i ) == false )	continue;
			target = gameParam->GetPlayerParam( i ).pos - enemyParam.pos;

			//	�Ƃ肠������ԋ߂��l�̒�����ۑ�
			if ( target.Length() < length )
			{
				length = target.Length();
			}
		}
		target.Normalize();

		//	�U���t���O�ݒ�
		if ( length <= ATTACK_DIST )	attackFlag = true;
		else attackFlag = false;

		//	���̋����܂ŋ߂Â��Ɗ��m
		if ( length <= searchDist )	return	true;
		return false;
	}

	//	���C�t�`�F�b�N�i �O�ȉ��Ȃ玀�S���[�h�Ɉڍs �j
	void	Enemy::LifeCheck( void )
	{
		if ( !lifeInfo.active )	return;

		if ( lifeInfo.life <= 0 )
		{
			lifeInfo.active = false;
			SetMode( MODE::DEAD );
		}
	}
	
	//	�ړ��l���Z
	void	Enemy::AddMove( const Vector3& move )
	{
		enemyParam.pos += move * deltaTime;
	}

	//	���������i �J�����e���Ȃ� �j
	void	Enemy::AngleAdjust( const Vector3& moveVec, float adjustSpeed )
	{
		//	�ړ����������߂�
		float	moveAngle = atan2f( moveVec.x, moveVec.z );

		//	�e�ɓ�����
		AngleAdjustParent(
			Vector3( sinf( moveAngle ), 0.0f, cosf( moveAngle ) ),
			adjustSpeed );
	}

	//	���������i�e�j
	void	Enemy::AngleAdjustParent( const Vector3& direction, float adjustSpeed )
	{
		//	���݂̌����ƖڕW�̌����̍������߂�
		float	targetAngle( atan2f( direction.x, direction.z ) );

		//	�p�x�������߂�
		float	dAngle( targetAngle - enemyParam.angle );

		//	���̐��K��
		if ( dAngle > 1.0f * D3DX_PI )		dAngle -= 2.0f * D3DX_PI;
		if ( dAngle < -1.0f * D3DX_PI )	dAngle += 2.0f * D3DX_PI;

		//	����speed���k�߂�
		if ( dAngle > 0.0f )
		{
			dAngle -= adjustSpeed;
			if ( dAngle < 0.0f )	dAngle = 0.0f;
		}
		else
		{
			dAngle += adjustSpeed;
			if ( dAngle > 0.0f )	dAngle = 0.0f;
		}

		enemyParam.angle = targetAngle - dAngle;

		//	�L�����N�^�[�̌�����PI�ȏ�ɂȂ�Ȃ��悤�ɂ���
		if ( enemyParam.angle >= 1.0f * D3DX_PI )  		enemyParam.angle -= 2.0f * D3DX_PI;
		if ( enemyParam.angle <= -1.0f * D3DX_PI )		enemyParam.angle += 2.0f * D3DX_PI;
	}

//------------------------------------------------------------------------------------
//	���[�h�ʓ���֐�
//------------------------------------------------------------------------------------
	
	//	�o�����[�h
	void	Enemy::EntryMode( void )
	{
		if ( CheckState() )
		{
			//	�N���C�A���g��񏉊���
			ClientStateInitialize();
			
			//	�ړ����[�h�ɕύX
			SetMode( MODE::MOVE );
		}
	}
	
	//	�ړ����[�h
	void	Enemy::MoveMode( void )
	{
		//	�v���C���[�����m�͈͂ɂ���΍s���J�n
		if ( DistCheck( target, atkFlag ) )
		{
			if ( !atkFlag )
			{
				//	�v���C���[�̕�������
				target.Normalize();
				AngleAdjust( target, ANGLEADJUST_SPEED );

				//	�����Ă�����ɑO�i
				Advance();
			}
			else
			{
				//	�U����
				SetMotion( MOTION_NUM::ATTACK );

				SetMode( MODE::ATTACK );
			}
		}
		else
		{
			//	�ҋ@���[�V����
			SetMotion( MOTION_NUM::POSTURE );
		}
	}

	//	�U�����[�h
	void	Enemy::AttackMode( void )
	{
		if ( CheckState() )
		{
			//	�N���C�A���g��񏉊���
			ClientStateInitialize();

			//	�ʏ탂�[�h��
			SetMode( MODE::MOVE );
		}
	}

//------------------------------------------------------------------------------------
//	�N���C�A���g���
//------------------------------------------------------------------------------------

	//	�N���C�A���g����M
	void	Enemy::ReceiveClientState( int client )
	{
		clientState[client] = true;
	}

	//	�N���C�A���g�̏�Ԃ��`�F�b�N
	bool	Enemy::CheckState( void )
	{
		allState = false;
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( !gameParam->GetPlayerActive( p ) )	continue;
			else
			{
				allState = clientState[p];
				if ( !allState ) 	break;
			}
		}

		return	allState;
	}

	//	���[�h�؂�ւ����M
	void	Enemy::SendMode( char nextMode )
	{
		//	���ݒ�
		static	struct
		{
			char com;
			char infoType;
			char enemyIndex;
			char nextMode;
		} sendInfo;

		sendInfo.com = SEND_COMMAND::ENEMY_INFO;
		sendInfo.infoType = SEND_INFO_TYPE::MODE;
		sendInfo.enemyIndex = index;
		sendInfo.nextMode = nextMode;

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) == false )	continue;
			gameParam->send( p, ( char* )&sendInfo, sizeof( sendInfo ) );
		}
	}

	//	���[�V�����؂�ւ����M
	void	Enemy::SendMotion( int motion )
	{
		//	���ݒ�
		static struct
		{
			char com;
			char infoType;
			char enemyIndex;
			int motion;
		} sendInfo;

		sendInfo.com = SEND_COMMAND::ENEMY_INFO;
		sendInfo.infoType = SEND_INFO_TYPE::MOTION;
		sendInfo.enemyIndex = index;
		sendInfo.motion = motion;
		
		//	���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) == false )	continue;
			gameParam->send( p, ( char* )&sendInfo, sizeof( sendInfo ) );
		}
	}

	//	�ʏ�G��񑗐M
	void	Enemy::SendEnemyInfo( void )
	{
		//	�\���̐錾
		static	struct
		{
			char com;
			char infoType;
			int enemyIndex;
			Vector3	pos;
			float			angle;
		} enemyInfo;

		//	���ݒ�
		enemyInfo.com = SEND_COMMAND::ENEMY_INFO;
		enemyInfo.infoType = SEND_INFO_TYPE::MOVE;
		enemyInfo.enemyIndex = index;
		enemyInfo.pos = enemyParam.pos;
		enemyInfo.angle = enemyParam.angle;

		if ( index == -1 )
		{
			int a = 0;
		}

		//	���M
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( char* )&enemyInfo, sizeof( enemyInfo ) );
		}
	}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

	//	���W�ݒ�
	void	Enemy::SetPos( const Vector3& pos )
	{
		enemyParam.pos = pos;
	}

	//	�����ݒ�
	void	Enemy::SetAngle( float angle )
	{
		enemyParam.angle = angle;
	}

	//	���[�V�����ݒ�
	void	Enemy::SetMotion( int motion )
	{
		if ( enemyParam.motion != motion )
		{
			enemyParam.motion = motion;
			SendMotion( motion );
		}
	}

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

	//	���W�擾
	Vector3	Enemy::GetPos( void )const
	{
		return	enemyParam.pos;
	}

	//	�����擾
	float			Enemy::GetAngle( void )const
	{
		return	enemyParam.angle;
	}

	//	���[�V�����擾
	int			Enemy::GetMotion( void )const
	{
		return	enemyParam.motion;
	}

	int	Enemy::GetMode( void )const
	{
		return mode;
	}

	bool	Enemy::GetAlive( void )const
	{
		return	alive;
	}