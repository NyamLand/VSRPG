
#pragma once

//*****************************************************************
//
//	Timer�N���X
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
	//	�������E���
	Timer( void );
	~Timer( void );
	void	Initialize( void );

	//	�X�^�[�g�ݒ�
	void	Start( float limit );

	//	�X�V
	bool	Update( void );

	//	���擾
	float	GetRemainingTime( void )const;
	float	GetErapseTime( void )const;
};
