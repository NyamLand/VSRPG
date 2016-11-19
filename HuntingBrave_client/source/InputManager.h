
#pragma once

//***************************************************************
//
//	InputManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"

//	�萔
namespace
{
	//	�L�[���
	namespace KEY_TYPE
	{
		enum
		{
			A = KEY_A,
			B,
			X,
			Y,
			L1 = KEY_L1,
			R1,
			L3 = KEY_L3,
			R3,
			SELECT,
			START,
		};
	}

	//	�L�[���
	namespace KEY_STATE
	{
		enum
		{
			NO_INPUT,
			STAY,
			UP,
			ENTER
		};
	}
}

//	class
class InputManager : public	Singleton<InputManager>
{
	friend	Singleton<InputManager>;
public:

private:
	//	�������E���
	InputManager( void );
	~InputManager( void );

public:
	//	�X�e�B�b�N���͎擾
	void GetStickInputLeft( float& axisX, float& axisY );
	void GetStickInputRight( float& axisX, float& axisY );
};

#define	inputManager ( InputManager::GetInstance() )