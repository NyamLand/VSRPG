
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"Interpolation.h"
#include	"InputManager.h"
#include	"KillLogUI.h"

//*************************************************************************
//
//	KillLogUI�N���X
//
//*************************************************************************

//-------------------------------------------------------------------------------------
//	�O���[�o��
//-------------------------------------------------------------------------------------

#define	KILL_LOG_WIDTH	300
#define	KILL_LOG_HEIGHT	75
#define	KILL_LOG_DIST	50
#define	SRC_POS_PLAYER	256
#define	SRC_WIDTH		512
#define	SRC_HEIGHT	128
#define	DEAD_ENEMY	3
#define	LERP_SPEED	0.01f

namespace
{
	//	�摜���ԑΉ��\( �v���C���[�l���{��^�G)
	int killInfo[][PLAYER_MAX + 1] =
	{
		{ -1, 0, 1, 2, DEAD_ENEMY },
		{ 0, -1, 1, 2, DEAD_ENEMY },
		{ 0, 1, -1, 2, DEAD_ENEMY },
		{ 0, 1, 2, -1, DEAD_ENEMY }
	};
}

//-------------------------------------------------------------------------------------
//	�������E���
//-------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	KillLogUI::KillLogUI( void ) : killLogImage( nullptr ),
		percentage( 1.0f ), killFrag( false )
	{
		//	�摜�\���̏�����
		killLogImage = new Image();
		killLogImage->Initialize(
			"DATA/UI/main_UI/Kill_log.png",
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 2,
			KILL_LOG_WIDTH, KILL_LOG_HEIGHT,
			0, 0, SRC_WIDTH, SRC_HEIGHT );

		//	�\�����Ȃ�
		killLogImage->renderflag = false;
	}

	//	�f�X�g���N�^
	KillLogUI::~KillLogUI( void )
	{
		SafeDelete( killLogImage );
	}

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------

	//	�X�V
	void	KillLogUI::Update( void )
	{
		//	���
		Interpolation::LinearInterpolation( killLogImage->y,
			( int )iexSystem::ScreenHeight / 2,
			( int )iexSystem::ScreenHeight / 2 - KILL_LOG_DIST,
			percentage );

		//	��ԃp�����[�^�X�V
		bool lerpState = Interpolation::PercentageUpdate( percentage, LERP_SPEED );

		//	��Ԃ��������������
		if ( lerpState )
		{
			killLogImage->renderflag = false;
		}
	}

	//	�`��
	void	KillLogUI::Render( void )
	{
		killLogImage->Render( IMAGE_MODE::ADOPTPARAM );
	}

//-------------------------------------------------------------------------------------
//	����֐�
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

	//	�L�����O�ݒ�
	void	KillLogUI::SetKillLog( int killer, int dead )
	{
		//	����������
		percentage = 0.0f;
		
		//	�ǂݍ��݈ʒu�ݒ�
		killLogImage->sx = killInfo[killer][dead] % 2;
		killLogImage->sy = SRC_POS_PLAYER * killer + SRC_HEIGHT * ( killInfo[killer][dead] / 2 );

		killLogImage->renderflag = true;
	}

//-------------------------------------------------------------------------------------
//	���擾
//-------------------------------------------------------------------------------------



