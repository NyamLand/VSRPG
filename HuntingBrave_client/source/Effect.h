
#pragma once

//***************************************************************
//
//	Effectクラス
//
//***************************************************************

//	include

//	class
class Effect
{
protected:
	bool	eraseFlag;

public:
	//	初期化・解放
	Effect( void ) : eraseFlag( false ){}
	virtual ~Effect( void ){};

	//	更新・描画
	virtual	void	Update( void ) = 0;
	virtual	void	Render( void ) = 0;

	//	消去フラグ取得
	bool	GetEraseFlag( void ){ return	eraseFlag; }
};
