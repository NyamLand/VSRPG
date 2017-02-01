
#pragma once

//***************************************************************
//
//	PlayerNumUIクラス
//
//***************************************************************

//	class
class PlayerNumUI
{
protected:
	Image* numImage;

public:
	//	初期化・解放
	PlayerNumUI( int player, int x, int y, int w, int h );
	~PlayerNumUI( void );

	//	更新・描画
	void	Update( int player );
	void	Update( int x, int y, int w, int h );
	void	Render( void );
};

