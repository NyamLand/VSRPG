
#pragma once

//*****************************************************************************************************************************
//
//	InputManager�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"

//	�萔( XBox�R���g���[�� )
namespace
{
	//	�L�[
	namespace KEY_TYPE
	{
		enum 
		{
			NO_INPUT,
			A = 4,
			B,
			X,
			Y,
			L1 = 8,
			R1,
			L3 = 12,
			R3,
			SELECT,
			START,
		};
	}

	//	���͏��
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

//	struct
struct InputInfo
	{
		float	axisX, axisY;
		int	keyType;
		int	keyState;
	};


//	class
class InputManager
{
private:
	InputInfo	inputInfo[PLAYER_MAX];

public:
	//	�������E���
	InputManager( void );
	~InputManager( void );

	//	���ݒ�
	void	SetInput( int id, int keyType, int keyState );
	void	SetAxis( int id, float axisX, float axisY );

	//	���擾
	InputInfo&	GetInput( int id );
	bool	GetInputState( int id, int keyType, int keyState );
};

extern	InputManager*	inputManager;