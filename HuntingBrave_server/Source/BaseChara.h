
#pragma once

//*****************************************************************************************************************************
//
//	BaseCharaクラス
//
//*****************************************************************************************************************************

//	include

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
		MODE_MAX
	};
}

//	class
class BaseChara
{
protected:
	Vector3	pos;
	float		angle;
	int			mode;
	int			motion;

public:
	//	初期化・解放
	BaseChara( void );
	virtual ~BaseChara( void );
	
	//	情報設定
	bool	SetMode( int nextMode );

	//	情報取得
	Vector3	GetPos( void )const;
};
