//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************

//	class前方宣言
#include	"Stage.h"
class TimeUpUI;

//	class
class	sceneMain : public Scene
{
private:
	Stage*	stage;
	
	//	バックバッファ
	Surface*	backBuffer;
	iex2DObj*	mainScreen;

	//	タイムアップ用
	TimeUpUI*	timeUp;

	//	シェーダー用
	iex2DObj*	diffuse;
	iex2DObj*	specular;
	iex2DObj*	depth;
	iex2DObj*	normal;
	iex2DObj*	light;

	float	blackWhitePercentage;
	static	bool	threadState;

public:
	~sceneMain( void );
	//	初期化
	bool Initialize( void );
	void	DifferedInitialize( void );

	//	更新・描画
	void Update( void );	//	更新
	void Render( void );	//	描画

	//	動作関数
	void	DebugRender( void );
	void	MyInfoRender( void );
	void	DeadScreen( void );
	static void	ThreadFunction( void* ptr );
};


