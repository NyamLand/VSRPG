
#pragma once

//*******************************************************************************
//
//	RandomƒNƒ‰ƒX
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
	//	‰Šú‰»E‰ğ•ú
	bool	Initialize( void );
	void	Release( void );

	//	“®ìŠÖ”
	int		GetInt( int min, int max );
	float		GetFloat( float min, float max );
	bool		PercentageRandom( float probability );
};

#define	random ( Random::GetInstance() )
