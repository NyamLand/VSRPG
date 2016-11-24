
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
	Player::Player( void ) : id( -1 )
	{
	}

	//	�f�X�g���N�^
	Player::~Player( void )
	{
		
	}

	//	������
	bool	Player::Initialize( int id )
	{
		//	�ǂݍ���
		Load( "DATA/CHR/suppin/Suppin.IEM" );

		//	���ݒ�
		SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		SetAngle( 0.0f );
		SetScale( PLAYER_SCALE );
		SetMotion( MOTION_NUM::POSUTURE );
		SetMode( MODE::MOVE );

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

		//----------------��-------------
		//std::fstream r("DATA\\test.csv", std::ios::in);

		//CSVReader csv(r);
		//vector<string> tokens;
		//while (!csv.Read(tokens))
		//{
		//	for (unsigned int i = 0; i<tokens.size(); i++)
		//	{
		//		if (tokens[0] == "HP")
		//		{
		//			hp = std::atoi(tokens[1].c_str());
		//		}
		//	}
		//}
		//csv.Close();
		//return 0;
		//---------------------------------


		if ( obj == nullptr )	return	false;
		return	true;
	}

	//	���

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

	//	�X�V
	void	Player::Update( PlayerParam& playerParam )
	{
		//	�T�[�o�[����̏��𔽉f
		this->playerParam = playerParam;
		SetPlayerParam( playerParam );

		//	�U�����ݒ�
		SetAttackShape();

		//	�X�V
		BaseChara::Update();
	}

	void	Player::Render( iexShader* shader, LPSTR technique )
	{
		BaseChara::Render();	

		AttackInfo attackInfo= gameParam->GetAttackInfo( id );
		//drawShape->DrawCapsule( attackInfo.pos1, attackInfo.pos2, attackInfo.radius, 0xFFFFFFFF );
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�ړ�
	bool	Player::Move( void )
	{
		return false;
	}

	//	���U��
	void	Player::SetAttackShape( void )
	{
		//	���A���[�V�����ԍ��ŃX�L�b�v
		Vector3	pos1, pos2;

		switch ( playerParam.motion )
		{
		case MOTION_NUM::ATTACK1:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::CAPSULE;
			gameParam->GetAttackInfo( id ).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo( id ).pos1 = GetBonePos( BONE_NUM::HAND );
			gameParam->GetAttackInfo( id ).pos2 = GetBonePos( BONE_NUM::SWORD );
			break;

		case MOTION_NUM::MAGIC_ACTUATION:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::SPHERE;
			gameParam->GetAttackInfo( id ).pos1 = GetBonePos( BONE_NUM::RIGHT_HAND );
			break;

		default:
			printf( "default\n" );
		}

		//	�U����񑗐M
		gameParam->SendAttackParam();
	}

	//	�e�N�X�`���ݒ�
	void	Player::ChangeTexture( int colorNum )
	{
		//	�t�@�C���ݒ�
		char	fileName[256] = "DATA/CHR/suppin/s_body_";
		char playerNum[8] = "";
		sprintf_s( playerNum, "%d.png", colorNum );
		strcat_s( fileName, playerNum );
		obj->SetTexture( 0, fileName );
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
	}

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------
