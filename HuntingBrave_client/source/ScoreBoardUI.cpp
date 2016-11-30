
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	"NumberUI.h"
#include	"ExpUI.h"
#include	"ScoreUI.h"
#include	"ScoreBoardUI.h"
#include	<math.h>

//***************************************************************
//
//	ScoreUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
ScoreBoardUI::ScoreBoardUI(int x, int y, int w, int h)
{
	//	座標、サイズ情報格納
	posx = x;	posy = y;	width = w;	height = h;

	//	BOARD
	board = new Image();
	board->Initialize("DATA/UI/main_UI/ScoreBord.png", posx, posy, width, height, 0, 0, BOARD_MAX::BOARD_WIDTH, BOARD_MAX::BOARD_HEIGHT);
	board->alpha = 0.6f;

	//	プレイヤーアイコン
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		p_icon[i] = new Image();
		p_icon[i]->Initialize("DATA/UI/main_UI/PlIcon.png", 0, 0, BOARD_MAX::ICON_SIZE, BOARD_MAX::ICON_SIZE, 0, 0, BOARD_MAX::ICON_SIZE, BOARD_MAX::ICON_SIZE);

		score[i] = new ScoreUI(0, 0, 0, 0);
		exp[i] = new ExpUI(0, 0, 0, 0);

		//p_icon[i]->alpha = 0.6f;
	}
}

//	デストラクタ
ScoreBoardUI::~ScoreBoardUI(void)
{
	SafeDelete(board);
	for (int i = 0; i < PLAYER_MAX; i++){
		SafeDelete(score[i]);
		SafeDelete(exp[i]);
		SafeDelete(p_icon[i]);
	}
}



//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

//	更新
void	ScoreBoardUI::Update(void)
{
	if (KEY_Get(KEY_SPACE) == 1)
	{
		board->renderflag = true;
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			p_icon[i]->renderflag = true;
			score[i]->SetRenderFlag(true);
			exp[i]->SetRenderFlag(true);
		}
	}
	else
	{
		board->renderflag = false;
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			p_icon[i]->renderflag = false;
			score[i]->SetRenderFlag(false);
			exp[i]->SetRenderFlag(false);
		}
	}

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		p_icon[i]->w = BOARD_MAX::ICON_SIZE;
		p_icon[i]->h = BOARD_MAX::ICON_SIZE;
		p_icon[i]->x = board->x - (board->w / 2) + p_icon[i]->w;	//	左端
		p_icon[i]->y = board->y + (BOARD_MAX::BOARD_MARGIN / BOARD_PER)
			- ((board->h - (BOARD_MAX::BOARD_MARGIN / BOARD_PER)) / 2)
			+ ((board->h - (BOARD_MAX::BOARD_MARGIN / BOARD_PER)) / 4) * i;	//	上から順に配置

		p_icon[i]->sx = 0; p_icon[i]->sy = 64 * i;
		p_icon[i]->sw = BOARD_MAX::ICON_SIZE;
		p_icon[i]->sh = BOARD_MAX::ICON_SIZE;
		
		int w = (board->w - p_icon[i]->w) / 2;
		int x = p_icon[i]->x + w -  w / 2;
		score[i]->SetParam(x, p_icon[i]->y, p_icon[i]->w, p_icon[i]->h);
		score[i]->Update();
		
		x = x + w;
		exp[i]->SetParam(x, p_icon[i]->y, p_icon[i]->w, p_icon[i]->h);
		exp[i]->Update();
	}
}


//	描画
void	ScoreBoardUI::Render(void)
{
	board->Render(IMAGE_MODE::ADOPTPARAM);

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		p_icon[i]->Render(IMAGE_MODE::ADOPTPARAM);
		score[i]->Render();
		exp[i]->Render();
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

