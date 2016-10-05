
#pragma once

//***************************************************************
//
//	Playerクラス
//
//***************************************************************

//	include
#include	"BaseChara.h"

//	class
class Player : public BaseChara
{
private:
	enum MODE	//	仮
	{
		MOVE,
		//POSTURE,
		MODE_MAX
	};

	//	モード別関数ポインタ
	void( Player::*ModeFunction[MODE_MAX] )( void );

public:
	//	初期化・解放
	Player( void );
	~Player( void )override;
	bool	Initialize( void )override;
	
	//	更新・描画
	void	Update( void )override;

	//	各モード動作関数
	void	MoveMode( void );
	//void	PostureMode( void );

	//	動作関数
	void	Move( void );

};
