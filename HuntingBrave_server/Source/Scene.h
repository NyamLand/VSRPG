
#pragma once

//*****************************************************************************************************************************
//
//	Scene�N���X
//
//*****************************************************************************************************************************

//	include
namespace
{
	namespace SCENE
	{
		enum
		{
			MATCHING,
			MAIN,
			RESULT
		};
	}
}

//	class
class Scene
{
protected:
	char	scene;

public:
	//	�������E���
	Scene( void ){};
	virtual	~Scene( void ){};
	virtual	bool	Initialize( void ) = 0;

	//	�X�V
	virtual	void	Update( int client ) = 0;

	//	���擾
	char	GetScene( void )const{ return	scene; }
};

