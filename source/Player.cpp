
#include	"iextreme.h"
#include	"GlobalFunction.h"
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
#define	Y2009_SCALE	0.02f

//	����X�s�[�h
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.5f

//	���͏��
#define	MIN_INPUT_STICK		0.3f

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Player::Player( void )
	{
	
	}

	//	�f�X�g���N�^
	Player::~Player( void )
	{

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

		//	�֐��|�C���^
		ModeFunction[MODE::MOVE] = &Player::MoveMode;
		//ModeFunction[MODE::MOVE] = &Player::PostureMode;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;

		//	���X�V
		UpdateInfo();

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

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�ړ����[�h����
	void	Player::MoveMode( void )
	{
		//	�X�e�B�b�N�ɂ��ړ�
		Move();
		if (KEY_Get(KEY_A) == 3) SetMode(MODE::SWOADATTACK);		//��
		if (KEY_Get(KEY_B) == 3) SetMode(MODE::MAGICATTACK);	
	}

	void	Player::ModeSwordAttack( void )
	{
		int param = SwordAttack();

		switch (param)
		{
		case 1:
			SetMode(MODE::MOVE);
			break;
		case 2:
			break;
		}
	}

	void	Player::ModeMagicAttack( void )
	{
		int param = MagicAttack();

		switch (param)
		{
		case 1:
			SetMode(MODE::MOVE);
			break;
		case 2:
			break;
		}
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�ړ�
	int		Player::Move( void )
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
				ANGLE_ADJUST_SPEED );

			//	�ړ�
			SetMove( Vector3( sinf( angle ), 0.0f, cosf( angle ) ) * speed );
		}
		else
		{
			//	���[�V�����ݒ�
			SetMotion( MOTION::WAIT );	//	�ҋ@���[�V����
		}
		return 1;
	}

	//���U��
	int		Player::SwordAttack(void)
	{
		SetMotion( MOTION::ATTACK );


		//��
		if (obj->GetFrame() == 413)return 1;	//�U�����삪�I����

		return false;
	}


	//���@�U��
	int		Player::MagicAttack(void)
	{
		SetMotion(MOTION::ATTACK2);

		move = Vector3(0, 0, 0);

		//	���X�e�B�b�N�̓��̓`�F�b�N
		float	axisX = (float)input[0]->Get(KEY_AXISX);
		float	axisY = -(float)input[0]->Get(KEY_AXISY);
		float	length = sqrtf(axisX * axisX + axisY * axisY) * 0.001f;

		//	���͂�����Έړ�����
		if (length >= MIN_INPUT_STICK)
		{
			angle += 0.1f; //����Ɠr��
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
			this->mode = mode;
		}
	}


//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

