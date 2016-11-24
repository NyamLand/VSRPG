
#pragma once

//**************************************************************************
//
//	MagicManagerクラス
//
//**************************************************************************

//	include
#include	"Magic.h"

//	class
class MagicManager
{
private:
	std::vector<Magic*>	magicList;

public:
	//	初期化・解放
	MagicManager( void );
	~MagicManager( void );

	//	更新
	void	Update( void );

	//	動作関数
	void	Append( int id, const Vector3& pos, const Vector3& vec );

	//	情報設定

	//	情報取得

};

extern	MagicManager*	magicManager;