
#pragma once

//***************************************************************
//
//	sceneTitleクラス
//
//***************************************************************

//	include

//	class
class sceneTitle : public Scene
{
private:
	bool	connectionOK;

public:
	//	初期化・解放
	bool	Initialize( void )override;
	~sceneTitle( void )override;

	//	更新・描画
	void	Update( void )override;
	void	Render( void )override;
};
