
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
	};
}

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Player::Player( void ) : id( -1 )
	{
		//	�֐��|�C���^
		ModeFunction[MODE::MOVE] = &Player::MoveMode;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;
		ModeFunction[MODE::AVOID] = &Player::ModeAvoid;
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
		attackInfo.power = 1;
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

		//	���U��
		SwordAttack();

		//	�X�V
		BaseChara::Update();
	}

	void	Player::Render( iexShader* shader, LPSTR technique )
	{
		BaseChara::Render();		
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�ړ����[�h����
	void	Player::MoveMode( void )
	{
		//	�ړ����[�V�����ݒ�
		Move();
	}

	void	Player::ModeSwordAttack( void )
	{
		bool param = SwordAttack();

		if( param )	SetMode( MODE::MOVE );
	}

	void	Player::ModeMagicAttack( void )
	{
		bool param = MagicAttack();
		if( param )SetMode( MODE::MOVE );
	}

	void	Player::ModeAvoid( void )
	{
		bool param = Avoid();
		if( param )SetMode( MODE::MOVE );
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�ړ�
	bool		Player::Move( void )
	{
		//float x, y, length;
		//length = gameParam->GetStickInput( x, y );

		//if ( length >= MIN_INPUT_STICK )	SetMotion( MOTION_NUM::RUN );
		//else SetMotion( MOTION_NUM::POSUTURE );
		return false;
	}

	//���U��
	bool		Player::SwordAttack( void )
	{
		//	�U�����[�V�����ȊO�Ȃ�X�L�b�v
		if ( GetMotion() != MOTION_NUM::ATTACK1 )
		{
			attackInfo.Reset();
			return false;
		}

		//	�U�����ݒ�
		int	frame = obj->GetFrame();

		if ( frame >= 170 && frame <= 180 )
		{
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;
		}
		
		//	�{�[���̍��W�擾�A�����蔻��p�\���̂ɃZ�b�g
		Vector3	handPos = GetBonePos( BONE_NUM::HAND );
		Vector3	swordPos = GetBonePos( BONE_NUM::SWORD );
		attackInfo.collisionShape.SetCapsule( Capsule( handPos, swordPos, 1.0f ) );

		return false;
	}

	//���@�U��
	bool		Player::MagicAttack( void )
	{
		SetMotion( MOTION_NUM::MAGIC_CHANT );		//��

		if ( !attackInfo.initFlag )
		{
			attackInfo.initFlag = true;
			attackInfo.timer = 0;
			move = Vector3( 0, 0, 0 );
		}

		//	���X�e�B�b�N�̓��̓`�F�b�N
		float	axisX = ( float )input[0]->Get( KEY_AXISX );
		float	axisY = -( float )input[0]->Get( KEY_AXISY );
		float	length = sqrtf( axisX * axisX + axisY * axisY ) * 0.001f;
		switch ( attackInfo.step )
		{
		case 0:

			//	���͂������
			if ( length >= MIN_INPUT_STICK )
			{
				//	��������
				AngleAdjust(
					Vector3( axisX, 0.0f, axisY ),
					ANGLE_ADJUST_MAGIC_SPEED );

				//if (axisX > 0)	angle += 0.1f; 
				//else			angle -= 0.1f;
			}


			if ( KEY_Get( KEY_B ) == 2 ) attackInfo.step++;
			break;
		case 1:
			attackInfo.timer++;		//�d��
			SetMotion( MOTION_NUM::MAGIC_CHANT );
			if (attackInfo.timer > 100)
			{
				attackInfo.initFlag = false;
				return true;
			}
		}
		return false;
	}

	//���
	bool		Player::Avoid( void )
	{
		Vector3 front = GetFront();
		SetMotion( MOTION_NUM::STEP );

		if ( !attackInfo.initFlag )
		{
			attackInfo.initFlag = true;
			attackInfo.timer = 0;
			move.x += front.x * 1.1f;
			move.z += front.z * 1.1f;
		}

		attackInfo.timer++;

		if (attackInfo.timer > 30)
		{
			attackInfo.initFlag = false;
			return true;
		}


		return false;
	}

	//	�e�N�X�`���ݒ�
	void		Player::ChangeTexture( int colorNum )
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
