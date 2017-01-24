
#pragma once

//*******************************************************************************
//
//	RandomƒNƒ‰ƒX
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

	//	‰Šú‰»E‰ğ•ú
	static	bool	Initialize( void );
	static	void	Release( void );

	//	“®ìŠÖ”
	static	int		GetInt( int min, int max );
	static	float		GetFloat( float min, float max );
	static	bool		PercentageRandom( float probability );
};
