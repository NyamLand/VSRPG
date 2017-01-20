
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"Interpolation.h"
#include	"InputManager.h"
#include	"KillLogUI.h"

//*************************************************************************
//
//	KillLogUIクラス
//
//*************************************************************************

//-------------------------------------------------------------------------------------
//	グローバル
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
	//	画像順番対応表( プレイヤー人数＋大型敵)
	int killInfo[][PLAYER_MAX + 1] =
	{
		{ -1, 0, 1, 2, DEAD_ENEMY },
		{ 0, -1, 1, 2, DEAD_ENEMY },
		{ 0, 1, -1, 2, DEAD_ENEMY },
		{ 0, 1, 2, -1, DEAD_ENEMY }
	};
}

//-------------------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------------------

	//	コンストラクタ
	KillLogUI::KillLogUI( void ) : killLogImage( nullptr ),
		percentage( 1.0f ), killFrag( false )
	{
		//	画像構造体初期化
		killLogImage = new Image();
		killLogImage->Initialize(
			"DATA/UI/main_UI/Kill_log.png",
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 2,
			KILL_LOG_WIDTH, KILL_LOG_HEIGHT,
			0, 0, SRC_WIDTH, SRC_HEIGHT );

		//	表示しない
		killLogImage->renderflag = false;
	}

	//	デストラクタ
	KillLogUI::~KillLogUI( void )
	{
		SafeDelete( killLogImage );
	}

//-------------------------------------------------------------------------------------
//	更新・描画
//-------------------------------------------------------------------------------------

	//	更新
	void	KillLogUI::Update( void )
	{
		//	補間
		Interpolation::LinearInterpolation( killLogImage->y,
			( int )iexSystem::ScreenHeight / 2,
			( int )iexSystem::ScreenHeight / 2 - KILL_LOG_DIST,
			percentage );

		//	補間パラメータ更新
		bool lerpState = Interpolation::PercentageUpdate( percentage, LERP_SPEED );

		//	補間が完了したら消す
		if ( lerpState )
		{
			killLogImage->renderflag = false;
		}
	}

	//	描画
	void	KillLogUI::Render( void )
	{
		killLogImage->Render( IMAGE_MODE::ADOPTPARAM );
	}

//-------------------------------------------------------------------------------------
//	動作関数
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

	//	キルログ設定
	void	KillLogUI::SetKillLog( int killer, int dead )
	{
		//	割合初期化
		percentage = 0.0f;
		
		//	読み込み位置設定
		killLogImage->sx = killInfo[killer][dead] % 2;
		killLogImage->sy = SRC_POS_PLAYER * killer + SRC_HEIGHT * ( killInfo[killer][dead] / 2 );

		killLogImage->renderflag = true;
	}

//-------------------------------------------------------------------------------------
//	情報取得
//-------------------------------------------------------------------------------------



