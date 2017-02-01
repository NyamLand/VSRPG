
#pragma once

//***************************************************************
//
//	RankUIクラス
//
//***************************************************************

//	class
class RankUI
{
protected:
	Image* rankImage;

public:
	//	初期化・解放
	RankUI( int x, int y, int w, int h );
	~RankUI( void );

	//	更新・描画
	void	Update( int player );
	void	Update( int x, int y, int w, int h );
	void	Render( void );
};

