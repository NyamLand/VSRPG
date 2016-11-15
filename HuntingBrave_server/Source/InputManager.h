
#pragma once

//*****************************************************************************************************************************
//
//	InputManager�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"

//	�萔
enum BUTTON_TYPE
{
	NO_INPUT = -1,
	A = 1,
	B,
	X,
	Y,
	R1,
	R3,
	L1,
	L3,
	START,
	SELECT,
};

//	struct
struct InputInfo
{
	float	axisX, axisY;
	int	buttonType;
	int	inputType;
};

//	class
class InputManager
{
public:
	enum BUTTON_STATE
	{
		NO_INPUT = -1,
		STAY = 1,
		UP,
		ENTER
	};

private:
	InputInfo	inputInfo[PLAYER_MAX];

public:
	//	�������E���
	InputManager( void );
	~InputManager( void );

	//	�X�V

	//	����֐�

	//	���ݒ�
	void	SetInput( int id, char buttonType, char inputType );
	void	SetAxis( int id, float axisX, float axisY );

	//	���擾
	InputInfo&	GetInput( int id );
};

extern	InputManager*	inputManager;