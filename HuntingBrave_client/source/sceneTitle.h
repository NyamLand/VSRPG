
#pragma once

//***************************************************************
//
//	sceneTitle�N���X
//
//***************************************************************

//	include

//	class
class sceneTitle : public Scene
{
private:
	iex2DObj*	bg;
	iex2DObj*	lovelive;
	iex2DObj*	chanolive;

	bool		pushState;
	float		percentage;
	float		percentage2;
	float		alpha;
	float		alpha2;
public:
	//	�������E���
	bool	Initialize( void )override;
	~sceneTitle( void )override;

	//	�X�V�E�`��
	void	Update( void )override;
	void	Render( void )override;
};
