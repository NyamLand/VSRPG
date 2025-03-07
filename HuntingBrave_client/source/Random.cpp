
#include	"iextreme.h"
#include	"Random.h"

//*******************************************************************************
//
//	Randomクラス
//
//*******************************************************************************

//--------------------------------------------------------------------------------
//	グローバル
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//	初期化・解放
//--------------------------------------------------------------------------------

	//	コンストラクタ
	Random::Random( void )
	{
		Initialize();
	}

	//	デストラクタ
	Random::~Random( void )
	{
		Release();
	}

	//	初期化
	bool	Random::Initialize( void )
	{
		rnd = new std::mt19937( std::random_device()() );
		return	true;
	}

	//	解放
	void	Random::Release( void )
	{
		if ( rnd != nullptr )
		{
			delete	rnd;
			rnd = nullptr;
		}
	}

//--------------------------------------------------------------------------------
//	情報取得
//--------------------------------------------------------------------------------

	//	整数型乱数取得
	int		Random::GetInt( int min, int max )
	{
		std::uniform_int_distribution<int>	_dist( min, max );
		return	_dist( *rnd );
	}

	//	実数型乱数取得
	float	Random::GetFloat( float min, float max )
	{
		std::uniform_real_distribution<float>	_dist( min, max );
		return	_dist( *rnd );
	}

	//	百分率でのランダム
	bool	Random::PercentageRandom( float probability )
	{
		std::bernoulli_distribution _dist( probability );

		return _dist( *rnd );
	}