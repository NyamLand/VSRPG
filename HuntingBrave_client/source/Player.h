
#pragma once

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
#include	"BaseEquipment.h"
#include	"GameData.h"

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


//	class
class Player : public BaseChara
{
private:
	//	モード別関数ポインタ
	void( Player::*ModeFunction[MODE::MODE_MAX] )( void );
	PlayerParam	playerParam;

public:
	//	初期化・解放
	Player( void );
	~Player( void )override;
	bool	Initialize( int id );
	
	//	更新・描画
	void	Update( PlayerParam& playerParam );
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	各モード動作関数
	void	MoveMode( void );
	//void	PostureMode( void );
	void	ModeSwordAttack( void );
	void	ModeMagicAttack( void );
	void	ModeAvoid( void );			//回避

	//	動作関数
	bool		Move( void );
	bool		SwordAttack( void );		//行動が終了すれば1を返し、中断されれば2を返す
	bool		MagicAttack( void );
	bool		Avoid( void );

	//	情報設定
	void	SetPlayerParam( const PlayerParam& playerParam );
};
