
#pragma once

//*****************************************************************************************************************************
//
//	Sceneクラス
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
	//	初期化・解放
	Scene( void ){};
	virtual	~Scene( void ){};
	virtual	bool	Initialize( void ) = 0;

	//	更新
	virtual	void	Update( int client ) = 0;

	//	情報取得
	char	GetScene( void )const{ return	scene; }
};

