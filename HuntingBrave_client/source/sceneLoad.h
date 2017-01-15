//***************************************************************
//
//	sceneLoad�N���X
//
//***************************************************************

//	include	
#include	"WaitLoad.h"

//	class
class sceneLoad : public Scene
{
private:
	WaitLoad*	waitLoad;
	iexView*	view;
	Scene*		newScene;		//	���̃V�[��
	static bool	threadState;	//	�X���b�h�̏��

public:
	//	�������E���
	sceneLoad( Scene* nextScene );
	~sceneLoad( void )override;
	bool	Initialize( void )override;

	//	�X�V�E�`��
	void	Update( void )override;
	void	Render( void )override;

	//	����֐�
	static	void	Thread( void* arg );
};
