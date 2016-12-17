
#pragma once

//************************************************************************
//
//	EffectManagerクラス
//
//************************************************************************

//	include
#include	"Effect.h"
#include	"Singleton.h"

//	class
class EffectManager : Singleton<EffectManager>
{
	friend	Singleton<EffectManager>;
private:
	std::list<Effect*>	effectList;

	//	初期化・解放
	EffectManager( void );
	~EffectManager( void );

public:
	bool	Initialize( void );
	void	Release( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
};
