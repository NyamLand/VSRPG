
#include	"iextreme.h"
#pragma comment( lib,"winmm.lib" )
#include	"GlobalFunction.h"

//*****************************************************************************
//
//	�O���[�o���֐�
//
//*****************************************************************************

	//	�O�t���[������̌o�ߎ��Ԏ擾
	float	GetElapseTime( void )
	{
		//	Windows�N������̌o�ߎ��Ԃ��擾
		static DWORD lastTime = timeGetTime();
		
		//	�O�t���[������̌o�ߎ��Ԃ��Z�o
		DWORD elapseTime = timeGetTime() - lastTime;

		//	���t���[���̌o�ߎ��Ԃ����Z
		lastTime += elapseTime;
		
		//	�o�ߎ��Ԃ�������
		return	( float )elapseTime / 1000.0f;
	}
