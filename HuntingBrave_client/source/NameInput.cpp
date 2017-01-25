
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"InputManager.h"
#include	"GameManager.h"
#include	"Sound.h"
#include	"NameInput.h"

//***************************************************************
//
//	NameInput�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

#define SIZE_OF_ARRAY( ary )  ( sizeof( ary )/sizeof( ( ary )[0]) )

//	�摜���
namespace
{
	#define	SRC_SCALE		64

	//	�J�[�\�����
	#define	INIT_POS_X		198
	#define	INIT_POS_Y		290
	#define	CURSOR_SPACE_X	98
	#define	CURSOR_SPACE_Y	70
	#define	CURSOR_SCALE	70
	#define	CURSOR_SPEED	0.1f
	#define	CURSOR_MAX_X	10
	#define	CURSOR_MAX_Y	5
	#define	INPUT_MIN		0.3f

	//	���O���
	#define	NAME_INIT_POS_X	485
	#define	NAME_INIT_POS_Y	157
	#define	NAME_SPACE	105
	#define	NAME_END_POS	878
	#define	NAME_SCALE	80
	#define	NAME_FRASH_SPEED	0.1f

	//	���_�A�����_
	#define	VOICED_SPOT_INDEX		56
	#define	SEMI_VOICED_SPOT_INDEX	57
	#define	SRC_SEMIVOICED_SPOT_CHAR_X  640
	#define	SRC_SEMIVOICED_SPOT_CHER_Y	64
}

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NameInput::NameInput( void ) : back( nullptr ), cursorImage( nullptr ),
		percentageX( 1.0f ), percentageY( 1.0f ), axisX( 0.0f ), axisY( 0.0f ),
		inputState( false ), cancelState( false ), doneState( false ),
		cursorX( 0 ), cursorY( 0 ), saveX( 0 ), saveY( 0 ), nameCursor( 0 )
	{
		//	�摜�ǂݍ���
		back = new iex2DObj( "DATA/UI/BackGround/name_input_gamen.png" );
		cursorImage = new Image();
		cursorImage->Initialize( "DATA/UI/main_UI/ward.png", 
			INIT_POS_X, INIT_POS_Y,
			CURSOR_SCALE, CURSOR_SCALE,
			SRC_SCALE * 10, 0, SRC_SCALE, SRC_SCALE );

		for ( int i = 0; i < NAME_MAX; i++ )
		{
			name[i] = 0;
			nameImage[i] = new Image();
			nameImage[i]->Initialize( "DATA/UI/main_UI/ward.png",
				NAME_INIT_POS_X + NAME_SPACE * i, NAME_INIT_POS_Y,
				NAME_SCALE, NAME_SCALE,
				0, 0, SRC_SCALE, SRC_SCALE );
			nameImage[i]->SetFlash( NAME_FRASH_SPEED );
			
			if( i != 0 ) nameImage[i]->renderflag = false;
		}
	}
	
	//	�f�X�g���N�^
	NameInput::~NameInput( void )
	{
		SafeDelete( back );
		SafeDelete( cursorImage );

		for ( int i = 0; i < NAME_MAX; i++ )
		{
			SafeDelete( nameImage[i] );
		}
	}

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

	//	�X�V
	bool	NameInput::Update( void )
	{
		//	��Ԓl�X�V
		bool moveStateX = Interpolation::PercentageUpdate( percentageX, CURSOR_SPEED );
		bool moveStateY = Interpolation::PercentageUpdate( percentageY, CURSOR_SPEED );

		//	���
		UpdateInfo();

		//	�L�[����
		if ( cancelState )	return false;
		if ( doneState )		return	true;
		if ( moveStateX && moveStateY )
		{
			DecisionCharacter();
			Cancel();

			MoveCursor();
		}

		return	doneState;
	}

	//	�`��
	void	NameInput::Render( void )
	{
		back->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720 );
		cursorImage->Render( IMAGE_MODE::NORMAL );

		for ( int i = 0; i < NAME_MAX; i++ )
		{
			if ( !inputState && i == nameCursor )	nameImage[i]->Render( IMAGE_MODE::FLASH );
			else nameImage[i]->Render( IMAGE_MODE::NORMAL );
		}
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�J�[�\���ړ�
	void	NameInput::MoveCursor( void )
	{
		inputManager->GetStickInputLeft( axisX, axisY );
		
		if ( abs( axisX ) >= INPUT_MIN )
		{
			percentageX = 0.0f;
			saveX = cursorX;

			sound->PlaySE( SE::MOVE_SELECT );

			if ( axisX > 0.0f )
			{
				if ( cursorX != CURSOR_MAX_X - 1 )	cursorX++;
			}
			else
			{
				if ( cursorX != 0 )		cursorX--;
			}
		}

		if ( abs( axisY ) >= INPUT_MIN )
		{
			percentageY = 0.0f;
			saveY = cursorY;

			sound->PlaySE(SE::MOVE_SELECT);

			if ( axisY > 0.0f )
			{
				if ( cursorY != 0 )		cursorY--;
			}
			else
			{
				if ( cursorY != CURSOR_MAX_Y )	cursorY++;
			}
		}
	}

	//	���X�V
	void	NameInput::UpdateInfo( void )
	{
		//	�ړ����
		Interpolation::CubicFunctionInterpolation(
			cursorImage->x, INIT_POS_X + CURSOR_SPACE_X * saveX, 
			INIT_POS_X + CURSOR_SPACE_X * cursorX, percentageX );
		Interpolation::CubicFunctionInterpolation(
			cursorImage->y, INIT_POS_Y + CURSOR_SPACE_Y * saveY, 
			INIT_POS_Y + CURSOR_SPACE_Y * cursorY, percentageY );

		//	���O���ݒ�
		if ( !inputState )
		{
			nameImage[nameCursor]->sx = cursorX * SRC_SCALE;
			nameImage[nameCursor]->sy = cursorY * SRC_SCALE;
			nameImage[nameCursor]->FlashUpdate();
		}
	}

	//	��������
	void	NameInput::DecisionCharacter( void )
	{
		bool	voicedSpotState = false;

		if ( KEY( KEY_TYPE::A ) == 3 )
		{
			sound->PlaySE( SE::OK );
			
			//	��������
			if ( nameCursor != NAME_MAX )
			{
				//	�����`�F�b�N
				CharacterCheck( voicedSpotState );

				//	���_�A�����_���ӊO�Ȃ�J�[�\�����Z
				if ( !voicedSpotState )	nameCursor++;
				if ( nameCursor == NAME_MAX )
				{
					//	�J�[�\��������Ɉړ�
					cursorX = CURSOR_MAX_X - 1;
					cursorY = CURSOR_MAX_Y;
					inputState = true;
				}
				else nameImage[nameCursor]->renderflag = true;

			}
			//	�J�[�\�����Ō�̏ꍇ
			else
			{
				//	����
				if ( cursorX == CURSOR_MAX_X - 1 && cursorY == CURSOR_MAX_Y )		doneState = true;
				else
				{
					//	���_�A�����_�̂ݔ���
					CharacterCheckLast();
				}
			}
		}
	}

	//	�L�����Z��
	void	NameInput::Cancel( void )
	{
		if ( KEY( KEY_TYPE::B ) == 3 )
		{
			sound->PlaySE(SE::CANCEL);

			if ( nameCursor != 0 )
			{
				if ( inputState )
				{
					inputState = false;
					nameCursor--;
				}
				else
				{
					nameImage[nameCursor]->renderflag = false;
					nameCursor--;
				}
			}
			else
			{
				gameManager->SetChangeSceneFrag( true );
				nameImage[nameCursor]->renderflag = false;
				cancelState = true;
			}
		}
	}

	//	�����`�F�b�N
	void	NameInput::CharacterCheck( bool& voicedSpotState )
	{
		bool	semiVoicedSpot = false;

		//	�I�������J�[�\���ʒu��ۑ�
		int out = 0;
		int nameIndex = cursorX + cursorY * CURSOR_MAX_X;

		//	���_�A�����_�`�F�b�N
		semiVoicedSpot = false;
		voicedSpotState = VoicedSpotCheck( out, name[nameCursor - 1], nameIndex, semiVoicedSpot );

		//	�ǂݍ��݈ʒu���w��
		if ( !voicedSpotState )
		{
			name[nameCursor] = nameIndex;
			NormalCharacterSet();
		}
		else
		{
			name[nameCursor - 1] = out;
			VoicedSpotCharacterSet( out, semiVoicedSpot );
		}
	}

	//	�����`�F�b�N�ŏI
	void	NameInput::CharacterCheckLast( void )
	{
		//	���_�A�����_�`�F�b�N
		bool semiVoicedSpot = false;
		int nameIndex = cursorX + cursorY * CURSOR_MAX_X;
		int out;
		bool voicedSpotState = VoicedSpotCheck( out, name[nameCursor - 1], nameIndex, semiVoicedSpot );

		//	�ǂݍ��݈ʒu���w��
		if ( voicedSpotState )
		{
			name[nameCursor - 1] = out;

			//	�����_��
			if ( semiVoicedSpot )
			{
				nameImage[nameCursor - 1]->sx =
					SRC_SEMIVOICED_SPOT_CHAR_X + ( ( out % 5 ) * SRC_SCALE );

				nameImage[nameCursor - 1]->sy = SRC_SEMIVOICED_SPOT_CHER_Y;
			}
			else
			{
				//	���_��
				nameImage[nameCursor - 1]->sx = ( ( out - 5 ) % CURSOR_MAX_X * SRC_SCALE );
				nameImage[nameCursor - 1]->sy = ( ( out - 5 ) / CURSOR_MAX_X * SRC_SCALE );
			}
		}
	}

	//	���_�A�����_�`�F�b�N( �����_��true�������� )
	bool	NameInput::VoicedSpotCheck( int& outIndex, int beforeIndex, int nameIndex, bool& semiVoicedSpot )
	{
		bool	out = false;

		//	�����_
		if ( nameIndex == SEMI_VOICED_SPOT_INDEX )
		{
			out = true;
			semiVoicedSpot = true;
			if ( beforeIndex >= 25 && beforeIndex <= 29 )
			{
				outIndex = 60 + beforeIndex + 5;
			}
			else	return	false;
		}

		//	���_
		else if ( nameIndex == VOICED_SPOT_INDEX )
		{
			out = true;

			//	���s
			if ( beforeIndex >= 5 && beforeIndex <= 9 )	
			{
				outIndex = 60 + beforeIndex;
			}
			//	���s
			else if ( beforeIndex >= 10 && beforeIndex <= 14 )
			{
				outIndex = 60 + beforeIndex;
			}
			//	���s
			else if ( beforeIndex >= 15 && beforeIndex <= 19 )
			{
				outIndex = 60 + beforeIndex;
			}
			//	�͍s
			else if ( beforeIndex >= 25 && beforeIndex <= 29 )
			{
				outIndex = 60 + beforeIndex - 5;
			}
			//	�Y���Ȃ�
			else	return	false;
		}
		else return	false;

		return	out;
	}

	//	�ʏ핶���ݒ�
	void	NameInput::NormalCharacterSet( void )
	{
		//	�ʏ펞
		nameImage[nameCursor]->sx = cursorX * SRC_SCALE;
		nameImage[nameCursor]->sy = cursorY * SRC_SCALE;
	}
	
	//	���_�A�����_�����ݒ�
	void	NameInput::VoicedSpotCharacterSet( int nameIndex, bool semiVoicedSpot )
	{
		//	�����_��
		if ( semiVoicedSpot )
		{
			nameImage[nameCursor - 1]->sx =
				SRC_SEMIVOICED_SPOT_CHAR_X + ( ( nameIndex % 5 ) * SRC_SCALE );

			nameImage[nameCursor - 1]->sy = SRC_SEMIVOICED_SPOT_CHER_Y;
		}
		else
		{
			//	���_��
			nameImage[nameCursor - 1]->sx = ( ( nameIndex - 5 ) % 10 * SRC_SCALE );
			nameImage[nameCursor - 1]->sy = ( ( nameIndex - 5 ) / 10 * SRC_SCALE );
		}
	}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

	//	�L�����Z�����擾
	bool	NameInput::GetCancelState( void )
	{
		return	cancelState;
	}

	//	������擾
	int*	NameInput::GetName( void )
	{
		return name;
	}