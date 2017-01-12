
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
			A = 4,
			B,
			X,
			Y,
			L1 = 8,
			R1,
			L3 = 12,
			R3,
			SELECT,
			START
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
			ENTER,
			KEY_STATE_MAX
		};
	}
}

//	struct
struct InputInfo
{
	float	axisX, axisY, axisRX, axisRY;
	std::map<char, char>	keyState;
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
	void	SetInput( int id, char keyType, char keyState );
	void	SetAxis( int id, float axisX, float axisY );
	void	SetAxisR( int id, float axisRX, float axisRY );
	void	ResetInput( int client );

	//	���擾
	InputInfo&	GetInput( int id );
	bool	GetInputState( int id, char keyType, char keyState );
};

extern	InputManager*	inputManager;