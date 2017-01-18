
#pragma once

//***************************************************************
//
//	Suppinクラス
//
//***************************************************************

//	incude
#include	"Player.h"

//	class
class Suppin : public Player
{
private:

public:
	//	初期化・解放
	Suppin( void );
	~Suppin( void );
	bool	Initialize( int id )override;
	
	//	更新・描画

	//	動作関数
	void	ChangeTexture( int colorNum )override;

	//	情報設定
	
	//	情報取得
};
