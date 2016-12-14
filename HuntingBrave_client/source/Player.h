
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

namespace
{
	//	モーション管理
	namespace MOTION_NUM
	{
		//	モーション番号
		enum
		{
			POSUTURE,						//	待機
			RUN_START,						//	走り出し
			RUN,									//	走り
			ATTACK1,							//	攻撃１
			ATTACK2,							//	攻撃２
			STEP,								//	ステップ
			MAGIC_CHANT_START,		//	詠唱開始
			MAGIC_CHANT,					//	詠唱中
			MAGIC_ACTUATION,			//	魔法発動
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
}



//	class
class Player : public BaseChara
{
private:
	//	パラメータ
	int	id;
	PlayerParam		playerParam;
	iex3DObj* org;

	enum	MODE//	仮
	{
		MOVE,
		//POSTURE,
		SWOADATTACK,
		MAGICATTACK,
		AVOID,
		MODE_MAX
	};

public:
	//	初期化・解放
	Player( void );
	~Player( void );
	bool	Initialize( int id );
	
	//	更新・描画
	void	Update( PlayerParam& playerParam );
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	動作関数
	bool		Move( void );
	void		SetAttackShape( void );
	void		ChangeTexture( int colorNum );

	//	情報設定
	void	SetPlayerParam( const PlayerParam& playerParam );
	void	SetModel( void );
};
