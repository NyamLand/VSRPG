
#pragma once

//************************************************************************
//
//	EffectManager�N���X
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

	//	�������E���
	EffectManager( void );
	~EffectManager( void );

public:
	bool	Initialize( void );
	void	Release( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
};
