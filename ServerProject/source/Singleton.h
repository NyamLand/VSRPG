
#pragma once

//***************************************************************
//
//	Singleton�N���X
//
//***************************************************************

//	include

//	class
template<class T>
class Singleton
{
protected:
	//	�������E���
	Singleton( void ){}
	virtual ~Singleton( void ){}

public:
	//	�������E���
	virtual bool	Initialize( void ){ return true; }
	virtual void Release( void ){};

	//	���̎擾
	static T* GetInstance( void )
	{
		static T instance;
		return	&instance;
	}
};
