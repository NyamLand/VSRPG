
#pragma once

//*****************************************************************
//
//	Timerクラス
//
//*****************************************************************

//	include
#include	<time.h>
#include	<chrono>

//	class
class Timer
{
private:
	std::chrono::time_point<std::chrono::system_clock>	start, now;
	float	end, remaining;

public:
	//	初期化・解放
	Timer( void );
	~Timer( void );
	void	Initialize( void );

	//	スタート設定
	void	Start( float limit );

	//	更新
	bool	Update( void );

	//	情報取得
	float	GetRemainingTime( void )const;
	float	GetErapseTime( void )const;
};
