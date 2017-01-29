//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************

//	class前方宣言
#include	"Stage.h"

//	class
class	sceneMain : public Scene
{
private:
	Stage*	stage;
	
	//	バックバッファ
	Surface*	backBuffer;
	iex2DObj*	mainScreen;

	float	blackWhitePercentage;
	static	bool	threadState;

public:
	~sceneMain( void );
	//	初期化
	bool Initialize( void );
	//	更新・描画
	void Update( void );	//	更新
	void Render( void );	//	描画

	//	動作関数
	void	DebugRender( void );
	void	MyInfoRender( void );
	void	DeadScreen( void );
	static void	ThreadFunction( void* ptr );
};


