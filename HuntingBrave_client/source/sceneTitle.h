
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

	bool		pushState;
	float		percentage;
	float		alpha;
public:
	//	�������E���
	bool	Initialize( void )override;
	~sceneTitle( void )override;

	//	�X�V�E�`��
	void	Update( void )override;
	void	Render( void )override;
};
