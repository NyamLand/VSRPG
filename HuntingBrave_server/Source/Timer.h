
#pragma once

//*****************************************************************
//
//	Timerクラス
//
//*****************************************************************

//	include
#include	<time.h>

//	class
class Timer
{
private:
	time_t	startTime, endTime, nowTime;

public:
	//	初期化・解放
	Timer( void );
	~Timer( void );

	//	スタート設定
	void	Start( int limit );

	//	更新
	bool	LimitTimerUpdate( void );

	//	情報取得
	int		GetLimitTime( void )const;
};
