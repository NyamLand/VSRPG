
#pragma	once

//*******************************************************************************
//
//	Screenクラス
//
//*******************************************************************************

namespace
{
	namespace SCREEN_MODE
	{
		enum
		{
			FADE_IN,
			FADE_OUT,
			WHITE_IN,
			WHITE_OUT,
			MAX,
		};
	}
}

//	include
#include	"iextreme.h"

//	class
class Screen
{
private:
	//	パラメータ
	Vector3	color;
	float			param;
	float			alpha;
	float			speed;
	float			startParam[SCREEN_MODE::MAX];
	float			endParam[SCREEN_MODE::MAX];
	bool			screenState;
	int			mode;

private:
	//	初期化・解放
	Screen( void );
	~Screen( void );

public:
	//	更新・描画
	bool	Update( void );
	void	Render( void );

	//	動作関数
	bool	Fade( void );
	bool	Wipe( void );

	//	情報設定
	void	SetScreenMode( int mode, float speed );

	//	情報取得
	float GetWidthFloat( void )const;
	float	GetWidthHalfFloat( void )const;
	float	GetHeightFloat( void )const;
	float	GetHeightHalfFloat( void )const;
	bool	GetScreenState( void )const;
	int	GetWidthInt( void )const;
	int	GetWidthHalfInt( void )const;
	int	GetHeightInt( void )const;
	int	GetHeightHalfInt( void )const;
	static	Screen*	GetInstance( void );
};

#define	screen ( Screen::GetInstance() )