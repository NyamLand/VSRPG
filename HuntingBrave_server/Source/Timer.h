
#pragma once

//*****************************************************************
//
//	Timer�N���X
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
	//	�������E���
	Timer( void );
	~Timer( void );

	//	�X�^�[�g�ݒ�
	void	Start( int limit );

	//	�X�V
	bool	LimitTimerUpdate( void );

	//	���擾
	int		GetLimitTime( void )const;
};
