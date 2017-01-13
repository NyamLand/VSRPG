
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Random.h"
#include	"EnemyManager.h"
#include	"UIManager.h"
#include	"GameParam.h"
#include	"LevelManager.h"
//***************************************************************
//
//	UIManagerクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
UIManager::UIManager(void)
{

}

//	デストラクタ
UIManager::~UIManager(void)
{
	Release();
}

//	初期化
bool	UIManager::Initialize( void )
{
	//---------------------------------------
	//	HPバーのポジションをセット(左下）
	//---------------------------------------
	int width = (int)(HP_MAX::WIDTH / 2.5f);			//	スケール1/2.5
	int height = (int)(HP_MAX::HEIGHT / 2.5f);			//	スケール1/2.5
	int posx = width / 2;								//	中心から端までの距離
	int posy = iexSystem::ScreenHeight - height / 2;	//	画面端から画像の中心から端までの距離引く

	hpUI = new HpUI(posx, posy, width, height);
	itemUI = new ItemUI(posx, posy, width, height);

	//---------------------------------------
	//	Timerのポジションをセット(真ん中の上)
	//---------------------------------------
	width = TIME_MAX::WIDTH;
	height = TIME_MAX::HEIGHT;
	posx = iexSystem::ScreenWidth / 2;
	posy = TIME_MAX::HEIGHT;

	timerUI = new TimerUI(posx, posy, width, height);

	//---------------------------------------
	//	EXPのポジションをセット
	//---------------------------------------
	Image* HP = hpUI->GetImageHp();					//	経験値のポジションを獲得

	width =  HP->w / 6;
	height = HP->h;
	posx = HP->x + width / 2;
	posy = HP->y - height / 2 - width / 6;

	expUI = new ExpUI(posx, posy, width, height);

	//---------------------------------------
	//	SCOREのポジションをセット
	//---------------------------------------
	Image* EXP = expUI->GetImageExp();					//	経験値のポジションを獲得
	scoreUI = new ScoreUI(EXP->x, EXP->y - EXP->w / 2 - EXP->w / 6, EXP->w, EXP->h);

	//---------------------------------------
	//	マップのポジションをセット(右上）
	//---------------------------------------
	width = (int)(MAP_MAX::WIDTH / 2.5f);			//	スケール1/2.5
	height = (int)(MAP_MAX::HEIGHT / 2.5f);			//	スケール1/2.5
	posx = iexSystem::ScreenWidth - (width / 2);	//	中心から端までの距離
	posy = height / 2;								//	画面端から画像の中心から端までの距離引く

	mapUI = new MapUI(posx, posy, width, height);

	//---------------------------------------
	//	スコアボードのポジションをセット(中心）
	//---------------------------------------
	width = (int)(BOARD_MAX::BOARD_WIDTH / BOARD_PER );
	height = (int)(BOARD_MAX::BOARD_HEIGHT / BOARD_PER );
	posx = iexSystem::ScreenWidth / 2;				//	画面の中心
	posy = iexSystem::ScreenHeight / 2;				//	画面の中心

	boardUI = new ScoreBoardUI( posx, posy, width, height );
	
	//	プレイヤー自身のナンバーセット
	p_num = gameParam->GetMyIndex();
	//	neta
	yaju = new Image();
	yaju->Initialize( "DATA/UI/main_UI/Yaju.png", posx, posy, 0, 0, 0, 0, 960, 540 );
	yaju->SetScaling( 0.01f );

	upGradeUI = new UpGradeUI();
	check = false;
	return	true;
}

//	解放
void	UIManager::Release( void )
{
	SafeDelete( timerUI );
	SafeDelete( hpUI );
	SafeDelete( expUI );
	SafeDelete( itemUI );
	SafeDelete( mapUI );
	SafeDelete( scoreUI );
	SafeDelete( boardUI );
	SafeDelete( upGradeUI );
}

//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

//	更新
void	UIManager::Update( void )
{
	timerUI->Update();
	hpUI->Update();
	expUI->Update();
	itemUI->Update();
	mapUI->Update();
	scoreUI->Update();
	boardUI->Update();
	upGradeUI->Update();
	

	//	値セット
	scoreUI->SetScore(gameParam->GetPointInfo(p_num).point);
	expUI->SetExp(levelManager->GetExp());

	if (KEY_Get(KEY_SPACE) == 3 && random->GetInt(0, 3000) == 1)	check = true;
	if (check){
		//	neta
		if (yaju->scalingState != IMAGE_SCALING::SMALL)
		{
			yaju->ScalingUpdate(iexSystem::ScreenHeight);
		}
		else
		{
			yaju->renderflag = false;
		}
	}
}
//	描画
void	UIManager::Render( void )
{
	enemyManager->RenderHp();
	timerUI->Render();
	hpUI->Render();
	expUI->Render();
	itemUI->Render();
	mapUI->Render();
	scoreUI->Render();
	boardUI->Render();
	upGradeUI->Render();
	yaju->Render(IMAGE_MODE::SCALING);
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

