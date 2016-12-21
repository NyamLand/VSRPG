
#pragma once

//***************************************************************
//
//	SingletonƒNƒ‰ƒX
//
//***************************************************************

//	include

//	class
template<class T>
class Singleton
{
protected:
	//	‰Šú‰»E‰ğ•ú
	Singleton( void ){}
	virtual ~Singleton( void ){}

public:
	//	À‘Ìæ“¾
	static T* GetInstance( void )
	{
		static T instance;
		return	&instance;
	}
};
