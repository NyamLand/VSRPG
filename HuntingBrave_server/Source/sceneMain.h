
#pragma once


#pragma once

//************************************************************************
//
//	sceneMain�N���X
//
//************************************************************************

//	include
#include	"Scene.h"

//	class
class sceneMain : public Scene
{
private:
public:
	//	�������E���
	bool	Initialize( void )override;
	~sceneMain( void )override;

	//	�X�V
	void	Update( void )override;
};
