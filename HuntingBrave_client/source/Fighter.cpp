
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"GameParam.h"
#include	"Fighter.h"

//***************************************************************
//
//	Fighterクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Fighter::Fighter( void )
	{
		
	}

	//	デストラクタ
	Fighter::~Fighter( void )
	{

	}

	//	初期化
	bool	Fighter::Initialize( int id )
	{
		//	初期化
		Player::Initialize( id );

		return	true;
	}

//------------------------------------------------------------------------------------
//	更新・描画
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	テクスチャ設定
	//void	Fighter::ChangeTexture( int colorNum )
	//{
	//	//	ファイル設定
	//	sprintf_s( fileName, "DATA/CHR/Fighter/%dpColor/body.png", colorNum + 1 );
	//	obj->SetTexture( 0, fileName );
	//	sprintf_s( fileName, "DATA/CHR/Fighter/%dpColor/toumeitachi.png", colorNum + 1 );
	//	obj->SetTexture( 3, fileName );
	//}
