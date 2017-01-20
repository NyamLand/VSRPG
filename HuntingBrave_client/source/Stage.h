
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
	iexMesh*	collisionMesh;
	iexMesh*	stage[PARTS_MAX];

public:
	//	初期化・解放
	Stage( void );
	~Stage( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
};
