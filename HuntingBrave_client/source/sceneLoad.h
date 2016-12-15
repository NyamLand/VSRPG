//***************************************************************
//
//	sceneLoadクラス
//
//***************************************************************

//	include	

//	class
class sceneLoad : public Scene
{
private:
public:
	//	初期化・解放
	bool	Initialize( void )override;
	~sceneLoad( void )override;

	//	更新・描画
	void	Update( void )override;
	void	Render( void )override;
};
