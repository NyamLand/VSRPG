//***************************************************************
//
//	sceneLoadクラス
//
//***************************************************************

//	include	
#include	"WaitLoad.h"

//	class
class sceneLoad : public Scene
{
private:
	WaitLoad*	waitLoad;
	iexView*	view;
	Scene*		newScene;		//	次のシーン
	static bool	threadState;	//	スレッドの状態

public:
	//	初期化・解放
	sceneLoad( Scene* nextScene );
	~sceneLoad( void )override;
	bool	Initialize( void )override;

	//	更新・描画
	void	Update( void )override;
	void	Render( void )override;

	//	動作関数
	static	void	Thread( void* arg );
};
