
#pragma once

//************************************************************************
//
//	EffectManagerクラス
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

	//	初期化・解放
	EffectManager( void );
	~EffectManager( void );

public:
	bool	Initialize( void );
	void	Release( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	サークル描画
	void	SetCircleRender( int player );
};

#define	effectManager ( EffectManager::GetInstance() )