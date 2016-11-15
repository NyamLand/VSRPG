
#include	"iextreme.h"
#include	"InputManager.h"

//***************************************************************
//
//	InputManager�N���X
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	�O���[�o��
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	�������E���
//-------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	InputManager::InputManager( void )
	{
	
	}

	//	�f�X�g���N�^
	InputManager::~InputManager( void )
	{

	}

	void	InputManager::Update( void )
	{
		BUTTON_STATE buttonState = BUTTON_STATE::ENTER;
		GetAButton( buttonState );
		GetBButton( buttonState );
		GetXButton( buttonState );
		GetYButton( buttonState );
		GetR1Button( buttonState );
		GetR3Button( buttonState );
		GetL1Button( buttonState );
		GetL3Button( buttonState );
		GetStartButton( buttonState );
		GetSelectButton( buttonState );
	}

//-------------------------------------------------------------------------------------
//	����֐�
//-------------------------------------------------------------------------------------

	//	�X�e�B�b�N���̓`�F�b�N( �X�e�B�b�N�̓��͕���, �ŏ����͒l )
	bool	InputManager::StickInputCheck( const Vector3& inputVec, float minInput )
	{
		float axisX = inputVec.x;
		float axisY = inputVec.y;

		float length = sqrtf( axisX * axisX + axisY * axisY );
		
		if ( length >= minInput )	return	true;
		return	false;
	}

	//	���͏��擾
	BUTTON_TYPE	InputManager::GetInput( int& inputType )
	{
		//	�ϐ�����
		BUTTON_TYPE	buttonType;
		inputType = BUTTON_STATE::NO_INPUT;

		//	���͎擾
		if ( GetAButton( BUTTON_STATE::ENTER ) )
		{
			buttonType = BUTTON_TYPE::A;
			inputType = BUTTON_STATE::ENTER;
		}
		return	buttonType;
	}

//-------------------------------------------------------------------------------------
//	�e�{�^�����擾
//-------------------------------------------------------------------------------------

	//	A�{�^���擾
	bool InputManager::GetAButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_A ) == buttonState )
		{
			printf( "A-Button\n" );
			return	true;
		}

		return	false;
	}

	//	B�{�^���擾
	bool InputManager::GetBButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_B ) == buttonState )
		{
			printf( "B-Button\n" );
			return	true;
		}

		return	false;
	}

	//	X�{�^���擾
	bool InputManager::GetXButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_X ) == buttonState )
		{
			printf( "X-Button\n" );
			return	true;
		}

		return	false;
	}

	//	Y�{�^���擾
	bool InputManager::GetYButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_Y ) == buttonState )
		{
			printf( "Y-Button\n" );
			return	true;
		}

		return	false;
	}

	//	R1�{�^���擾
	bool InputManager::GetR1Button( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_R1 ) == buttonState )
		{
			printf( "R1-Button\n" );
			return	true;
		}

		return	false;
	}

	//	R3�{�^���擾
	bool InputManager::GetR3Button( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_R3 ) == buttonState )
		{
			printf( "R3-Button\n" );
			return	true;
		}

		return	false;
	}

	//	L1�{�^���擾
	bool InputManager::GetL1Button( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_L1 ) == buttonState )
		{
			printf( "L1-Button\n" );
			return	true;
		}

		return	false;
	}

	//	L3�{�^���擾
	bool InputManager::GetL3Button( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_L3 ) == buttonState )
		{
			printf( "L3-Button\n" );
			return	true;
		}
		
		return	false;
	}

	//	�X�^�[�g�{�^���擾
	bool InputManager::GetStartButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_SELECT ) == buttonState )
		{
			printf( "Start-Button\n" );
			return	true;
		}

		return	false;
	}

	//	�Z���N�g�{�^���擾
	bool InputManager::GetSelectButton( InputManager::BUTTON_STATE buttonState )
	{
		if ( KEY( KEY_ENTER ) == buttonState )
		{
			printf( "Select-Button\n" );
			return	true;
		}

		return	false;
	}

	//	���X�e�B�b�N���͎擾
	Vector3	InputManager::GetStickInputLeft( void )
	{
		//	�o��
		Vector3	out = Vector3(
			KEY( KEY_AXISX ) * 0.001f,
			-KEY( KEY_AXISY ) * 0.001f,
			0.0f );

		return	out;
	}

	//	�E�X�e�B�b�N���͎擾
	Vector3	InputManager::GetStickInputRight( void )
	{
		//	�o��
		Vector3	out = Vector3 (
			KEY( KEY_AXISX2 ) * 0.001f,
			-KEY( KEY_AXISY2 ) * 0.001f,
			0.0f );

		return	out;
	}
