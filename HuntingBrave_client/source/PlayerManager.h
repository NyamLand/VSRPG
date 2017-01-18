
#pragma once

//***************************************************************
//
//	PlayerManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"Suppin.h"
#include	"Fighter.h"
#include	"Magician.h"
#include	"Player.h"


namespace
{
	namespace PLAYER_TYPE
	{
		enum
		{
			NORMAL,
			FIGHTER,		//	ファイター
			MAGICIAN,	//	マジシャン
			KNIGHT,		//	ナイト
			PRIEST,		//	プリースト
			ASSASSIN,	//	アサシン
			MODEL_MAX
		};
	}
}

//	class
class PlayerManager : public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;
public:


private:
	//	元モデル
	iex3DObj*	obj[PLAYER_TYPE::MODEL_MAX];

	//	パラメータ
	std::vector<Player*>	playerList;

	//	初期化・解放
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void );
	void	Release( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
	void	RenderHp( void );

	//	動作関数
	void	ClassChange( int id, char nextClass );
	
	//	情報設定
	void	SetPlayer( int id );

	//	情報取得
	Player*&	GetPlayer( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )
