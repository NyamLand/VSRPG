
#pragma once

//*************************************************************************
//
//	Stageクラス
//
//*************************************************************************

//	include

//	class
class Stage
{
private:
	iexMesh*	collisionMesh;
	iexMesh*	stage;
	iexMesh*	soto;
	iexMesh*	tree;
	iexMesh*	toride;

public:
	//	初期化・解放
	Stage( void );
	~Stage( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
};
