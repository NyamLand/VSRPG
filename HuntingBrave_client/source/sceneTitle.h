
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
	bool	connectionOK;

public:
	//	�������E���
	bool	Initialize( void )override;
	~sceneTitle( void )override;

	//	�X�V�E�`��
	void	Update( void )override;
	void	Render( void )override;
};
