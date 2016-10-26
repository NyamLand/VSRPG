
#pragma once

//*****************************************************************************************************************************
//
//	BaseCharaクラス
//
//*****************************************************************************************************************************

//	include

//	class
class BaseChara
{
protected:
	Vector3	pos;
	float		angle;

public:
	//	初期化・解放
	BaseChara( void );
	virtual ~BaseChara( void );
	
	//	更新

	//	情報取得
	Vector3	GetPos( void )const;
};
