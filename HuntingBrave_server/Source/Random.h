
#pragma once

//*******************************************************************************
//
//	Randomクラス
//
//*******************************************************************************

//	include
#include	<random>
using namespace std;

//	class
class Random
{
private:
	static	std::mt19937* rnd;

public:
	Random( void );
	~Random( void );

	//	初期化・解放
	static	bool	Initialize( void );
	static	void	Release( void );

	//	動作関数
	static	int		GetInt( int min, int max );
	static	float		GetFloat( float min, float max );
	static	bool		PercentageRandom( float probability );
};
