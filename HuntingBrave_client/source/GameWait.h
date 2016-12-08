
#pragma once

//***************************************************************
//
//	GameWaitクラス
//
//***************************************************************

//	include
#include	"NameUI.h"
#include	"GameData.h"

//	class
class GameWait
{
private:
	iex2DObj*	back;
	iex3DObj*	obj[PLAYER_MAX];
	iex2DObj*	targetTex[PLAYER_MAX];
	iexView*	view[PLAYER_MAX];
	NameUI*	nameUI;

	//	バックバッファ
	Surface*	backBuffer;

	//	変数
	int	index;
	int	order[PLAYER_MAX];
	bool	renderFrag[PLAYER_MAX];

public:
	//	初期化・解放
	GameWait( void );
	~GameWait( void );
	void	Initialize( int index, int* name );
	void	ObjInitialize( int index );
	void	ViewInitialize( int index );
	void	TextureInitialize( int index );

	//	更新・描画
	void	Update( void );
	void	Render( void );
	void	MyCharacterRender( void );
	void	OtherPlayerRender( int index );
	void	UpdateInfo( void );
};
