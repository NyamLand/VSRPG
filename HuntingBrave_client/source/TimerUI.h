
#pragma once

//***************************************************************
//
//	TimerUIクラス
//
//***************************************************************

//	include

//	class
class TimerUI
{
private:
	int		timer;

public:
	//	初期化・解放
	TimerUI( void );
	~TimerUI( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
};

