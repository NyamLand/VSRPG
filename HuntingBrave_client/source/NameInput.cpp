
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
		if ( KEY( KEY_TYPE::A ) == 3 )
		{
			sound->PlaySE( SE::OK );
			if ( !inputState )
			{
				name[nameCursor] = cursorX + cursorY * CURSOR_MAX_X;
				nameImage[nameCursor]->sx = cursorX * SRC_SCALE;
				nameImage[nameCursor]->sy = cursorY * SRC_SCALE;
			}

			if ( nameCursor != NAME_MAX - 1 )
			{
				nameCursor++;
				nameImage[nameCursor]->renderflag = true;
			}
			else
			{
				if ( inputState )
				{
					if ( cursorX == CURSOR_MAX_X - 1 && cursorY == CURSOR_MAX_Y )
						doneState = true;
				}
				cursorX = CURSOR_MAX_X - 1;
				cursorY = CURSOR_MAX_Y;
				inputState = true;
			}
		}
	}

	//	キャンセル
	void	NameInput::Cancel( void )
	{
		if ( KEY( KEY_TYPE::B ) == 3 )
		{
			if ( nameCursor != 0 )
			{
				if ( inputState )	inputState = false;
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