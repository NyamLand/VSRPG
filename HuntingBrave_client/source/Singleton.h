
#pragma once

//***************************************************************
//
//	Singletonクラス
//
//***************************************************************

//	include

//	class
template<class T>
class Singleton
{
protected:
	//	初期化・解放
	Singleton( void ){}
	virtual ~Singleton( void ){}

public:
	//	実体取得
	static T* GetInstance( void )
	{
		static T instance;
		return	&instance;
	}
};
