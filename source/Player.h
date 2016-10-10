
#pragma once

//***************************************************************
//
//	Playerクラス
//
//***************************************************************

//	include
#include	"BaseChara.h"

namespace MODE
{
	enum	//	仮
	{
		MOVE,
		//POSTURE,
		SWOADATTACK,
		MAGICATTACK,
		MODE_MAX
	};
}

//*仮モデルに対して
namespace MOTION
{
	enum
	{
		HOPPING,
		RIGOR,
		WAIT,
		HOPPING2,
		MOVE,
		ATTACK,
		ATTACK2 = 7,
	};
}
//	class
class Player : public BaseChara
{
private:

	//	モード別関数ポインタ
	void( Player::*ModeFunction[MODE::MODE_MAX] )( void );

	iex2DObj*	texture;


public:
	//	初期化・解放
	Player( void );
	~Player( void )override;
	bool	Initialize( void )override;
	
	//	更新・描画
	void	Update( void )override;
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	各モード動作関数
	void	MoveMode( void );
	//void	PostureMode( void );
	void	ModeSwordAttack(void);
	void	ModeMagicAttack( void );


	//	動作関数
	int		Move( void );
	int		SwordAttack(void);		//行動が終了すれば1を返し、中断されれば2を返す
	int		MagicAttack( void );


	//情報設定
	void	SetMode(int mode);
};
