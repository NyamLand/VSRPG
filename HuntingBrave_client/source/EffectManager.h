
#pragma once

//************************************************************************
//
//	EffectManager�N���X
//
//************************************************************************

//	include
#include	"Singleton.h"
#include	"Effect.h"
#include	"Circle.h"
#include	"GameData.h"

//	class
class EffectManager : public Singleton<EffectManager>
{
	friend	Singleton<EffectManager>;
private:
	Circle* circle[PLAYER_MAX];

private:

	//	�������E���
	EffectManager( void );
	~EffectManager( void );

public:
	bool	Initialize( void );
	void	Release( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	�T�[�N���`��
	void	SetCircleRender( int player );
};

#define	effectManager ( EffectManager::GetInstance() )