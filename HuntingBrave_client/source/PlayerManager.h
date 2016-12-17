
#pragma once

//***************************************************************
//
//	PlayerManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"Player.h"


namespace
{
	namespace PLAYER_MODEL_TYPE
	{
		enum
		{
			NORMAL,
			MAGICIAN,	//	マジシャン
			PRIEST,		//	プリースト
			FIGHTER,		//	ファイター
			KNIGHT,		//	ナイト
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
	iex3DObj*	obj[PLAYER_MODEL_TYPE::MODEL_MAX];

	//	パラメータ
	Player*	player[PLAYER_MAX];

	//	初期化・解放
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void );
	void	Release( void );
	void	LoadModel( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
	void	RenderHp( void );
	
	//	情報設定
	void	SetPlayer( int id );
	void	PlayerClassChange( char nextType );

	//	情報取得
	Player*&	GetPlayer( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )
