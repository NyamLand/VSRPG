
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"GameParam.h"
#include	"Sound.h"
#include	"PlayerManager.h"
#include	"Collision.h"

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
#define	DEAD_LENGTH	30.0f

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Enemy::Enemy( void ):
		targetPos( 0.0f, 0.0f, 0.0f ),
		interpolationParam(0.0f), searchDist(0.0f), attackDist(0.0f), count(40)
	{
	}

	//	�f�X�g���N�^
	Enemy::~Enemy( void )
	{

	}

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------
	
	//	�ړ�
	void	Enemy::Move( float speed )
	{
		float	length = 0.0f;
		if ( DistCheck( length ) )	return;

		if ( length <= searchDist )
		{
			//	�v���C���[�̕�������
			FacingPlayer();

			//	�����Ă�����ɑO�i
			Advance( speed );
		}
		else
		{
			//	���[�V�����ݒ�
			SetMotion( 0 );	//	�ҋ@���[�V����
		}
	}

	//	�v���C���[�̕�������
	void	Enemy::FacingPlayer( void )
	{
		//	�v���C���[�ւ̃x�N�g�������߂�
		int id = gameParam->GetMyIndex();
		Vector3	targetVec = playerManager->GetPlayer( id )->GetPos() - pos;
		targetVec.Normalize();

		AngleAdjust( targetVec, ANGLEADJUST_SPEED );
	}

	//	�O�i
	void	Enemy::Advance( float speed )
	{
		SetMotion( 1 );
		Vector3	moveVec = Vector3( sinf( angle ), 0.0f, cosf( angle ) );
		SetMove( moveVec * speed );
	}

	//	�v���C���[�Ƃ̋����`�F�b�N
	bool	Enemy::DistCheck( float& length )
	{
		Vector3	vec = playerManager->GetPlayer( gameParam->GetMyIndex() )->GetPos() - pos;
		length = vec.Length();

		//	���̋����܂ŋ߂Â��ƍU��
		if ( length <= attackDist )
		{
			SetMode( MODE::ATTACK );
			return	true;
		}

		else if (length>DEAD_LENGTH)
		{
			SetMode(MODE::DEAD);
		}
		return false;
	}

	//	���C�t�`�F�b�N�i �O�ȉ��Ȃ玀�S���[�h�Ɉڍs �j
	void	Enemy::LifeCheck( void )
	{
		if ( !lifeInfo.active )	return;

		if ( lifeInfo.life <= 0 )
		{
			lifeInfo.active = false;
			sound->PlaySE(SE::ENEMY_DEAD);
			SetMode( MODE::DEAD );

			//	������񑗐M
			SendHuntInfo();
		}
	}

	//	���������i �J�����e���Ȃ� �j
	void	Enemy::AngleAdjust( const Vector3& moveVec, float adjustSpeed )
	{
		//	�ړ����������߂�
		float	moveAngle = atan2f( moveVec.x, moveVec.z );

		//	�e�ɓ�����
		AngleAdjustParent(
			Vector3( sinf( moveAngle ), 0.0f, cosf( moveAngle ) ),
			adjustSpeed);
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------
	void	Enemy::Update()
	{

	}

	void	Enemy::StageCheck()
	{

	}

	//	���M
	void	Enemy::SendHuntInfo( void )
	{
		static	struct 
		{
			char com;
			char infoType;
			char enemyType;
		} sendInfo;

		//	���ݒ�
		sendInfo.com = SEND_COMMAND::ENEMY_INFO;
		sendInfo.infoType = SEND_ENEMY_COMMAND::SMALL_ENEMY_HUNT;
		sendInfo.enemyType = enemyType;

		//	���M
		gameParam->send( ( char* )&sendInfo, sizeof( sendInfo ) );
	}

//------------------------------------------------------------------------------------
//	���[�h�֐�
//------------------------------------------------------------------------------------

	//��(��ŏ���)
	void	Enemy::DamageMode(void)
	{
		lifeInfo.active = false;
		count--;
		if (count <= 0){
			count = 40;
			lifeInfo.active = true;
			SetMode(MODE::MOVE);
		}

	}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------
	
	//	�^�[�Q�b�g�̈ʒu��ݒ�
	void	Enemy::SetTargetPos( const Vector3& pos )
	{
		targetPos = pos;
	}

	//	�G�^�C�v�ݒ�
	void	Enemy::SetEnemyType( char enemyType )
	{
		this->enemyType = enemyType;
	}
	
//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

	//	�G�^�C�v�擾
	char	Enemy::GetEnemyType( void )const
	{
		return	enemyType;
	}

	int		Enemy::GetMode( void )const
	{
		return mode;
	}