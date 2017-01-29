
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

	//	クラスタイプ
	namespace CLASS_TYPE
	{
		enum
		{
			NORMAL,
			FIGHTER,
			MAGICIAN,
			KNIGHT,
			PRIEST,
			ASSASSIN,
			CLASS_MAX
		};
	}
}

//	class
class Player : public BaseChara
{
protected:
	//	パラメータ
	int	id;
	PlayerParam		playerParam;
	iex3DObj* org[CLASS_TYPE::CLASS_MAX];
	enum	MODE//	仮
	{
		MOVE,
		SWOADATTACK,
		MAGICATTACK,
		AVOID,
		MODE_MAX
	};

	char curClass;

public:
	//	初期化・解放
	Player( void );
	~Player( void );
	virtual	bool	Initialize( int id );
	void	Load( void );

	//	更新・描画
	void	Update( void );
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	動作関数
	void	SetAttackShape( void );
	void	ChangeTexture( iex3DObj*& model, char classType, int id );
	void	ChangeModel( char nextClass );
	void	PlaySE( int motion );
	void	ChangeFaceTexture( char faceType );
	void	ChangeFaceType( int motion );

	//	情報設定
	void	SetPlayerParam( const PlayerParam& playerParam );
	void	SetCollisionShape( const PlayerParam& playerParam );
	void	SetMotion( int motion ) override;
};
