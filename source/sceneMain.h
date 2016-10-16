//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************

//	クラス前方宣言
class GameParam;

class	sceneMain : public Scene
{
private:

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
	static	void	ThreadReceive( void );
};


