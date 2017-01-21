
#include	"iextreme.h"
#include	"GameParam.h"

#include	"Enemy.h"

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

#define	ANGLEADJUST_SPEED 1.0f
#define	MOVE_SPEED	20.0f

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Enemy::Enemy( void ): timer( nullptr ),
		targetPos( 0.0f, 0.0f, 0.0f ), move( 0.0f, 0.0f, 0.0f ),
		interpolationParam( 0.0f ), searchDist( 0.0f ), attackDist( 0.0f ), count( 40 ),
		alive( true )
	{
		ZeroMemory( &lifeInfo, sizeof( lifeInfo ) );
		ZeroMemory( &enemyParam, sizeof( enemyParam ) );
		timer = new Timer();
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

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------
	
	//	�ړ�
	void	Enemy::Move( void )
	{
		Vector3	target;

		//	�v���C���[�����m�͈͂ɂ���΍s���J�n
		if ( DistCheck( target ) )
		{
			//	�v���C���[�̕�������
			AngleAdjust( target, ANGLEADJUST_SPEED );

			//	�����Ă�����ɑO�i
			Advance();
		}
	}

	//	�O�i
	void	Enemy::Advance( void )
	{
		Vector3	moveVec = Vector3( sinf( angle ), 0.0f, cosf( angle ) );
		move = moveVec * MOVE_SPEED;
	}

	//	�v���C���[�Ƃ̋����`�F�b�N
	bool	Enemy::DistCheck( Vector3& target )
	{
		float length = 500.0f;
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			//	��A�N�e�B�u�̃v���C���[�̓X�L�b�v
			if ( gameParam->GetPlayerActive( i ) )	continue;
			target = gameParam->GetPlayerParam( i ).pos - enemyParam.pos;

			//	�Ƃ肠������ԋ߂��l�̒�����ۑ�
			if ( target.Length() < length )
			{
				length = target.Length();
			}
		}
		target.Normalize();

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
	void	Enemy::AddMove( void )
	{
		enemyParam.pos += move * timer->GetErapseTime();
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
//	����֐�
//------------------------------------------------------------------------------------
	
	//	�X�V
	void	Enemy::Update( void )
	{
		//	�ʏ�ړ�
		Move();

		//	�ړ��l���Z
		AddMove();
	}

//------------------------------------------------------------------------------------
//	���[�h�֐�
//------------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

	int	Enemy::GetMode( void )const
	{
		return mode;
	}

	bool	Enemy::GetAlive( void )const
	{
		return	alive;
	}