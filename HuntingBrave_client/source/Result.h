
#pragma once

//***************************************************************
//
//	Resultクラス
//
//***************************************************************

//	include
#include	"NameUI.h"
#include	"PlayerTitleUI.h"
#include	"GameData.h"

//	class
class Result
{
private:
	iex2DObj*	back;
	iex3DObj*	obj[PLAYER_MAX];
	iex2DObj*	targetTex[PLAYER_MAX];
	iexView*	view;
	NameUI*	nameUI[PLAYER_MAX];
	PlayerTitleUI*	playerTitleUI[PLAYER_MAX];

	//	バックバッファ
	Surface*	backBuffer;

	//	変数
	int	index;
	int	order[PLAYER_MAX];
	bool	renderFrag[PLAYER_MAX];

public:
	//	初期化・解放
	Result( void );
	~Result( void );
	void	Initialize( int index );
	void	ObjInitialize( int index );
	void	ViewInitialize( int index );
	void	TextureInitialize( int index );
	void	NameUIInitialize( int index );
	void	PlayerTitleUIInitialize( int index );

	//	更新
	void	Update( void );
	void	UpdateInfo( void );
	void	UpdateName( void );
	void	UpdatePlayerTitle( void );

	//	描画
	void	Render( void );
	void	MyCharacterRender( void );
	void	OtherPlayerRender( int index );
	void	NameUIRender( void );
	void	PlayerTitleUIRender( void );
	void	VSRender( void );

};
