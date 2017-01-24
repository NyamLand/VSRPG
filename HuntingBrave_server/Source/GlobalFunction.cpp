
#include	"iextreme.h"
#pragma comment( lib,"winmm.lib" )
#include	"GlobalFunction.h"

//*****************************************************************************
//
//	グローバル関数
//
//*****************************************************************************

	//	前フレームからの経過時間取得
	float	GetElapseTime( void )
	{
		//	Windows起動からの経過時間を取得
		static DWORD lastTime = timeGetTime();
		
		//	前フレームからの経過時間を算出
		DWORD elapseTime = timeGetTime() - lastTime;

		//	現フレームの経過時間を加算
		lastTime += elapseTime;
		
		//	経過時間をかえす
		return	( float )elapseTime / 1000.0f;
	}
