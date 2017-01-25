
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"Camera.h"
#include	"Image.h"
#include	"MapUI.h"

//***************************************************************
//
//	MapUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//	マップ、レーダー距離
#define	MAP_MAX_LENGTH		400.0f
#define	RADER_LENGTH		50.0f

//	マップUIサイズ
#define	MAP_SIZE		250
#define	MAP_POS_X		1150
#define	MAP_POS_Y		130
#define	MAP_SRC_SIZE	512

//	アイコンUIサイズ
#define	ICON_SIZE	15
#define	MY_ICON_SIZE	20
#define	ICON_MAX_POS	125
#define	ICON_SRC_POS	512
#define	ICON_SRC_SIZE	32

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

	//	コンストラクタ
	MapUI::MapUI( void )
	{
		//	座標、サイズ情報格納
		posx = MAP_POS_X;	
		posy = MAP_POS_Y;	
		width = MAP_SIZE;	
		height = MAP_SIZE;

		//	自分のID取得
		myIndex = gameParam->GetMyIndex();

		//	レーダー背景初期化
		back = new Image();
		back->Initialize( "DATA/UI/main_UI/Map_UI.png", 
			MAP_POS_X, MAP_POS_Y, 
			MAP_SIZE, MAP_SIZE, 
			0, 0, MAP_SRC_SIZE, MAP_SRC_SIZE );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			player[i] = new Image();
			player[i]->Initialize( "DATA/UI/main_UI/Map_UI.png",
				MAP_POS_X, MAP_POS_Y,
				ICON_SIZE, ICON_SIZE,
				ICON_SRC_POS + ICON_SRC_SIZE * ( i % 2 ), 
				ICON_SRC_SIZE * ( i / 2 ), 
				ICON_SRC_SIZE, ICON_SRC_SIZE );

			if ( !gameParam->GetPlayerActive( i ) )	player[i]->renderflag = false;

			//	自キャラだけ若干大きく表示
			if ( gameParam->GetMyIndex() == i )
			{
				player[i]->w = player[i]->h = MY_ICON_SIZE;
			}
		}
	}

	//	デストラクタ
	MapUI::~MapUI( void )
	{
		SafeDelete( back );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			SafeDelete( player[i] );
		}
	}

//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

	//	更新
	void	MapUI::Update( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( !gameParam->GetPlayerActive( i ) )	continue;

			PlayerParam	playerParam = gameParam->GetPlayerParam( i );

			//	自キャラからの距離を求める
			Vector3 vec = playerParam.pos - gameParam->GetPlayerParam( myIndex ).pos;

			//	マップ表示用に割合を求める
			float percentage = vec.Length() / RADER_LENGTH;

			//	マップ上のアイコン距離を求める
			float	length = 0.0f;
			if ( percentage >= 1.0f )	length = ICON_MAX_POS;
			else  length = ICON_MAX_POS * percentage;

			//	距離からアイコン座標を求める
			vec.Normalize();
			Vector3 iconPos = vec * length;
			
			//	カメラ方向取得
			Vector3	vEye( mainView->GetTarget() - mainView->GetPos() );
			float	cameraAngle = atan2f( vEye.x, vEye.z );
			iconPos.x *= cosf( cameraAngle );
			iconPos.z *= sinf( cameraAngle );

			//	アイコン座標設定
			player[i]->x = player[i]->p.x = MAP_POS_X + ( int )iconPos.x;
			player[i]->y = player[i]->p.y = MAP_POS_Y - ( int )iconPos.z;

			//	アイコン向き設定
			player[i]->angle = playerParam.angle * cameraAngle;
		}
	}

	//	描画
	void	MapUI::Render( void )
	{
		back->Render( IMAGE_MODE::ADOPTPARAM );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			player[i]->Render( IMAGE_MODE::ADOPTPARAM );
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

