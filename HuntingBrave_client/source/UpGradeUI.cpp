
#include	"iextreme.h"
#include	"system/System.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"LevelManager.h"
#include	"InputManager.h"

#include	"UpGradeUI.h"

//***************************************************************
//
//	UpGradeUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//	ボード用
namespace
{
#define	BOARD_ALPHA	0.6f
#define	SELECT_CENTER_DIST	170
}

//	レベル種類アイコン用
namespace
{
#define	ICON_START_DIST	400
#define	ICON_SCALE	70
#define	ICON_SPACE	100
#define	ICON_BIG_SCALE	90
#define	BIG_SRC_SIZE	128
}

//	レベルアイコン用
namespace
{
#define	LEVEL_ICON_DIST	50
#define	LEVEL_ICON_SCALE	45
#define	SRC_SIZE		64
}

//	数値UI用
namespace
{
#define	EXP_UI_CENTER_DIST	100
#define	EXP_UI_DIST	150
#define	EXP_UI_WIDTH	100
#define	EXP_UI_HEIGHT	50
}

//	現在レベルアイコン用
namespace
{
#define	CUR_LEVEL_CENTER_DIST		70
#define	CUR_LEVEL_DIST	250
#define	CUR_LEVEL_SIZE		150
}

//	その他
#define	INTERPOLATION_SPEED	0.1f

//	構造体
namespace
{
	struct IconSrcPos
	{
		int sx;
		int sy;
	};

	IconSrcPos	srcPos[] =
	{
		{ 384, 128 },	//	attack
		{ 384, 384 },	//	magicAttack
		{ 384, 256 },	//	difense
		{ 256, 384 },	//	magicDifense
		{ 128, 384 }	//	speed
	};
}

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

	//	コンストラクタ
	UpGradeUI::UpGradeUI( void ) : back( nullptr ), 
		typeIcon( nullptr ), levelIcon( nullptr ),
		expUI( nullptr ), flavorText( nullptr ),
		select( 0 ), beforeSelect( 1 ),
		percentage( 0.0f ), percentage2( 1.0f )
	{
		//	プレイヤー番号取得
		id = gameParam->GetMyIndex();

		//	ボードサイズ
		int x = iexSystem::ScreenWidth / 2;
		int y = iexSystem::ScreenHeight / 2;
		int w = ( int )( iexSystem::ScreenWidth / 1.25f );
		int h = ( int )( iexSystem::ScreenHeight / 1.25f );

		//	背景初期化
		back = new Image();
		back->Initialize( "DATA/UI/BackGround/Upgrade_UI.png", x, y, w, h, 0, 0, 1280, 720 );

		//	現在レベルアイコン初期化
		curLevelIcon = new Image();
		curLevelIcon->Initialize( "DATA/UI/icon/Upgrade/icon.png", 
			x + CUR_LEVEL_DIST,
			y - CUR_LEVEL_CENTER_DIST,
			CUR_LEVEL_SIZE, CUR_LEVEL_SIZE, 
			0, 0, SRC_SIZE, SRC_SIZE );

		//	レベルアイコン初期化
		typeIcon = new Image*[LEVEL_TYPE::TYPE_MAX];
		levelIcon = new Image*[LEVEL_TYPE::TYPE_MAX * levelManager->LEVEL_MAX];
		for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
		{
			//	タイプ選択用アイコン
			typeIcon[i] = new Image();
			typeIcon[i]->Initialize( "DATA/UI/icon/Upgrade/icon.png", 
				x -  ICON_START_DIST + ( i * ICON_SPACE ),
				y + SELECT_CENTER_DIST, 
				ICON_SCALE, ICON_SCALE, srcPos[i].sx, srcPos[i].sy, 
				BIG_SRC_SIZE, BIG_SRC_SIZE );

			//	レベル用アイコン
			for ( int j = 0; j < levelManager->LEVEL_MAX; j++ )
			{
				levelIcon[i * levelManager->LEVEL_MAX + j] = new Image();
				levelIcon[i *levelManager->LEVEL_MAX + j]->Initialize( "DATA/UI/icon/Upgrade/icon.png",
					typeIcon[i]->x,
					( typeIcon[i]->y - ICON_SCALE ) - ( LEVEL_ICON_DIST * j ),
					LEVEL_ICON_SCALE, LEVEL_ICON_SCALE, j * SRC_SIZE, i * SRC_SIZE, SRC_SIZE, SRC_SIZE );
			}
		}

		//	経験値UI初期化
		expUI = new ExpUI( x + EXP_UI_DIST, y + EXP_UI_CENTER_DIST, 
			EXP_UI_WIDTH, EXP_UI_HEIGHT );

		//	フォント初期化
		flavorText = new Font( "ＤＦ麗雅宋W5", 25 );

		text = "";
	}

	//	デストラクタ
	UpGradeUI::~UpGradeUI( void )
	{
		SafeDelete( back );
		SafeDeleteArray( typeIcon );
		SafeDeleteArray( levelIcon );
		SafeDelete( expUI );
		SafeDelete( curLevelIcon );
		SafeDelete( flavorText );
	}
	
//---------------------------------------------------------------------------------------
//	更新・描画	
//---------------------------------------------------------------------------------------

	//	更新
	void	UpGradeUI::Update( void )
	{
		bool state1 = Interpolation::PercentageUpdate( percentage, INTERPOLATION_SPEED );
		bool state2 = Interpolation::PercentageUpdate( percentage2, INTERPOLATION_SPEED );

		//	読み込み位置設定
		SetBigIconSrcPos();

		//	入力取得
		float	axisX, axisY;
		inputManager->GetStickInputLeft( axisX, axisY );

		//	補間
		Interpolation::LinearInterpolation( typeIcon[select]->w, ICON_SCALE, ICON_BIG_SCALE, percentage );
		Interpolation::LinearInterpolation( typeIcon[select]->h, ICON_SCALE, ICON_BIG_SCALE, percentage );
		Interpolation::LinearInterpolation( typeIcon[beforeSelect]->w, ICON_BIG_SCALE, ICON_SCALE, percentage2 );
		Interpolation::LinearInterpolation( typeIcon[beforeSelect]->h, ICON_BIG_SCALE, ICON_SCALE, percentage2 );

		//	選択
		if ( state1 && state2 )
		{
			if ( KEY( KEY_ENTER ) == 3 )
			{
				Dicision();
			}

			if ( abs( axisX ) >= 0.3f )
			{
				//	カーソル移動
				beforeSelect = select;
				if ( axisX > 0.0f )	select++;
				else select--;

				//	パラメータリセット
				percentage = percentage2 = 0.0f;

				//	カーソル制限
				if ( select >= LEVEL_TYPE::TYPE_MAX )		select = 0;
				if ( select < 0 )			select = LEVEL_TYPE::TYPE_MAX - 1;
			}
		}
	}

	//	描画
	void	UpGradeUI::Render( void ) 
	{
		back->Render( IMAGE_MODE::ADOPTPARAM );

		//	レベルアイコン描画
		for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ ) 
		{
			typeIcon[i]->Render( IMAGE_MODE::ADOPTPARAM );

			for ( int j = 0; j < levelManager->LEVEL_MAX; j++ )
			{
				char level = levelManager->GetLevel( i );
				if ( j + 1 <= level )
					levelIcon[i * levelManager->LEVEL_MAX + j]->Render( IMAGE_MODE::NORMAL );
				else
					levelIcon[i * levelManager->LEVEL_MAX + j]->Render( IMAGE_MODE::NORMAL, shader2D, "blackWhite" );
			}
		}

		//	経験値描画
		expUI->Render();

		//	現在レベル描画
		curLevelIcon->Render( IMAGE_MODE::NORMAL );

		flavorText->DrawFont( text, 
			iexSystem::ScreenWidth / 2 - 450, 
			iexSystem::ScreenHeight / 2 + 220, 1000, 720, 0xFFFFFFFF );
	}

//---------------------------------------------------------------------------------------
//	動作関数	
//---------------------------------------------------------------------------------------

	//	決定
	void	UpGradeUI::Dicision( void )
	{
		if ( levelManager->GetLevel( select ) != levelManager->LEVEL_MAX )
		{
			levelManager->SendLevel( select );
		}
	}
	
//---------------------------------------------------------------------------------------
//	情報設定	
//---------------------------------------------------------------------------------------

	//	大アイコン読み込み位置設定
	void	UpGradeUI::SetBigIconSrcPos( void )
	{
		//	レベル取得
		char level = levelManager->GetLevel( select );

		//	フレーバーテキスト読み込み、設定
		text = gameManager->GetFlavorText( select, level + 1 );

		//	画像X座標読み込み位置設定
		if ( level == levelManager->LEVEL_MAX )
		{
			curLevelIcon->sx = ( level - 1 ) * SRC_SIZE;
			text = gameManager->GetFlavorText( select, level );
		}
		else
			curLevelIcon->sx = level * SRC_SIZE;
		
		//	画像Y座標読み込み位置設定
		curLevelIcon->sy = select * SRC_SIZE;
	}

//---------------------------------------------------------------------------------------
//	情報取得	
//---------------------------------------------------------------------------------------

