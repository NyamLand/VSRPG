
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"DrawShape.h"
#include	"NetEnemy.h"

//***************************************************************
//
//	NetEnemy�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------
#define INIT_LIFE	20
#define HALK_RADIUS	2.0f
#define	HALK_HEIGHT	4.0f
#define	DEAD_MOTION_END		960

namespace
{
	namespace MOTION_NUM
	{
		enum
		{
			POSTURE,
			POSTURE1,
			MOVE,
			ATTACK_1,
			ATTACK_2,
			ATTACK_3,
			NAZO,
			WAVE,
			DEAD
		};
	}

	namespace MOTION_FRAME
	{
		const int ATTACK_ONE_START = 348;
		const int ATTACK_ONE_END = 375;
		const int ATTACK_TWO_START = 440;
		const int ATTACK_TWO_END = 500;
		const int ATTACK_THREE_START = 530;
		const int ATTACK_THREE_END = 575;
	}
}
//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
NetEnemy::NetEnemy(void) : obj(nullptr), bar(nullptr),
		pos( 0.0f, 0.0f, 0.0f ), 
		angle( 0.0f ),
		life(0),
		isAlive( false )
	{
		ZeroMemory( &attackInfo, sizeof( attackInfo ) );
	}

	//	�f�X�g���N�^
	NetEnemy::~NetEnemy( void )
	{
		SafeDelete( obj );
		SafeDelete(bar);
	}

	//	������
	void	NetEnemy::Initialize( iex3DObj* org, const Vector3& Pos, float Angle )
	{
		life = INIT_LIFE;
		this->pos = Pos;
		this->angle = Angle;
		this->isAlive = true;
		obj = org;
		obj->SetPos( pos );
		obj->SetAngle( angle );
		org->SetScale( 0.015f );
		obj->Update();
		bar = new EnemyHpUI();
		bar->Initilaize(HPUI_TYPE::ENEMY, GetLife());
	}

//----------------------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	NetEnemy::Update( void )
	{
		//	���S���[�V������
		if ( obj->GetMotion() == MOTION_NUM::DEAD )
			Death();

		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->Update();
		obj->Animation();

		CheckAttackInfo();
	}

	//	�`��
	void	NetEnemy::Render( void )
	{
		obj->Render();
	}

	//	HP�o�[�`��
	void	NetEnemy::RenderHpBar(void)
	{
		bar->Render((float)GetLife(), GetPos(), GetUp());
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	���S
	void	NetEnemy::Death( void )
	{
		//	�t���[���擾
		int frame = obj->GetFrame();

		//	�t���[������
		if ( frame >= DEAD_MOTION_END )
		{
			//	���ߊJ�n
			isAlive = false;
		}
	}

	//	�t���[����񂩂�U������ݒ�
	void	NetEnemy::CheckAttackInfo( void )
	{
		int motion = obj->GetMotion();
		int frame = obj->GetFrame();
		if ( motion != MOTION_NUM::ATTACK_1 &&
			motion != MOTION_NUM::ATTACK_2 &&
			motion != MOTION_NUM::ATTACK_3 )	return;

		//	�U�����[�V�����Ǘ�
		if ( frame >= MOTION_FRAME::ATTACK_ONE_START && frame <= MOTION_FRAME::ATTACK_ONE_END )
		{
			//	�U����Ԃ�L���ɂ���
			attackInfo.Set( SHAPE_TYPE::CAPSULE, HALK_RADIUS, pos, pos + Vector3( 0.0f, HALK_HEIGHT, 0.0f ) );
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			//	�U����Ԃ𖳌��ɂ���
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

			//	�ʏ탂�[�h�ֈڍs
			if ( frame >= 420 )
			{
				SetMotion( MOTION_NUM::POSTURE );
			}
		}
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	���W�ݒ�
	void	NetEnemy::SetPos( const Vector3& pos )
	{
		this->pos = pos;
	}

	//	�����ݒ�
	void	NetEnemy::SetAngle( float angle )
	{
		this->angle = angle;
	}

	//	���[�V�����ݒ�
	void	NetEnemy::SetMotion( int motion )
	{
		if ( obj->GetMotion() != motion )
		{
			obj->SetMotion( motion );
		}
	}

	//	���b�V���ݒ�
	void	NetEnemy::SetMesh( iex3DObj*	mesh )
	{
		obj = mesh;
	}

	//	���S������
	void	NetEnemy::SetDeath( void )
	{
		SetMotion( MOTION_NUM::DEAD );
	}

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	���W�擾
	Vector3	NetEnemy::GetPos( void )const
	{
		return	pos;
	}

	//	����擾
	Vector3	NetEnemy::GetUp( void )const
	{
		Matrix mat = GetMatrix();
		Vector3	up = Vector3(mat._21, mat._22, mat._23);
		up.Normalize();
		return	up;
	}

	//	�s��擾
	Matrix	NetEnemy::GetMatrix( void )const
	{
		return	obj->TransMatrix;
	}