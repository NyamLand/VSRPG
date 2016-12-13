
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"LevelManager.h"
#include	"UpGradeUI.h"

//***************************************************************
//
//	UpGradeUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

#define	BOARD_ALPHA	0.6f
#define	SELECT_CENTER_DIST	170
#define	ICON_START_DIST	400
#define	ICON_SCALE	70
#define	ICON_SPACE	100
#define	LEVEL_ICON_DIST	50
#define	LEVEL_ICON_SCALE	45

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

	//	コンストラクタ
	UpGradeUI::UpGradeUI( void ) : back( nullptr )
	{
		int x = iexSystem::ScreenWidth / 2;
		int y = iexSystem::ScreenHeight / 2;
		int w = ( int )( iexSystem::ScreenWidth / 1.25f );
		int h = ( int )( iexSystem::ScreenHeight / 1.25f );

		//	背景初期化
		back = new Image();
		back->Initialize( "DATA/UI/BackGround/Upgrade_UI.png", x, y, w, h, 0, 0, 1280, 720 );
		back->alpha = BOARD_ALPHA;

		//	アイコン初期化
		typeIcon = new Image*[LEVEL_TYPE::TYPE_MAX];
		levelIcon = new Image*[LEVEL_TYPE::TYPE_MAX * levelManager->LEVEL_MAX];
		for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
		{
			//	タイプ選択用アイコン
			typeIcon[i] = new Image();
			typeIcon[i]->Initialize( "DATA/UI/icon/Upgrade/icon.png", 
				x -  ICON_START_DIST + ( i * ICON_SPACE ),
				y + SELECT_CENTER_DIST, 
				ICON_SCALE, ICON_SCALE, 0, 0, 64, 64 );
			typeIcon[i]->alpha = BOARD_ALPHA;

			//	レベル管理用アイコン
			for ( int j = 0; j < levelManager->LEVEL_MAX; j++ )
			{
				levelIcon[i * levelManager->LEVEL_MAX + j] = new Image();
				levelIcon[i *levelManager->LEVEL_MAX + j]->Initialize( "DATA/UI/icon/Upgrade/icon.png",
					typeIcon[i]->x,
					( typeIcon[i]->y - ICON_SCALE ) - ( LEVEL_ICON_DIST * j ),
					LEVEL_ICON_SCALE, LEVEL_ICON_SCALE, 0, 0, 64, 64 );
				levelIcon[i * levelManager->LEVEL_MAX + j]->alpha = BOARD_ALPHA;
			}
		}
	}

	//	デストラクタ
	UpGradeUI::~UpGradeUI( void )
	{
		SafeDelete( back );
		SafeDeleteArray( typeIcon );
	}
	
//---------------------------------------------------------------------------------------
//	更新・描画	
//---------------------------------------------------------------------------------------

	//	更新
	void	UpGradeUI::Update( void )
	{

	}

	//	描画
	void	UpGradeUI::Render( void ) 
	{
		back->Render( IMAGE_MODE::ADOPTPARAM );

		for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ ) 
		{
			typeIcon[i]->Render( IMAGE_MODE::ADOPTPARAM );

			for ( int j = 0; j < levelManager->LEVEL_MAX; j++ )
			{
				levelIcon[i * levelManager->LEVEL_MAX + j]->Render( IMAGE_MODE::ADOPTPARAM );
			}
		}
	}

//---------------------------------------------------------------------------------------
//	動作関数	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	情報設定	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	情報取得	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------
 

