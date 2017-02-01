
#include	<vector>
#include	<fstream>
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"GameParam.h"
#include	"CSVReader.h"
#include	"Sound.h"
#include	"BaseEquipment.h"
#include	"EffectManager.h"
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
#define	KNIGHT_SCALE	0.08f
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
		LEFT_HAND = 15,
		HAND = 27,
		SWORD,
		RIGHT_HAND = 35
	};

	//	�\��
	namespace FACE_TYPE
	{
		enum
		{
			NORMAL,
			DAMAGE,
			ATTACK
		};
	}

	namespace
	{
		const LPSTR fileName[] =
		{
			"DATA/CHR/suppin/Suppin.IEM",
			"DATA/CHR/Fighter/Fighter.IEM",
			"DATA/CHR/Magician/Magician.IEM",
			"DATA/CHR/Knight/Knight.IEM",
			"DATA/CHR/Prist/prist.IEM",
			"DATA/CHR/Assasin/assasin.IEM"
		};

		//	�ʏ��
		const LPSTR	normalFaceFile[] =
		{
			"DATA/CHR/suppin/face.png",
			"DATA/CHR/Fighter/face.png",
			"DATA/CHR/Magician/face.png",
			"DATA/CHR/Knight/face.png",
			"DATA/CHR/Prist/face2.png",
			"DATA/CHR/Assasin/face.png"
		};

		//	�_���[�W��
		const LPSTR	damageFaceFile[] =
		{
			"DATA/CHR/suppin/face_damage.png",
			"DATA/CHR/Fighter/face_damage.png",
			"DATA/CHR/Magician/face_damage.png",
			"DATA/CHR/Knight/face_damage.png",
			"DATA/CHR/Prist/face_damage.png",
			"DATA/CHR/Assasin/face_damage.png"
		};

		//	�U����
		const LPSTR attackFaceFile[] = 
		{
			"DATA/CHR/suppin/face_koueki.png",
			"DATA/CHR/Fighter/face_koueki.png",
			"DATA/CHR/Magician/face_koueki.png",
			"DATA/CHR/Knight/face_koueki.png",
			"DATA/CHR/Prist/face_koueki.png",
			"DATA/CHR/Assasin/face_koueki.png"
		};
	}
	
	namespace 
	{
		const LPSTR bodyTexFileName[] =
		{
			"DATA/CHR/suppin/body_",
			"DATA/CHR/Fighter/body_",
			"DATA/CHR/Magician/body_",
			"DATA/CHR/Knight/body_",
			"DATA/CHR/Prist/body_",
			"DATA/CHR/Assasin/body_"
		};
	}

	namespace
	{
		int shotBone[] =
		{
			BONE_NUM::RIGHT_HAND,
			BONE_NUM::LEFT_HAND,
			BONE_NUM::LEFT_HAND,
			BONE_NUM::LEFT_HAND,
			BONE_NUM::RIGHT_HAND,
			BONE_NUM::RIGHT_HAND,
		};
	}
}

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Player::Player( void ) : id( -1 ), curClass( CLASS_TYPE::NORMAL )
	{
		for ( int i = 0; i < CLASS_TYPE::CLASS_MAX; i++ )
		{
			org[i] = nullptr;
		}
	}

	//	�f�X�g���N�^
	Player::~Player( void )
	{
		ZeroMemory( &playerParam, sizeof( PlayerParam ) );

		for ( int i = 0; i < CLASS_TYPE::CLASS_MAX; i++ )
		{
			SafeDelete( org[i] );
		}
		
		obj = nullptr;
	}

	//	������
	bool	Player::Initialize( int id )
	{
		this->id = id;

		//	���f���ǂݍ���
		Load();
		obj = org[CLASS_TYPE::NORMAL];

		//	���ݒ�
		SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		SetAngle( 0.0f );
		SetScale( PLAYER_SCALE );
		SetMode( MODE::MOVE );
		SetMotion(MOTION_NUM::POSUTURE );
		lifeInfo.Initialize( MAX_LIFE );

		//	�����蔻��`��ݒ�
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, PLAYER_HEIGHT, PLAYER_RADIUS );

		//	�ϐ�������
		speed = MOVE_SPEED;
		lifeInfo.active = true;
		lifeInfo.isAlive = true;

		//	���X�V
		UpdateInfo();

		//	�o�[������
		bar = new EnemyHpUI();
		bar->Initilaize( HPUI_TYPE::PLAYER, gameParam->GetPlayerStatus().maxLife );
		bar->SetId( id );

		if ( obj == nullptr )	return	false;
		return	true;
	}

	//	�ǂݍ���
	void	Player::Load( void )
	{
		for ( int i = 0; i < CLASS_TYPE::CLASS_MAX; i++ )
		{
			if ( org[i] == nullptr )
			{ 
				org[i] = new iex3DObj( fileName[i] );
				org[i]->SetScale( PLAYER_SCALE );
				org[i]->SetPos( 0.0f, 0.0f, 0.0f );
				org[i]->SetAngle( 0.0f );
				org[i]->SetMotion( MOTION_NUM::POSUTURE );
				ChangeTexture( org[i], ( char)i, id );
				org[i]->Update();
			}
		}
	}

	//	�e�N�X�`���ݒ�
	void	Player::ChangeTexture( iex3DObj*& model, char classType, int id )
	{
		//	�t�@�C���ݒ�
		char str[50] = "";
		sprintf_s( str, bodyTexFileName[classType] );
		
		//	�v���C���[�ԍ��ݒ�
		char pNum[10] = "";
		sprintf_s( pNum, "%d.png", id + 1 );

		//	�A��
		strcat_s( str, pNum );
		if ( classType == CLASS_TYPE::ASSASSIN )
		{
			model->SetTexture( 1, str );
		}
		else model->SetTexture( 0, str );

		if ( classType == CLASS_TYPE::FIGHTER )
		{
			sprintf_s( str, "" );
			sprintf_s( str, "DATA/CHR/Fighter/toumeitachi_%d.png", id + 1 );
			model->SetTexture( 3, str );
		}
	}

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


		//	���@�r�����Ȃ�`��
		if (obj->GetMotion() == MOTION_NUM::MAGIC_CHANT)
		{
			effectManager->SetCircleRender(id);
		}

		//	���G��ԃ`�F�b�N
		CheckUnrivaled();
		
		//	�X�V
		BaseChara::Update();
	}

	//	�`��
	void	Player::Render( iexShader* shader, LPSTR technique )
	{
		shader->SetValue( "effParam", 1.0f - gameParam->GetPlayerParam( id ).effParam );

		//	���f���`��
		BaseChara::Render( shader, technique );	
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

		case MOTION_NUM::ATTACK2:
			gameParam->GetAttackInfo(id).shape = SHAPE_TYPE::CAPSULE;
			gameParam->GetAttackInfo(id).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo(id).vec1 = GetBonePos(BONE_NUM::HAND);
			gameParam->GetAttackInfo(id).vec2 = GetBonePos(BONE_NUM::SWORD);
			break;

		case MOTION_NUM::MAGIC_ACTUATION:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::SPHERE;
			gameParam->GetAttackInfo( id ).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo( id ).vec1 = GetBonePos( shotBone[curClass] );
			gameParam->GetAttackInfo( id ).vec2 = GetFront();
			break;

		default:
			return;
		}

		//	��񑗐M
		gameParam->SendAttackParam();
	}

	//	���[�V�����؂芷������SE�ݒ�
	void	Player::PlaySE( int motion )
	{
		switch ( motion )
		{
			case MOTION_NUM::ATTACK1:
			case MOTION_NUM::ATTACK2:
				sound->PlaySE( SE::ATTACK );
				break;

			case MOTION_NUM::STEP:
				sound->PlaySE(SE::STEP);
				break;

			/*case MOTION_NUM::LEVEL_UP:
				sound->PlaySE(SE::LVUP);
				break;*/

			case MOTION_NUM::DEAD:
				sound->PlaySE(SE::PLAYER_DEAD);
				break;

			case MOTION_NUM::MAGIC_CHANT:
				sound->PlaySE(SE::MAGIC_CHARGE);
				break;

			//�@���j���[�J���������Ȃ��@
			case MOTION_NUM::MENU:
				sound->PlaySE(SE::OK);
				break;

			default:
				break;
		}
	
	}

	//	���f���`�F���W
	void	Player::ChangeModel( char nextClass )
	{
		//	�N���X�ݒ�
		curClass = nextClass;

		//	���ړ�
		obj = org[curClass];
		
		SetPos( pos );
		SetAngle( angle );
		SetMotion( gameParam->GetPlayerParam( id ).motion );
		SetScale( PLAYER_SCALE );
		sound->PlaySE(SE::MAX_UPGRADE);
		if (curClass == CLASS_TYPE::KNIGHT)	SetScale(KNIGHT_SCALE);
		if (curClass == CLASS_TYPE::ASSASSIN)	SetScale(KNIGHT_SCALE);
		obj->Update();
	}

	//	�\��ύX
	void	Player::ChangeFaceTexture( char faceType )
	{
		switch ( faceType )
		{
		case FACE_TYPE::NORMAL:
			if (curClass == CLASS_TYPE::FIGHTER || curClass == CLASS_TYPE::MAGICIAN)
				obj->SetTexture( 2, normalFaceFile[curClass] );
			else if (curClass == CLASS_TYPE::ASSASSIN)
			{
				obj->SetTexture( 0, normalFaceFile[curClass] );
				//obj->SetTexture( 2, normalFaceFile[curClass] );
			}
			else
				obj->SetTexture( 1, normalFaceFile[curClass] );
			break;

		case FACE_TYPE::DAMAGE:
			if (curClass == CLASS_TYPE::FIGHTER || curClass == CLASS_TYPE::MAGICIAN)
				obj->SetTexture( 2, damageFaceFile[curClass] );
			else if (curClass == CLASS_TYPE::ASSASSIN)
			{
				obj->SetTexture( 0, damageFaceFile[curClass]);
				//obj->SetTexture( 2, damageFaceFile[curClass] );
			}
			else
				obj->SetTexture( 1, damageFaceFile[curClass] );
			break;

		case FACE_TYPE::ATTACK:
			if ( curClass == CLASS_TYPE::FIGHTER || curClass == CLASS_TYPE::MAGICIAN )
				obj->SetTexture( 2, attackFaceFile[curClass] );
			else if (curClass == CLASS_TYPE::ASSASSIN)
			{
				obj->SetTexture( 0, attackFaceFile[curClass] );
				//obj->SetTexture( 2, attackFaceFile[curClass] );
			}
			else
				obj->SetTexture(1, attackFaceFile[curClass]);
			break;

		default:
			break;
		}
	}

	//	���[�V�����ɑΉ������\��ύX
	void	Player::ChangeFaceType( int motion )
	{
		switch ( motion )
		{
			//	�_���[�W��
		case MOTION_NUM::KNOCKBACK1:
		case MOTION_NUM::KNOCKBACK2:
		case MOTION_NUM::DEAD:
		case MOTION_NUM::FALL:
			ChangeFaceTexture( FACE_TYPE::DAMAGE );
			break;

			//	�U����
		case MOTION_NUM::ATTACK1:
		case MOTION_NUM::ATTACK2:
		case MOTION_NUM::MAGIC_ACTUATION:
			ChangeFaceTexture( FACE_TYPE::ATTACK );
			break;

		default:
			ChangeFaceTexture( FACE_TYPE::NORMAL );
			break;
		}
	}

	//	���G��ԃ`�F�b�N
	void	Player::CheckUnrivaled( void )
	{
		switch ( obj->GetMotion() )
		{
		case MOTION_NUM::KNOCKBACK1:
		case MOTION_NUM::FALL:
		case MOTION_NUM::DEAD:
			lifeInfo.active = false;
			break;

		default:
			if ( gameParam->GetPlayerParam( id ).effParam < 1.0f )
			{
				lifeInfo.active = false;
			}
			else lifeInfo.active = true;
		}

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

	//	���[�V�����ݒ�
	void	Player::SetMotion( int motion )
	{
		if ( obj->GetMotion() != motion )
		{
			obj->SetMotion( motion );
			PlaySE( motion );
			ChangeFaceType( motion );
		}
	}

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------
