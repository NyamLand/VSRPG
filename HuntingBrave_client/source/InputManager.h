
#pragma once

//***************************************************************
//
//	InputManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"

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

//	class
class InputManager : public	Singleton<InputManager>
{
	friend	Singleton<InputManager>;
public:
	enum BUTTON_STATE
	{
		NO_INPUT = -1,
		STAY = 1,
		UP,
		ENTER
	};

private:
	//	�������E���
	InputManager( void );
	~InputManager( void );

public:
	//	����֐�
	bool StickInputCheck( const Vector3& inputVec, float minInput );
	BUTTON_TYPE	GetInput( char& inputType );

	void	Update( void );

	//	���͏��擾
	bool	GetAButton( BUTTON_STATE buttonState );
	bool	GetBButton( BUTTON_STATE buttonState );
	bool	GetXButton( BUTTON_STATE buttonState );
	bool	GetYButton( BUTTON_STATE buttonState );
	bool	GetR1Button( BUTTON_STATE buttonState );
	bool	GetR3Button( BUTTON_STATE buttonState );
	bool	GetL1Button( BUTTON_STATE buttonState );
	bool	GetL3Button( BUTTON_STATE buttonState );
	bool	GetStartButton( BUTTON_STATE buttonState );
	bool	GetSelectButton( BUTTON_STATE buttonState );

	//	�X�e�B�b�N���͎擾
	Vector3 GetStickInputLeft( void );
	Vector3 GetStickInputRight( void );
};

#define	inputManager ( InputManager::GetInstance() )