
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
	iexMesh*	collisionMesh;
	iexMesh*	stage;
	iexMesh*	soto;
	iexMesh*	tree;
	iexMesh*	toride;

public:
	//	�������E���
	Stage( void );
	~Stage( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
};
