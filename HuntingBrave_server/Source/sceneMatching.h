
#pragma once

//************************************************************************
//
//	sceneMatching�N���X
//
//************************************************************************

//	include
#include	"Scene.h"

//	class
class sceneMatching : public Scene
{
private:
public:
	//	�������E���
	bool	Initialize( void )override;
	~sceneMatching( void )override;

	//	�X�V
	void	Update( int client )override;
};
