
#pragma once

//***************************************************************
//
//	Result�N���X
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

	//	�o�b�N�o�b�t�@
	Surface*	backBuffer;

	//	�ϐ�
	int	index;
	int	order[PLAYER_MAX];
	bool	renderFrag[PLAYER_MAX];

public:
	//	�������E���
	Result( void );
	~Result( void );
	void	Initialize( int index );
	void	ObjInitialize( int index );
	void	ViewInitialize( int index );
	void	TextureInitialize( int index );
	void	NameUIInitialize( int index );
	void	PlayerTitleUIInitialize( int index );

	//	�X�V
	void	Update( void );
	void	UpdateInfo( void );
	void	UpdateName( void );
	void	UpdatePlayerTitle( void );

	//	�`��
	void	Render( void );
	void	MyCharacterRender( void );
	void	OtherPlayerRender( int index );
	void	NameUIRender( void );
	void	PlayerTitleUIRender( void );
	void	VSRender( void );

};
