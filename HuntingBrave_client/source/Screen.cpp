
#include	"iextreme.h"
#include	"system\System.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"Screen.h"

//*******************************************************************************
//
//	Screenクラス
//
//*******************************************************************************

//-----------------------------------------------------------------------------------
//	グローバル
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
//	初期化・解放
//-----------------------------------------------------------------------------------

	//	コンストラクタ
	Screen::Screen( void ) : color( Color::BLACK ),
		alpha( 1.0f ), speed( 1.0f ), param( 0.0f ),
		screenState( false ),
		mode( SCREEN_MODE::FADE_IN )
	{
		//	各補間初期値、最終値設定
		startParam[SCREEN_MODE::FADE_IN]		=		startParam[SCREEN_MODE::WHITE_IN]		= 1.0f;
		startParam[SCREEN_MODE::FADE_OUT]	=		startParam[SCREEN_MODE::WHITE_OUT]	= 0.0f;
		endParam[SCREEN_MODE::FADE_OUT]		=		endParam[SCREEN_MODE::WHITE_OUT]	= 1.0f;
		endParam[SCREEN_MODE::FADE_IN]			=		endParam[SCREEN_MODE::WHITE_IN]		= 0.0f;
		startParam[SCREEN_MODE::GRAY] = 0.0f;
		endParam[SCREEN_MODE::GRAY] = 0.5f;
	}

	//	デストラクタ
	Screen::~Screen( void )
	{

	}

//-----------------------------------------------------------------------------------
//	更新・描画
//-----------------------------------------------------------------------------------

	//	更新
	bool	Screen::Update( void )
	{
		//	補間割合加算
		Interpolation::PercentageUpdate( param, speed );

		//	スクリーン状態初期化
		screenState = false;

		//	フェード処理
		screenState = Fade();

		return	screenState;
	}

	//	描画
	void	Screen::Render( void )
	{
		iexPolygon::Rect( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, RS_COPY, GetColor( color, alpha ) );
	}

//-----------------------------------------------------------------------------------
//	動作関数
//-----------------------------------------------------------------------------------

	//	フェード処理
	bool	Screen::Fade( void )
	{
		//	補間
		bool	isEnd = Interpolation::CubicFunctionInterpolation( alpha, startParam[mode], endParam[mode], param );

		return	isEnd;
	}
	
	//	灰色処理
	bool	Screen::Gray( void )
	{
		//	補間
		bool	isEnd = Interpolation::CubicFunctionInterpolation( alpha, startParam[mode], endParam[mode], param );

		return	isEnd;
	}

//-----------------------------------------------------------------------------------
//	情報設定
//-----------------------------------------------------------------------------------

	//	スクリーンモード
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
//	情報取得
//-----------------------------------------------------------------------------------

	//	スクリーン状態取得
	bool	Screen::GetScreenState( void )const
	{
		return	screenState;
	}

	//	実体取得
	Screen*	Screen::GetInstance( void )
	{
		static	Screen	out;
		return	&out;
	}