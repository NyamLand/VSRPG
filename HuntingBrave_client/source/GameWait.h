
#pragma once

//***************************************************************
//
//	GameWait�N���X
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
	iexView*	view;
	NameUI*	nameUI;

	//	�o�b�N�o�b�t�@
	Surface*	backBuffer;

	//	�ϐ�
	int	index;
	int	order[PLAYER_MAX];
	bool	renderFrag[PLAYER_MAX];

public:
	//	�������E���
	GameWait( void );
	~GameWait( void );
	void	Initialize( int index, int* name );
	void	ObjInitialize( int index );
	void	ViewInitialize( int index );
	void	TextureInitialize( int index );

	//	�X�V
	void	Update( void );
	void	UpdateInfo( void );

	//	�`��
	void	Render( void );
	void	MyCharacterRender( void );
	void	OtherPlayerRender( int index );
	void	VSRender( void );

};
