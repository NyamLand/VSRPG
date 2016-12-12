
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<map>
#include	"Interpolation.h"
#include	"GameParam.h"
#include	"InputManager.h"
#include	"NameManager.h"
#include	"NameUI.h"

//***************************************************************
//
//	NameUIクラス
//
//***************************************************************

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

#define	SRC_X_MAX		10
#define	SRC_Y_MAX		5
#define	SRC_SIZE			64
#define	DAKUTEN			60

//----------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------

	//	コンストラクタ
	NameUI::NameUI( void ) : posX( 0 ), posY( 0 ), space( 0 ), scale( 0 )
	{
		for ( int i = 0; i < NAME_MAX; i++ )
		{
			nameImage[i] = nullptr;
		}
	}

	//	デストラクタ
	NameUI::~NameUI( void )
	{
		for (int i = 0; i < NAME_MAX; i++ )
		{
			SafeDelete( nameImage[i] );
		}
	}

	//	初期化
	bool	NameUI::Initialize( int x, int y, int w, int h, int* name )
	{
		scale = w;
		space = w + 10;
		posX = x;
		posY = y;

		for ( int i = 0; i < NAME_MAX; i++ )
		{
			nameImage[i] = new Image();
			nameImage[i]->Initialize( "DATA/UI/main_UI/ward.png", x, y, w, h, 0, 0, SRC_SIZE, SRC_SIZE );
			
			//	読み込み位置設定
			if ( name[i] == 0 )
			{
				nameImage[i]->sy = 0;
				nameImage[i]->sx = 0;
			}
			else
			{
				int sx, sy;
				if ( name[i] != 0 )
				{
					sy = name[i] / SRC_X_MAX;
					sx = name[i] % SRC_X_MAX;
				}
				else
				{
					sx = 0; sy = 0;
				}
				nameImage[i]->sy = sy * SRC_SIZE;
				nameImage[i]->sx = sx * SRC_SIZE;
			}
		}
		return	true;
	}

//----------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------

	//	更新
	void	NameUI::Update( void )
	{
		for ( int i = 0; i < NAME_MAX; i++ ) 
		{
			nameImage[i]->x = ( int )( posX - ( space * 1.5f ) + ( space * i ) );
			nameImage[i]->y = posY;
		}
	}

	//	描画
	void	NameUI::Render( void )
	{
		for ( int i = 0; i < NAME_MAX; i++ )
		{
			nameImage[i]->Render( IMAGE_MODE::NORMAL );
		}
	}

//----------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------

	//	座標設定
	void	NameUI::SetPos( int posx, int posy )
	{
		posX = posx;
		posY = posy;
	}

	//	間隔設定
	void	NameUI::SetSpace( int space )
	{
		this->space = space;
	}

//----------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------

