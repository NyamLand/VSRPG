
#pragma once

//*************************************************************************
//
//	Stage�N���X
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
	//	�������E���
	Stage( void );
	~Stage( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
	void	RenderTexture( void );

	//	�}�b�v�e�N�X�`���擾
	Image*&	GetTexture( void );
};
