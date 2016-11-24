
#pragma once

//*****************************************************************************************************************************
//
//	BaseCharaクラス
//
//*****************************************************************************************************************************

//	include
#include	"CharaInfo.h"

//	enum
namespace MODE
{
	//	モード番号
	enum 
	{
		MOVE,
		SWOADATTACK,
		MAGICATTACK,
		AVOID,
		DAMAGE,
		MODE_MAX
	};
}

//	定数関連
namespace
{
	//	モーション番号
	enum PLAYER_MOTION
	{
		POSUTURE,						//	待機
		RUN_START,						//	走り出し
		RUN,									//	走り
		ATTACK1,							//	攻撃１
		ATTACK2,							//	攻撃２
		STEP,								//	ステップ
		MAGIC_CHANT_START,		//	詠唱開始
		MAGIC_CHANT,					//	詠唱中
		MAGIC_ACTIVATION,			//	魔法発動
		KNOCKBACK1,					//	仰け反り１
		KNOCKBACK2,					//	仰け反り２
		FALL,									//	倒れる
		DEAD,								//	死亡
		EAT,									//	食べる
		MENU_OPEN,						//	メニューを開く
		MENU,								//	メニュー操作中
		LEVEL_UP,							//	レベルアップ
		MENU_CLOSE,					//	メニューを閉じる
		WIN,									//	勝利
		WIN_KEEP,						//	勝利キープ
		CRY									//	泣き
	};
}

//	class
class BaseChara
{
protected:
	Vector3	pos;
	float			angle;
	int			mode;
	int			motion;

public:
	//	初期化・解放
	BaseChara( void );
	virtual ~BaseChara( void );

	//	情報設定
	bool	SetMode( int nextMode );
	void	SetAttackInfo( const AttackInfo& attackInfo );

	//	情報取得
	Vector3	GetPos( void )const;
};
