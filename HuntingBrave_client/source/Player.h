
#pragma once
#include	"BaseEquipment.h"
//***************************************************************
//
//	Playerクラス
//
//***************************************************************

struct Status
{
	float	hp;
	float	atk;
	float	dif;
	float	mat;
	float	mdf;
	float	speed;
};

//struct Equipments
//{
//	BaseEquipment*	atk;
//	BaseEquipment*	mat;
//	BaseEquipment*
//
//};


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
		AVOID,
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
		AVOID,
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
	void	ModeAvoid( void );			//回避


	//	動作関数
	bool		Move( void );
	bool		SwordAttack(void);		//行動が終了すれば1を返し、中断されれば2を返す
	bool		MagicAttack( void );
	bool		Avoid( void );



	//情報設定
	void	SetMode(int mode);
};
