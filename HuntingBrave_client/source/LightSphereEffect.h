
#pragma once

//***************************************************************
//
//	LightSphereEffect�N���X
//
//***************************************************************

//	include
#include	"Effect.h"

//	class
class LightSphereEffect : public Effect
{
private:
	DWORD	color;
	float			speed;
	float			percentage;

public:
	//	�������E���
	LightSphereEffect( void );
	~LightSphereEffect( void )override;

	//	�X�V�E�`��
	void	Update( void )override;
	void	Render( void )override;

	//	���擾
	
};