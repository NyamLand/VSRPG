
#pragma once

//*******************************************************************************
//
//	Random�N���X
//
//*******************************************************************************

//	include
#include	<random>
#include	"Singleton.h"
using namespace std;

//	class
class Random : public Singleton<Random>
{
	friend Singleton<Random>;

private:
	std::mt19937* rnd;
	Random( void );
	~Random( void );

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );

	//	����֐�
	int		GetInt( int min, int max );
	float		GetFloat( float min, float max );
	bool		PercentageRandom( float probability );
};

#define	random ( Random::GetInstance() )
