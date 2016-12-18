
#include	<vector>
#include	<fstream>
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"GameParam.h"
#include	"CSVReader.h"
#include	"BaseEquipment.h"
#include	"Player.h"

//***************************************************************
//
//	Player�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//	���f�����
#define	PLAYER_SCALE	0.2f
#define	PLAYER_HEIGHT		2.5f
#define	PLAYER_RADIUS		1.5f
#define	ATTACK_RADIUS		0.5f

//	����X�s�[�h
#define	ANGLE_ADJUST_MOVE_SPEED	0.3f
#define	ANGLE_ADJUST_MAGIC_SPEED	0.05f
#define	MOVE_SPEED		0.1f

//	���͏��
#define	MIN_INPUT_STICK		0.3f

//	���C�t�ݒ�
#define MAX_LIFE	5


//	�萔�֘A
namespace
{
	//	�{�[���ԍ�
	enum BONE_NUM
	{
		HAND = 27,
		SWORD,
		RIGHT_HAND = 35
	};
}

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Player::Player( void ) : nextObj( nullptr ),
		id( -1 )
	{
		
	}

	//	�f�X�g���N�^
	Player::~Player( void )
	{
		SafeDelete( nextObj );
	}

	//	������
	bool	Player::Initialize( int id )
	{
		//	���ݒ�
		SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		SetAngle( 0.0f );
		SetScale( PLAYER_SCALE );
		SetMotion( MOTION_NUM::POSUTURE );
		SetMode( MODE::MOVE );
		lifeInfo.Initialize( MAX_LIFE );

		//	�����蔻��`��ݒ�
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, PLAYER_HEIGHT, PLAYER_RADIUS );

		//	�ϐ�������
		this->id = id;
		speed = MOVE_SPEED;
		lifeInfo.active = true;
		lifeInfo.isAlive = true;

		//	�e�N�X�`����������
		ChangeTexture( id );
		
		//	���X�V
		UpdateInfo();

		//	�o�[������
		bar = new EnemyHpUI();
		bar->Initilaize( HPUI_TYPE::PLAYER, GetLifeInfo().maxLife );
		bar->SetId( id );

		if ( obj == nullptr )	return	false;
		return	true;
	}

	//	���

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

	//	�X�V
	void	Player::Update( void )
	{
		//	���擾
		playerParam = gameParam->GetPlayerParam( id );

		//	�U�����ݒ�
		SetAttackShape();

		//	�����蔻��`��ݒ�
		SetCollisionShape( playerParam );

		//	�T�[�o�[����̏��𔽉f
		SetPlayerParam( playerParam );

		//	�X�V
		BaseChara::Update();
	}

	//	�`��
	void	Player::Render( iexShader* shader, LPSTR technique )
	{
		BaseChara::Render();	
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	���U��
	void	Player::SetAttackShape( void )
	{
		//	���A���[�V�����ԍ��ŃX�L�b�v
		switch ( playerParam.motion )
		{
		case MOTION_NUM::ATTACK1:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::CAPSULE;
			gameParam->GetAttackInfo( id ).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo( id ).vec1 = GetBonePos( BONE_NUM::HAND );
			gameParam->GetAttackInfo( id ).vec2 = GetBonePos( BONE_NUM::SWORD );
			break;

		case MOTION_NUM::MAGIC_ACTUATION:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::SPHERE;
			gameParam->GetAttackInfo( id ).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo( id ).vec1 = GetBonePos( BONE_NUM::RIGHT_HAND );
			gameParam->GetAttackInfo( id ).vec2 = GetFront();
			break;

		default:
			return;
		}

		//	��񑗐M
		gameParam->SendAttackParam();
	}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

	//	�p�����[�^�ݒ�
	void	Player::SetPlayerParam( const PlayerParam& playerParam )
	{
		pos = playerParam.pos;
		angle = playerParam.angle;
		SetMotion( playerParam.motion );
		lifeInfo.life = ( playerParam.life );
	}

	//	�R���W�����`��ݒ�
	void	Player::SetCollisionShape( const PlayerParam& playerParam )
	{
		collisionInfo.collisionShape.capsule = Capsule(
			Vector3( playerParam.pos.x, playerParam.pos.y + collisionInfo.radius, playerParam.pos.z ),
			Vector3( playerParam.pos.x, playerParam.pos.y + collisionInfo.height + collisionInfo.radius, playerParam.pos.z ),
			collisionInfo.radius );
	}

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------
