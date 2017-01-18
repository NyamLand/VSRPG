
#pragma once

//***************************************************************
//
//	ExpUIクラス
//
//***************************************************************

#define	EXP_DIGIT	4

namespace EXP_MAX
{
	enum
	{
		ICON_SIZE = 64,				//	画像幅
	};
}

#include	"NumberUI.h"


//	class
class ExpUI
{
protected:
	Image* icon;
	NumberUI*	number;
	int	posx, posy, size;

public:
	//	初期化・解放
	ExpUI( int x, int y, int w, int h );
	virtual	~ExpUI( void );

	//	更新・描画
	void	Update( void );
	void	ExpManager( void );
	void	SetParam( int x, int y, int w, int h );
	void	SetRenderFlag( bool c );
	void	SetExp( int e );
	void	NumberSet( Image* img, const int num, const int digit );
	Image*	GetImageExp( void ){ return icon; }
	void	Render( void );
};

//	必要経験値UI
class NeedExpUI : public ExpUI
{
private:
public:
	//	初期化・解放
	NeedExpUI( int x, int y, int w, int h );
	~NeedExpUI( void );
};



