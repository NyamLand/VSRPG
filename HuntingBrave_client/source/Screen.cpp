
#include	"iextreme.h"
#include	"system\System.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"Screen.h"

//*******************************************************************************
//
//	Screen�N���X
//
//*******************************************************************************

//-----------------------------------------------------------------------------------
//	�O���[�o��
//-----------------------------------------------------------------------------------

#define	WIPE_MAX_SIZE	1000.0f

	namespace
	{
		namespace Color
		{
			const Vector3 WHITE( 1.0f, 1.0f, 1.0f );
			const Vector3 BLACK( 0.0f, 0.0f, 0.0f );
			const Vector3 GRAY( 0.5f, 0.5f, 0.5f );
		}
	}

//-----------------------------------------------------------------------------------
//	�������E���
//-----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Screen::Screen( void ) : color( Color::BLACK ),
		alpha( 1.0f ), speed( 1.0f ), param( 0.0f ),
		screenState( false ),
		mode( SCREEN_MODE::FADE_IN )
	{
		//	�e��ԏ����l�A�ŏI�l�ݒ�
		startParam[SCREEN_MODE::FADE_IN]		=		startParam[SCREEN_MODE::WHITE_IN]		= 1.0f;
		startParam[SCREEN_MODE::FADE_OUT]	=		startParam[SCREEN_MODE::WHITE_OUT]	= 0.0f;
		endParam[SCREEN_MODE::FADE_OUT]		=		endParam[SCREEN_MODE::WHITE_OUT]	= 1.0f;
		endParam[SCREEN_MODE::FADE_IN]			=		endParam[SCREEN_MODE::WHITE_IN]		= 0.0f;
		startParam[SCREEN_MODE::GRAY] = 0.0f;
		endParam[SCREEN_MODE::GRAY] = 0.5f;
	}

	//	�f�X�g���N�^
	Screen::~Screen( void )
	{

	}

//-----------------------------------------------------------------------------------
//	�X�V�E�`��
//-----------------------------------------------------------------------------------

	//	�X�V
	bool	Screen::Update( void )
	{
		//	��Ԋ������Z
		Interpolation::PercentageUpdate( param, speed );

		//	�X�N���[����ԏ�����
		screenState = false;

		//	�t�F�[�h����
		screenState = Fade();

		return	screenState;
	}

	//	�`��
	void	Screen::Render( void )
	{
		iexPolygon::Rect( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, RS_COPY, GetColor( color, alpha ) );
	}

//-----------------------------------------------------------------------------------
//	����֐�
//-----------------------------------------------------------------------------------

	//	�t�F�[�h����
	bool	Screen::Fade( void )
	{
		//	���
		bool	isEnd = Interpolation::CubicFunctionInterpolation( alpha, startParam[mode], endParam[mode], param );

		return	isEnd;
	}
	
	//	�D�F����
	bool	Screen::Gray( void )
	{
		//	���
		bool	isEnd = Interpolation::CubicFunctionInterpolation( alpha, startParam[mode], endParam[mode], param );

		return	isEnd;
	}

//-----------------------------------------------------------------------------------
//	���ݒ�
//-----------------------------------------------------------------------------------

	//	�X�N���[�����[�h
	void	Screen::SetScreenMode( int mode, float speed )
	{
		this->mode = mode;
		this->speed = speed;
		this->screenState = false;
		param = 0.0f;
		switch ( this->mode )
		{
		case SCREEN_MODE::FADE_IN:
		case SCREEN_MODE::FADE_OUT:
			color = Color::BLACK;
			break;

		case SCREEN_MODE::WHITE_IN:
		case SCREEN_MODE::WHITE_OUT:
			color = Color::WHITE;
			break;

		case SCREEN_MODE::GRAY:
			color = Color::GRAY;
			break;
		default:
			break;
		}
	}

//-----------------------------------------------------------------------------------
//	���擾
//-----------------------------------------------------------------------------------

	//	�X�N���[����Ԏ擾
	bool	Screen::GetScreenState( void )const
	{
		return	screenState;
	}

	//	���̎擾
	Screen*	Screen::GetInstance( void )
	{
		static	Screen	out;
		return	&out;
	}