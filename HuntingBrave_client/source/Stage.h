
#pragma once

//*************************************************************************
//
//	Stage�N���X
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
	//	�������E���
	Stage( void );
	~Stage( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
};
