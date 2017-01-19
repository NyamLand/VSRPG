
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

//	濁点、半濁点
#define	VOICED_SPOT_INDEX		56
#define	SEMI_VOICED_SPOT_INDEX	57
#define	SRC_SEMIVOICED_SPOT_CHAR_X  640
#define	SRC_SEMIVOICED_SPOT_CHER_Y	64

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
	bool	NameUI::Initialize( int x, int y, int w, int h )
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
			nameImage[i]->sy = 0;
			nameImage[i]->sx = 0;
		}
		return	true;
	}

//----------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------

	//	更新
	void	NameUI::Update( int* name )
	{
		for ( int i = 0; i < NAME_MAX; i++ ) 
		{
			//	座標設定
			nameImage[i]->x = ( int )( posX - ( space * 1.5f ) + ( space * i ) );
			nameImage[i]->y = posY;

			//	読み込み位置を指定
			if ( name[i] < 60 )
			{
				NormalCharacterSet( name, i );
			}
			else
			{
				VoicedSpotCharacterSet( name, i );
			}
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

	//	通常文字設定
	void	NameUI::NormalCharacterSet( int* name, int index )
	{
		//	通常文字設定
		if ( name[index] == 0 )
		{
			nameImage[index]->sy = 0;
			nameImage[index]->sx = 0;
		}
		else
		{
			int sx, sy;
			if ( name[index] != 0 )
			{
				sy = name[index] / SRC_X_MAX;
				sx = name[index] % SRC_X_MAX;
			}
			else
			{
				sx = 0; sy = 0;
			}

			nameImage[index]->sy = sy * SRC_SIZE;
			nameImage[index]->sx = sx * SRC_SIZE;
		}
	}

	//	濁点、半濁点文字設定
	void	NameUI::VoicedSpotCharacterSet( int* name, int index )
	{
		//	半濁点時
		if ( name[index] >= 90 )
		{
			nameImage[index]->sx =
				SRC_SEMIVOICED_SPOT_CHAR_X + ( ( name[index] % 5 ) * SRC_SIZE );

			nameImage[index]->sy = SRC_SEMIVOICED_SPOT_CHER_Y;
		}
		else
		{
			//	濁点時
			nameImage[index]->sx = ( ( name[index] - 5 ) % 10 * SRC_SIZE );
			nameImage[index]->sy = ( ( name[index] - 5 ) / 10 * SRC_SIZE );
		}
	}

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

