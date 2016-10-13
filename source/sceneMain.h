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
	static	GameParam*	m_GameParam;

public:
	~sceneMain( void );
	//	初期化
	bool Initialize( void );
	//	更新・描画
	void Update( void );	//	更新
	void Render( void );	//	描画

	//	情報取得
	void	MyInfoRender( void );
	static	void	ThreadFunc1( void );
	static	void	ThreadFunc2( void );
};


