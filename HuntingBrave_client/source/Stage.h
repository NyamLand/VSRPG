
#pragma once

//*************************************************************************
//
//	Stageクラス
//
//*************************************************************************

//	include
#include	"Image.h"

//	class
class Stage
{
private:
	enum
	{
		STAGE,
		SOTO,
		TREE,
		TORIDE,
		DEPARI,
		HEI,
		MOUNTAIN,
		PARTS_MAX
	};
	iexMesh*	stage[PARTS_MAX];
	iexMesh*	collisionMesh;
	Image*			viewTex;
	iexView*		view;
	Surface*	backBuffer;
	bool				initState;

public:
	//	初期化・解放
	Stage( void );
	~Stage( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
	void	RenderTexture( void );

	//	マップテクスチャ取得
	Image*&	GetTexture( void );
};
