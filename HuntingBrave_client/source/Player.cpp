
#include	<vector>
#include	<fstream>
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Player.h"
#include	"CSVReader.h"
#include	"BaseEquipment.h"

//***************************************************************
//
//	Player�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//	���f�����
#define	Y2009_SCALE	0.02f

//	����X�s�[�h
#define	ANGLE_ADJUST_MOVE_SPEED	0.3f
#define	ANGLE_ADJUST_MAGIC_SPEED	0.05f
#define	MOVE_SPEED		0.5f

//	���͏��
#define	MIN_INPUT_STICK		0.3f

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
Player::Player(void) : texture(nullptr)
	{
	
	}

	//	�f�X�g���N�^
	Player::~Player( void )
	{
		SafeDelete( texture );
	}

	//	������
	bool	Player::Initialize( void )
	{
		//	�ǂݍ���
		Load( "DATA/CHR/Y2009/Y2009.IEM" );

		SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		SetAngle( 0.0f );
		SetScale( Y2009_SCALE );
		SetMotion( 1 );	//	���l��
		speed = MOVE_SPEED;
		SetMode(MODE::MOVE);

		//	�e�N�X�`���e�X�g
		obj->SetTexture( 0, "DATA/CHR/Y2009/testTexture.png" );

		//	�֐��|�C���^
		ModeFunction[MODE::MOVE] = &Player::MoveMode;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;
		ModeFunction[MODE::AVOID] = &Player::ModeAvoid;

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
	void	Player::Update( void )
	{
		//	�e���[�h�ɉ���������֐�
		( this->*ModeFunction[mode] )();

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
		//	�X�e�B�b�N�ɂ��ړ�
		Move();
		if ( KEY_Get( KEY_A ) == 3 ) SetMode( MODE::SWOADATTACK );		//��
		if ( KEY_Get( KEY_B ) == 3 ) SetMode( MODE::MAGICATTACK );
		if ( KEY_Get( KEY_C ) == 3 ) SetMode( MODE::AVOID );
	}

	void	Player::ModeSwordAttack( void )
	{
		bool param = SwordAttack();

		if(param)SetMode(MODE::MOVE);
	}

	void	Player::ModeMagicAttack( void )
	{
		bool param = MagicAttack();
		if(param)SetMode(MODE::MOVE);
	}


	void	Player::ModeAvoid(void)
	{
		bool param = Avoid();
		if(param)SetMode(MODE::MOVE);
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�ړ�
	bool		Player::Move( void )
	{
		//	���X�e�B�b�N�̓��̓`�F�b�N
		float	axisX = ( float )input[0]->Get( KEY_AXISX );
		float	axisY = -( float )input[0]->Get( KEY_AXISY );
		float	length = sqrtf( axisX * axisX + axisY * axisY ) * 0.001f;

		//	���͂�����Έړ�����
		if ( length >= MIN_INPUT_STICK )
		{
			//	���[�V�����ݒ�
			SetMotion( MOTION::MOVE );	//	���胂�[�V����

			//	��������
			AngleAdjust( 
				Vector3( axisX, 0.0f, axisY ), 
				ANGLE_ADJUST_MOVE_SPEED );

			//	�ړ�
			SetMove( Vector3( sinf( angle ), 0.0f, cosf( angle ) ) * speed );
		}
		else
		{
			//	���[�V�����ݒ�
			SetMotion( MOTION::WAIT );	//	�ҋ@���[�V����
		}
		return false;
	}



	//���U��
	bool		Player::SwordAttack(void)
	{
		SetMotion( MOTION::ATTACK );		//��
		if (!initflag) initflag = true;

		//��
		if (obj->GetFrame() == 413)
		{
			initflag = false;
			return true;	//�U�����삪�I����
		}
		return false;
	}





	//���@�U��
	bool		Player::MagicAttack(void)
	{
		SetMotion(MOTION::ATTACK2);		//��

		if (!initflag)
		{
			initflag = true;
			timer = 0;
			move = Vector3(0, 0, 0);
		}

		//	���X�e�B�b�N�̓��̓`�F�b�N
		float	axisX = (float)input[0]->Get(KEY_AXISX);
		float	axisY = -(float)input[0]->Get(KEY_AXISY);
		float	length = sqrtf(axisX * axisX + axisY * axisY) * 0.001f;
		switch (step)
		{
		case 0:

			//	���͂������
			if (length >= MIN_INPUT_STICK)
			{
				//	��������
				AngleAdjust(
					Vector3(axisX, 0.0f, axisY),
					ANGLE_ADJUST_MAGIC_SPEED);

				//if (axisX > 0)	angle += 0.1f; 
				//else			angle -= 0.1f;
			}


			if (KEY_Get(KEY_B) == 2) step++;
			break;
		case 1:
			timer++;		//�d��
			SetMotion(MOTION::RIGOR);
			if (timer > 100)
			{
				initflag = false;
				return true;
			}
		}
		return false;
	}


	//���
	bool		Player::Avoid(void)
	{
		Vector3 front = GetFront();
		SetMotion(MOTION::AVOID);

		if (!initflag)
		{
			initflag = true;
			timer = 0;
			move.x += front.x * 1.1f;
			move.z += front.z * 1.1f;
		}

		timer++;

		if (timer > 30)
		{
			initflag = false;
			return true;
		}


		return false;
	}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

	void	Player::SetMode(int mode)
	{
		if (this->mode != mode)
		{
			step = 0;
			this->mode = mode;
		}
	}


//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

