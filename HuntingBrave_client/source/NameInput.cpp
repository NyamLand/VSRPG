
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"InputManager.h"
#include	"GameManager.h"
#include	"Sound.h"
#include	"NameInput.h"

//***************************************************************
//
//	NameInputクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

#define SIZE_OF_ARRAY( ary )  ( sizeof( ary )/sizeof( ( ary )[0]) )

//	画像情報
namespace
{
	#define	SRC_SCALE		64

	//	カーソル情報
	#define	INIT_POS_X		198
	#define	INIT_POS_Y		290
	#define	CURSOR_SPACE_X	98
	#define	CURSOR_SPACE_Y	70
	#define	CURSOR_SCALE	70
	#define	CURSOR_SPEED	0.1f
	#define	CURSOR_MAX_X	10
	#define	CURSOR_MAX_Y	5
	#define	INPUT_MIN		0.3f

	//	名前情報
	#define	NAME_INIT_POS_X	485
	#define	NAME_INIT_POS_Y	157
	#define	NAME_SPACE	105
	#define	NAME_END_POS	878
	#define	NAME_SCALE	80
	#define	NAME_FRASH_SPEED	0.1f

	//	濁点、半濁点
	#define	VOICED_SPOT_INDEX		56
	#define	SEMI_VOICED_SPOT_INDEX	57
	#define	SRC_SEMIVOICED_SPOT_CHAR_X  640
	#define	SRC_SEMIVOICED_SPOT_CHER_Y	64
}

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	NameInput::NameInput( void ) : back( nullptr ), cursorImage( nullptr ),
		percentageX( 1.0f ), percentageY( 1.0f ), axisX( 0.0f ), axisY( 0.0f ),
		inputState( false ), cancelState( false ), doneState( false ),
		cursorX( 0 ), cursorY( 0 ), saveX( 0 ), saveY( 0 ), nameCursor( 0 )
	{
		//	画像読み込み
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
	
	//	デストラクタ
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
//	更新・描画
//------------------------------------------------------------------------------------

	//	更新
	bool	NameInput::Update( void )
	{
		//	補間値更新
		bool moveStateX = Interpolation::PercentageUpdate( percentageX, CURSOR_SPEED );
		bool moveStateY = Interpolation::PercentageUpdate( percentageY, CURSOR_SPEED );

		//	補間
		UpdateInfo();

		//	キー操作
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

	//	描画
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
//	動作関数
//------------------------------------------------------------------------------------

	//	カーソル移動
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

	//	情報更新
	void	NameInput::UpdateInfo( void )
	{
		//	移動補間
		Interpolation::CubicFunctionInterpolation(
			cursorImage->x, INIT_POS_X + CURSOR_SPACE_X * saveX, 
			INIT_POS_X + CURSOR_SPACE_X * cursorX, percentageX );
		Interpolation::CubicFunctionInterpolation(
			cursorImage->y, INIT_POS_Y + CURSOR_SPACE_Y * saveY, 
			INIT_POS_Y + CURSOR_SPACE_Y * cursorY, percentageY );

		//	名前情報設定
		if ( !inputState )
		{
			nameImage[nameCursor]->sx = cursorX * SRC_SCALE;
			nameImage[nameCursor]->sy = cursorY * SRC_SCALE;
			nameImage[nameCursor]->FlashUpdate();
		}
	}

	//	文字決定
	void	NameInput::DecisionCharacter( void )
	{
		bool	voicedSpotState = false;

		if ( KEY( KEY_TYPE::A ) == 3 )
		{
			sound->PlaySE( SE::OK );
			
			//	文字決定
			if ( nameCursor != NAME_MAX )
			{
				//	文字チェック
				CharacterCheck( voicedSpotState );

				//	濁点、半濁点時意外ならカーソル加算
				if ( !voicedSpotState )	nameCursor++;
				if ( nameCursor == NAME_MAX )
				{
					//	カーソルを決定に移動
					cursorX = CURSOR_MAX_X - 1;
					cursorY = CURSOR_MAX_Y;
					inputState = true;
				}
				else nameImage[nameCursor]->renderflag = true;

			}
			//	カーソルが最後の場合
			else
			{
				//	決定
				if ( cursorX == CURSOR_MAX_X - 1 && cursorY == CURSOR_MAX_Y )		doneState = true;
				else
				{
					//	濁点、半濁点のみ判定
					CharacterCheckLast();
				}
			}
		}
	}

	//	キャンセル
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

	//	文字チェック
	void	NameInput::CharacterCheck( bool& voicedSpotState )
	{
		bool	semiVoicedSpot = false;

		//	選択したカーソル位置を保存
		int out = 0;
		int nameIndex = cursorX + cursorY * CURSOR_MAX_X;

		//	濁点、半濁点チェック
		semiVoicedSpot = false;
		voicedSpotState = VoicedSpotCheck( out, name[nameCursor - 1], nameIndex, semiVoicedSpot );

		//	読み込み位置を指定
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

	//	文字チェック最終
	void	NameInput::CharacterCheckLast( void )
	{
		//	濁点、半濁点チェック
		bool semiVoicedSpot = false;
		int nameIndex = cursorX + cursorY * CURSOR_MAX_X;
		int out;
		bool voicedSpotState = VoicedSpotCheck( out, name[nameCursor - 1], nameIndex, semiVoicedSpot );

		//	読み込み位置を指定
		if ( voicedSpotState )
		{
			name[nameCursor - 1] = out;

			//	半濁点時
			if ( semiVoicedSpot )
			{
				nameImage[nameCursor - 1]->sx =
					SRC_SEMIVOICED_SPOT_CHAR_X + ( ( out % 5 ) * SRC_SCALE );

				nameImage[nameCursor - 1]->sy = SRC_SEMIVOICED_SPOT_CHER_Y;
			}
			else
			{
				//	濁点時
				nameImage[nameCursor - 1]->sx = ( ( out - 5 ) % CURSOR_MAX_X * SRC_SCALE );
				nameImage[nameCursor - 1]->sy = ( ( out - 5 ) / CURSOR_MAX_X * SRC_SCALE );
			}
		}
	}

	//	濁点、半濁点チェック( 半濁点時trueをかえす )
	bool	NameInput::VoicedSpotCheck( int& outIndex, int beforeIndex, int nameIndex, bool& semiVoicedSpot )
	{
		bool	out = false;

		//	半濁点
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

		//	濁点
		else if ( nameIndex == VOICED_SPOT_INDEX )
		{
			out = true;

			//	か行
			if ( beforeIndex >= 5 && beforeIndex <= 9 )	
			{
				outIndex = 60 + beforeIndex;
			}
			//	さ行
			else if ( beforeIndex >= 10 && beforeIndex <= 14 )
			{
				outIndex = 60 + beforeIndex;
			}
			//	た行
			else if ( beforeIndex >= 15 && beforeIndex <= 19 )
			{
				outIndex = 60 + beforeIndex;
			}
			//	は行
			else if ( beforeIndex >= 25 && beforeIndex <= 29 )
			{
				outIndex = 60 + beforeIndex - 5;
			}
			//	該当なし
			else	return	false;
		}
		else return	false;

		return	out;
	}

	//	通常文字設定
	void	NameInput::NormalCharacterSet( void )
	{
		//	通常時
		nameImage[nameCursor]->sx = cursorX * SRC_SCALE;
		nameImage[nameCursor]->sy = cursorY * SRC_SCALE;
	}
	
	//	濁点、半濁点文字設定
	void	NameInput::VoicedSpotCharacterSet( int nameIndex, bool semiVoicedSpot )
	{
		//	半濁点時
		if ( semiVoicedSpot )
		{
			nameImage[nameCursor - 1]->sx =
				SRC_SEMIVOICED_SPOT_CHAR_X + ( ( nameIndex % 5 ) * SRC_SCALE );

			nameImage[nameCursor - 1]->sy = SRC_SEMIVOICED_SPOT_CHER_Y;
		}
		else
		{
			//	濁点時
			nameImage[nameCursor - 1]->sx = ( ( nameIndex - 5 ) % 10 * SRC_SCALE );
			nameImage[nameCursor - 1]->sy = ( ( nameIndex - 5 ) / 10 * SRC_SCALE );
		}
	}

//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

	//	キャンセル情報取得
	bool	NameInput::GetCancelState( void )
	{
		return	cancelState;
	}

	//	文字列取得
	int*	NameInput::GetName( void )
	{
		return name;
	}